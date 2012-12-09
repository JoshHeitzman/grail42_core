#                  Copyright (C) 2012 Josh Heitzman
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or online copies at:
# * http://www.boost.org/LICENSE_1_0.txt
# * http://opensource.org/licenses/BSL-1.0
# * http://directory.fsf.org/wiki/License:Boost1.0
# * http://en.wikipedia.org/wiki/Boost_Software_License

import os

from grail42.core.ease import algorithms

#
# WARNING
#
# Currently this module is private as indicated by the underscore prefixed to the module 
# name.  The code in this module is sufficient to support the immediate need it was written to 
# fulfill; however, it needs refactoring and proper testing.  This code should not be utilized in 
# new scenarios without first being refactored and tested.
#

__all__ = ("Walker",)

class Walker(object):
    # REVIEW when support for dirs and files is added, as it may turn out that those should be
    # handled seperately.  In that case, trees should be a required argument.
    def __init__(self, processors, trees=None):
        self._processors = processors
        self._trees = trees
    def __call__(self, trees=None):
        if trees is not None:
            self._trees = trees
        # TODO make the result an object with attributes instead of a dict.  The only client of
        # the result is clonetree.py
        results = dict()
        for tree in self._trees:
            algorithms.foreach(lambda p: p.on_tree_root_visit(tree), self._processors)
            for dirpath, dirnames, filenames in os.walk(tree):
                # REVIEW will all three ever be empty?
                for processor in self._processors:
                    treeconfigs, dirconfigs, fileconfigs = processor.on_tree_dir_visit(
                        tree, dirpath, dirnames, filenames)
                    if treeconfigs is not None:
                        results.setdefault('annotations_for_elements', dict()).setdefault(
                            'trees', dict()).setdefault(dirpath, list()).extend(treeconfigs)
                    # TODO add support for annotations on elements of a directory and single 
                    # elements in addition to entire trees.
                    assert dirconfigs is None
                    assert fileconfigs is None
                    # skip additional processors and additions to results if everything was removed
                    if not dirnames and not filenames:                        
                        break 
                else:
                    names_for_path = dict()
                    if dirnames:
                        names_for_path['dirnames'] = dirnames
                    if filenames:
                        names_for_path['filenames'] = filenames
                    results.setdefault('annotated_elements', list()).append((dirpath, names_for_path))
        return results
