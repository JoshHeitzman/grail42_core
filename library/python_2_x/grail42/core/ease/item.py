#                  Copyright (C) 2012 Josh Heitzman
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or online copies at:
# * http://www.boost.org/LICENSE_1_0.txt
# * http://opensource.org/licenses/BSL-1.0
# * http://directory.fsf.org/wiki/License:Boost1.0
# * http://en.wikipedia.org/wiki/Boost_Software_License

# __all__ intentionally omitted.

# This module provides shorthand for common lambdas and lambda factories specific to accessing 
# items in sequences to allow for more concise code, thus each name is shorter than the lambda it 
# aliases.

# REVIEW The benifts of using this module are unproven, and is an experiment by the author to see 
# if its use improves productivity.

first = lambda s: s[0]
second = lambda s: s[1]
third = lambda s: s[2]

last = lambda s: s[-1]

at = lambda i: lambda s: s[i]