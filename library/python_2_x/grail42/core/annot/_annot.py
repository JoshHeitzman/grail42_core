#                  Copyright (C) 2012 Josh Heitzman
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or online copies at:
# * http://www.boost.org/LICENSE_1_0.txt
# * http://opensource.org/licenses/BSL-1.0
# * http://directory.fsf.org/wiki/License:Boost1.0
# * http://en.wikipedia.org/wiki/Boost_Software_License

from _git import ignore
import _config_file
import _local_filesystem

#
# WARNING
#
# Currently this module is package as indicated by the underscore prefixed to the module 
# name.  The code in this module is sufficient to support the immediate need it was written to 
# fulfill; however, it needs refactoring and proper testing.  This code should not be utilized in 
# new scenarios without first being refactored and tested.
#

__all__ = ("prepare_query_maker",)

# TODO add the additional parameters to query makers.  Probably something like:
#  annotation_handler - optional callable taking one argument that will be passed an
#   annotations object and returns a sequence of pairs (key, subkey) that 
#   identify the values to include in the result set.  If not supplied
#   the complete annotations will be passed to annotated_element_handler (or included in the result
#   set if annotated_element_handler is not supplied).  
#   The handler may not be executed locally, and will be pickled locally and unpickled remotely if 
#   remote execution is required.
#  annotated_element_handler - callable taking two arguments.  The first argument is an annotations
#   object and the second is the sequence of elements that the annotations apply to.
#   If the second argument is None then the annotations apply to all elements.
#   The annotations object is only guaranteed to include values whose identifying
#   (key, subkey) pair was returned from annotation_handler.  Other values may or
#   may not be included.  If present the result will not include the annotations.
#  unannotated_element_handler - optional callable taking one argument that will be passed the id of 
#   each elemented not included in a sequence passed to annotated_element_handler.
#   If present the result will not include the unannotated element ids.
#  element_handler - optional callable taking one argument that will be passed the id of 
#   each element.  If False is returned then element will not be included in
#   element ids.  May be called as soon as an element is encountered and before
#   any annotations have been found for the element.  If present the result will not include
#   the annotated element ids.

class _MakeQuery(object):
    def __init__(self, *args, **kwargs):
        self.processors = []
        filters = kwargs.get('filters')
        if filters is not None:
            self.processors.extend(filters)
        if 'annotation_types' not in kwargs:
            self.processors.append(_config_file.AnnotationsLoader)
    def __call__(self, *args, **kwargs):
        """kwargs:
        trees=None - a sequence of directory paths in the local filesystem"""
        return _local_filesystem.Walker([p() for p in self.processors], **kwargs)
    
class __PrepareQueryMaker(object):
    local_filesytem_gitignore_pruner = "local.filesytem.gitignore.pruner"
    local_filesytem_limits_tree = "local.filesystem.limits.tree"    
    # TODO add support for different annotations types:
    #  default - same as grail42
    #  all
    #  grail42
    #  local.filesytem.gitignore - infers annotations from the .gitingore files used by the git
    #  distributed version control system.
    #
    # TODO add callables parameter to support optional sequence of one or more of 
    #  annotation_handler, annotated_element_handler, unannotated_element_handler, element_handler.
    #  If not present then no callables will be supported.
    @classmethod
    def __call__(cls, *args, **kwargs):
        """
        filters: prepare_query_maker.local_filesytem_gitignore_pruner
        local_filesytem_limits: prepare_query_maker.local_filesytem_limits_tree
        """
        if 'local_filesytem_limits' in kwargs:
            if cls.local_filesytem_limits_tree in kwargs['local_filesytem_limits']:
                filters = []
                if 'filters' in kwargs:
                    if cls.local_filesytem_gitignore_pruner in kwargs['filters']:
                        filters.append(ignore.GitIgnorePruner)
                if not filters:
                    filters = None
                return _MakeQuery(filters=filters)
        raise Exception("Provided arguments do not match current support.")

prepare_query_maker = __PrepareQueryMaker()


