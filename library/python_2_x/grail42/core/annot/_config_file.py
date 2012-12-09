#                  Copyright (C) 2012 Josh Heitzman
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or online copies at:
# * http://www.boost.org/LICENSE_1_0.txt
# * http://opensource.org/licenses/BSL-1.0
# * http://directory.fsf.org/wiki/License:Boost1.0
# * http://en.wikipedia.org/wiki/Boost_Software_License

import re
import sys
import os
import ConfigParser
import functools

from grail42.core.ease import iterators, invoke, item

#
# WARNING
#
# Currently this module is private package as indicated by the underscoreprefixed to the module 
# name.  The code in this module is sufficient to support the immediate need it was written to 
# fulfill; however, it needs refactoring and proper testing.  This code should not be utilized in 
# new scenarios without first being refactored and tested.
#

__all__ = ("GitIgnorePruner",)

# REVIEW move to a more general purpose location?
def _consolidate_faux_containers(parser):
    container_spec=re.compile("^.+?\[.+?\]$")
    for section in parser.sections():
        containers = {}
        for name, value in parser.items(section):
            if container_spec.match(name) is not None:
                container_name, item_key_or_index = name[:-1].split('[')
                if invoke.try_except(lambda: parser.get(section, container_name)):
                    # An option exists for container_name, so container can not be added to section
                    containers[container_name] = None
                    continue
                container_options_pair = containers.setdefault(container_name, (dict(), list()))
                if container_options_pair is not None:
                    container = container_options_pair[0]
                    if item_key_or_index in container:
                        # duplicate key/index found, not a valid container so stop processing it
                        containers[container_name] = None
                        continue
                    container[item_key_or_index] = value
                    container_options_pair[1].append(name)
        options_to_remove = []
        # TODO add support for keyed containers as well as indexed containers.
        for container_name, container_options_pair in containers.iteritems():
            if container_options_pair is None:
                continue
            container = container_options_pair[0]
            index_min = sys.maxint
            index_max = -1
            index_count = 0
            for key_or_index in container.iterkeys():
                try:
                    index = int(key_or_index)
                except:
                    # Keys not indexes
                    container = None
                    break
                if index >= sys.maxint:
                    # Index to large, treat as keys
                    container = None
                    break
                if index < index_min:
                    index_min = index
                if index > index_max:
                    index_max = index
                index_count += 1
            else:
                # indexes need to be contiguous, starting at 0
                if index_max >= 0 and index_max-index_min+1 == index_count:
                    items_to_sort = container.items()
                    items_to_sort.sort()
                    container = [value for index, value in items_to_sort]
            if container is None:
                continue
            parser.set(section, container_name, container)
            options_to_remove.extend(container_options_pair[1])
        for toremove in options_to_remove:
            parser.remove_option(section, toremove)

# NOTE while _AnnotationFile is a private type, instances of it are provided to clients of
# the public type AnnotationsLoader.
class _AnnotationFile(object):
    def __init__(self, path):
        #self.annotation_file_path = path # Can be useful when debugging
        self._parser = ConfigParser.ConfigParser(allow_no_value=True)
        self._parser.read(path)
        _consolidate_faux_containers(self._parser)
    def get(self, key_subkey):
        """Returns the value idenified by the ordered pair key_subkey whose first value is the key 
        and second is the subkey.  Raises and exception if the key or subkey is not present."""
        return self._parser.get(*key_subkey)
    # REVIEW consider creating a _AnnotationKey type that provdes the methods: __itemget__, 
    # __contains__ and then providing an iterkeys method on this type.  This would allow removing
    # this method, whose only caller is in clonetree.py
    def for_each_key(self, function):
        for section in self._parser.sections():
            function(section, functools.partial(self._parser.get, section))


class AnnotationsLoader(object):
    def __init__(self):
        pass
    def _find_parallel_annotation_directories(self, path):
        # Parallel as in at the same depth in the filesystem.  The common ancestor directories can
        # be any of the segments of the path.  The code is consistent with the specification that
        # is documented separately.
        #
        # For example the directories:
        #   'c:\dir1\dir2.g42.annots\target'
        #   'c:\dir1.g42.annots\dir2\target'
        # are both parallel annotation directory to:
        #   'c:\dir1\dir2\target'
        annotation_parallel_dirname_remainder_spec=re.compile("^\.g42\..*?annots$")
        parallel_dirs = []
        tail_original = ""
        for head, tail in iterators.dowhile(
            os.path.split(path), item.second, lambda p: os.path.split(p[0])):
            len_tail = len(tail)
            for name in os.listdir(head):
                remainder = name if name[0] != '.' else name[1:]
                if not remainder.startswith(tail):
                    continue
                remainder = remainder[len_tail:]
                if not annotation_parallel_dirname_remainder_spec.match(remainder):
                    continue
                parallel_dir = head + os.sep + name + tail_original
                if os.path.exists(parallel_dir):
                    parallel_dirs.append(parallel_dir)
            tail_original = os.sep + tail + tail_original
        return parallel_dirs
    def _find_tree_annotations(self, tree, dirnames, filenames):
        # For example 'i.g42.0b.annot'
        tree_annotation_in_parallel_dir_filename_spec=re.compile("^\.?i\.g42\..*?0b\.annot(\..+)?$")
        
        treeconfigs = []
        # TODO
        # 1. check if any of the filenames match the filename spec for a tree annotation file at the
        #    root of a tree 
        # 2. check if any of the dirnames match the dirname spec for conforming subdirectories
        #    a. check if any of the filenames in conforming subdirectories match the filename spec 
        #       for a tree annotation file in a subdirectory of the root
        # 3. check if any of the filenames match the filename spec for an annotation archive file
        #    a. check if any of the filenames in the root of the annotation archive files match the
        #       filename spec for a tree annotation file in a archive
        
        parallel_dirs = self._find_parallel_annotation_directories(tree)
        
        # 4. check each parallel to see if any of the filenames match the filename spec for a tree 
        # annotation file located in a directory parralel to the root of the tree.
        for parallel_dir in parallel_dirs:
            for name in os.listdir(parallel_dir):
                if not tree_annotation_in_parallel_dir_filename_spec.match(name):
                    continue
                filepath = parallel_dir + os.sep + name
                if not os.path.isfile(filepath):
                    continue
                annot = _AnnotationFile(filepath)
                treeconfigs.append(annot)
        
        # TODO from above continued
        # 5. 
        return treeconfigs
    def on_tree_root_visit(self, tree):
        pass
    def on_tree_dir_visit(self, tree, path, dirnames, filenames):
        treeconfigs = self._find_tree_annotations(path, dirnames, filenames)
        # TODO load directory, file, and archive annotations as well
        return treeconfigs if treeconfigs else None, None, None
