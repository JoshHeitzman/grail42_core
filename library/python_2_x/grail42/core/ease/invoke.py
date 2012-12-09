#                  Copyright (C) 2012 Josh Heitzman
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or online copies at:
# * http://www.boost.org/LICENSE_1_0.txt
# * http://opensource.org/licenses/BSL-1.0
# * http://directory.fsf.org/wiki/License:Boost1.0
# * http://en.wikipedia.org/wiki/Boost_Software_License

__all__ = ("try_except",)

# REVIEW The benifts of using this module are unproven, and is an experiment by the author to see 
# if its use improves productivity.

def try_except(func, *args, **kwargs):
    """Invokes the func(*args, **kwargs) and catches any exception raised by the invocation.
    Returns False if an exception was raised and True otherwise."""
    try:
        func(*args, **kwargs)
        return True
    except:
        return False

