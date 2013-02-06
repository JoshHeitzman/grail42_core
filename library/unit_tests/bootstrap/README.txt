The following tests all require TUT.  Some require gtest and/or CppUTest.

  bootstrap010 - unit tests for the sparse vector with list, the common output stream reporter, the TUT callback adapter, the TUT internal API adapters.
  bootstrap015 - unit tests for the normalized API and the TUT API and main adapters.
  bootstrap020 - unit tests for gtest adapters and the thread class.
  bootstrap025 - unit tests for CppUTest adapters.
  bootstrap030 - unit tests for the thread functors for TUT, gtest, and CppUTest.

The following tests require TUT, gtest, and CppUTest.

  bootstrap050 - unit tests for the atomic class, test part classes, test_executor_single_thread_without_test_part_validation, and test_part_registry.
  bootstrap055 - unit tests for test_part_registrar.

The following tests do not require TUT, gtest, or CppUTest.

  bootstrap060 - unit tests for grail42's own implementation common API utilizing test_executor_single_thread_without_test_part_validation.
  bootstrap065 - unit tests for test_part_combiner, test_part_executor, tests_executor, test_executor_multiple_threads, and test_execution.
  bootstrap070 - unit tests for grail42's own implementation common API utilizing test_execution rather than test_executor_single_thread_without_test_part_validation.