#                  Copyright (C) 2012 Josh Heitzman
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or online copies at:
# * http://www.boost.org/LICENSE_1_0.txt
# * http://opensource.org/licenses/BSL-1.0
# * http://directory.fsf.org/wiki/License:Boost1.0
# * http://en.wikipedia.org/wiki/Boost_Software_License

import os.path
import shutil
import itertools

from grail42.core.ease import iterators
from grail42.core.ease.lambdas import isnotnone

__all__ = ("GitIgnorePruner",)

#
# WARNING
#
# Currently this module is in a private package as indicated by the underscore
# prefixed to the package name.  The code in this package is sufficient to
# support the immediate need it was written to fulfill; however, it needs 
# refactoring and proper testing.  This code should not be utilized in new 
# scenarios without first being refactored and tested.
#

# TODO add support for returning False when the there is '!' at the beginning of the pattern
class _GitIgnoreFile(object):
    """This class is not suitable for consumption thus the leading '_' and
    omission from __all__.  The current implementation is not complete with
    respect to all gitignore features and may possibly be imcompatible with
    some as well."""
    def __init__(self, path):
        self._path = path
        dir_patterns = []
        file_patterns = []
        gitignore = open(path)
        # According the the documentation:
        # 1. empty lines and lines beginning with '#' are ignored.
        # 2. lines ending with '/' are applied to directory names only.
        # 3. Anything is is treated as 'a shell glob suitable for consumption 
        #    by fnmatch(3) with the FNM_PATHNAME flag' and Python's 
        #    shutil.ignore_patterns has thus far proved to be compatible.
        #
        # REVIEW there may be some issues with patterns that include part of the
        # path as well as the filename.
        for line in gitignore.readlines():
            pattern = line.rstrip()
            if pattern and pattern[0] != '#':
                if pattern[-1] == '/':
                    dir_patterns.append(pattern[:-1])
                else:
                    file_patterns.append(pattern)
        gitignore.close()
        self._dir_ignore = shutil.ignore_patterns(*dir_patterns)
        self._file_ignore = shutil.ignore_patterns(*file_patterns)
    def get_ignored_dirs(self, path, names):
        return self._dir_ignore(path, names)
    def get_ignored_files(self, path, names):
        # TODO remove self._path from the beginning of path and then split the
        # remainder into directory names and check against the dir patterns.
        return self._file_ignore(path, names)

class _AnnotationsAdapter(object):
    """This class is not suitable for consumption thus the leading '_' and
    omission from __all__.  This class needs to be refactored."""
    def __init__(self):
        self._paths = {}
        self._reporoots = {}
    def _get_repo_root(self, path):
        for reporoot in self._reporoots:
            # It is assumed that paths are always passed in the same relative
            # form (hopefully absolute and normalized, but that isn't strictly
            # necessary).
            if path.startswith(reporoot):
                return (reporoot, self._reporoots[reporoot])
    # REVIEW consider moving to a RepoInfo class
    def process_new_repo_dir(self, path, repoinfo):
        gitignorepath = path + os.path.sep + ".gitignore"
        if os.path.exists(gitignorepath):
            repoinfo.gitignorefiles[path] = _GitIgnoreFile(gitignorepath)
    def find_repo_root(self, path):
        result = self._get_repo_root(path)
        if result is not None:
            return result
        reporoot = path
        for reporoot in iterators.dowhile(path, lambda i: i[-1] != os.path.sep, os.path.dirname):
            dotgitpath = reporoot + os.path.sep + ".git"
            if os.path.exists(dotgitpath):
                repoinfo = type('RepoInfo', (object,), {'gitignorefiles':dict()})()
                self._reporoots[reporoot] = repoinfo
                self.process_new_repo_dir(reporoot, repoinfo)
                # REVIEW considering merging in the contents of .git/info/exclude as well
                # but currently none of the Grail42 project utilizes that file, so it may
                # not be necessary
                return (reporoot, repoinfo)
        else:
            raise Exception("The git repo root could not be found.")
    # REVIEW consider adding a method add_tree_root that returns an intance
    # with equivalent methods that don't have a tree in the name and don't
    # take a tree parameter
    def on_tree_root_visit(self, path):
        self.find_repo_root(path)
    # REVIEW consider adding a method add_directory that returns an instance
    # with equivalent methods that don't have dir_in_tree in the name and
    # don't take tree or path parameters.
    def _on_tree_dir_visit(self, tree, path):
        reporoot, repoinfo = self._get_repo_root(tree)
        self.process_new_repo_dir(path, repoinfo)
    def _get_gitignores_applying_to_dir_in_tree(self, tree, path):
        """result is ordered from deepest to highest"""
        reporoot, repoinfo = self._get_repo_root(tree)
        len_root = len(reporoot)
        dirpaths = iterators.dowhile(path, lambda i: len(i) >= len_root, os.path.dirname)
        gitignores = filter(isnotnone, itertools.imap(repoinfo.gitignorefiles.get, dirpaths))
        return gitignores
    # TODO refactor this to be use an implementation shared with the method
    # _get_subkey_for_files_in_dir_in_tree and taking a sequence of names instead
    # of a single name.
    def _get_subkey_for_things_in_dir_in_tree(self, is_thing_ignored_name, tree, path, key, subkey, names):
        if key == 'system.revisioncontrol.abstract':
            if subkey == 'excluded.explicitly':
                gitignores = self._get_gitignores_applying_to_dir_in_tree(tree, path)
                # As these are ordered by precedence, things that have been ignored 
                # once do not need to be check again against a lower precedence 
                # git ignore file
                names = names[:] # copy so original is not affected by in-place removals
                result = []
                for gitignore in gitignores:
                    is_thing_ignored = getattr(gitignore, is_thing_ignored_name) 
                    ignored_names = is_thing_ignored(path, names)
                    for name in ignored_names:
                        names.remove(name)
                        result.append((name, True))
                return result
            else:
                raise Exception("Subkey not present.") # TODO better exception
        else:
            raise Exception("Key not present.") # TODO better exception
    def _get_subkey_for_dirs_in_dir_in_tree(self, tree, path, key, subkey, names):
        return self._get_subkey_for_things_in_dir_in_tree('get_ignored_dirs', tree, path, key, subkey, names)
    def _get_subkey_for_files_in_dir_in_tree(self, tree, path, key, subkey, names):
        return self._get_subkey_for_things_in_dir_in_tree('get_ignored_files', tree, path, key, subkey, names)

class GitIgnorePruner(_AnnotationsAdapter):
    def __init__(self):
        _AnnotationsAdapter.__init__(self)
    def on_tree_dir_visit(self, tree, dirpath, dirnames, filenames):
        self._on_tree_dir_visit(tree, dirpath)
        dirname_value_pairs = self._get_subkey_for_dirs_in_dir_in_tree(tree, dirpath, 'system.revisioncontrol.abstract', 'excluded.explicitly', dirnames)
        for dirname, value in dirname_value_pairs:
            dirnames.remove(dirname)
        filename_value_pairs = self._get_subkey_for_files_in_dir_in_tree(tree, dirpath, 'system.revisioncontrol.abstract', 'excluded.explicitly', filenames)
        for filename, value in filename_value_pairs:
            filenames.remove(filename)
        return None, None, None

