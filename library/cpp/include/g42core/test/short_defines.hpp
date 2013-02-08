/*                   Copyright (C) 2012 Josh Heitzman
Distributed under the Boost Software License, Version 1.0.
See accompanying file LICENSE_1_0.txt or online copies at:
* http://www.boost.org/LICENSE_1_0.txt
* http://opensource.org/licenses/BSL-1.0
* http://directory.fsf.org/wiki/License:Boost1.0
* http://en.wikipedia.org/wiki/Boost_Software_License                */

#ifndef G42CORE_HG_CFAAB4B4A0AD4258B527600BA93F724E
#define G42CORE_HG_CFAAB4B4A0AD4258B527600BA93F724E

#ifndef G42CORE_TEST_BEGIN_GROUP
#error "Including g42core/test/test.hpp is required prior to g42core/test/short_defines.hpp"
#endif

G42CORE_MC_PRAGMA_ONCE

#define BEGIN_TESTS G42CORE_TEST_BEGIN_GROUP
#define END_TESTS G42CORE_TEST_END_GROUP
#define DEFINE_TEST G42CORE_TEST_DEFINE_TEST
#define DEFINE_TEST_PART_MT G42CORE_TEST_DEFINE_TEST_PART_MULTITHREADED

/*
VERIFY is used for the default as it is shorter than endorse.  Both verify and endorse are synonyms of certify and confirm.
CERTIFY is used for continuable errors, as the lack of a failure report is the cerification that the expression evaludated to true.
CONTINUE is used here for test fatal errors, as failure only discontinues the current test's execution while allowing the remainder of the tests in the group / suite, process, and overally test run are allowed to continued.
APPROVE is used here for suite / group fatal errors, as it needed a name.
ALLOW is used here for process fatal errors, as the process isn't allowed to execute further and one of the antonyms of allow is keep, which is also an antonym of abort.
CONFIRM is used here for errors fatal to the overall runnning of test groups / suites, as an antonym of confirm is cancel (i.e. "cancel the test run").

ASSERT is not used to avoid confusion with the assert included in the C standard library.  CppUnit utilizes ASSERT for test or process fatal errors (later if C++ exceptions not enabled).  gtest utilizes ASSERT for test fatal errors.
CHECK is not used.  boost::test, UnitTest++, and CppUnitLite utilize CHECK for continuable errors.
ENSURE is not used as it is the post-condition assert commonly used in design-by-contract.  tut utlizes ensure for test fatal errors.
EXPECT is not used.  gtest utilizes EXPECT for continuable errors.
IS is not used.  Aeryn utilizes IS for process fatal errors.
REQUIRE is not used as it is the pre-condition assert commonly used in design-by-contract.  boost::test utilizes REQUIRE for test fatal errors.
*/

#define VERIFY G42CORE_TEST_IF_NOT_REPORT

#ifdef G42CORE_TEST_IF_NOT_REPORT_ONLY
#define CERTIFY G42CORE_TEST_IF_NOT_REPORT_ONLY
#endif

#ifdef G42CORE_TEST_IF_NOT_REPORT_ABORT_TEST
#define CONTINUE G42CORE_TEST_IF_NOT_REPORT_ABORT_TEST
#endif

#ifdef G42CORE_TEST_IF_NOT_REPORT_ABORT_GROUP
#define APPROVE G42CORE_TEST_IF_NOT_REPORT_ABORT_GROUP
#endif

#ifdef G42CORE_TEST_IF_NOT_REPORT_ABORT_PROCESS
#define ALLOW G42CORE_TEST_IF_NOT_REPORT_ABORT_PROCESS
#endif

#ifdef G42CORE_TEST_IF_NOT_REPORT_ABORT_RUN
#define CONFIRM G42CORE_TEST_IF_NOT_REPORT_ABORT_RUN
#endif

#endif // G42CORE_HG_CFAAB4B4A0AD4258B527600BA93F724E
