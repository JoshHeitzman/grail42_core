#                  Copyright (C) 2012 Josh Heitzman
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or online copies at:
# * http://www.boost.org/LICENSE_1_0.txt
# * http://opensource.org/licenses/BSL-1.0
# * http://directory.fsf.org/wiki/License:Boost1.0
# * http://en.wikipedia.org/wiki/Boost_Software_License

__all__ = ("forloop", "dowhile")

# REVIEW It's possible there is an existing, standard, and equally concise way 
# of doing what these generators accomplish. The author spent more time trying to find it then 
# it took to actuall write these prior to writing them, so that existing way is not very 
# discoverable.

# REVIEW The benifts of using this module are unproven, and is an experiment by the author to see 
# if its use improves productivity.

def forloop(initial, condition, increment):
    """Generator modeled on the C++ for loop.  The initial argument is the first
    value to be yielded.  The condition argument is a unary callable that is 
    passed the value to be yielded and its result determines if the value is
    yielded (True) or generation stops (False), so it is possible for not values
    to be yielded.  The increment argument is a unary callable that is passed 
    the value just yielded and its result is the next value to yield."""
    while condition(initial):
        yield initial
        initial = increment(initial)

def dowhile(initial, condition, increment):
    """Generator modeled on a hybrid of the C++ for and do-while loops.  The 
    initial argument is the first value to be yielded and it will always be 
    yielded.  The condition argument is a unary callable that is passed the 
    value just yielded and its result determines if generation continues (True) 
    or stops (False).  The increment argument is a unary callable that is passed
    the value just yielded and its result will be yielded immediately."""
    while True:
        yield initial
        if not condition(initial):
            break
        initial = increment(initial)
