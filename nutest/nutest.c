#include "nutest.h"

void register_test_case(TestCase *test_case) {
    // Find or create the test suite
    TestSuite *suite = NULL;
    for (size_t i = 0; i < test_registry.suite_count; i++) {
        if (strcmp(test_registry.suites[i].name, test_case->suite_name) == 0) {
            suite = &test_registry.suites[i];
            break;
        }
    }

    if (!suite) {
        // Create new suite
        test_registry.suite_count++;
        test_registry.suites =
            realloc(test_registry.suites,
                    test_registry.suite_count * sizeof(TestSuite));
        suite = &test_registry.suites[test_registry.suite_count - 1];
        *suite = (TestSuite){test_case->suite_name, NULL, 0, NULL};
    }

    // Add test to suite
    suite->test_count++;
    suite->tests = realloc(suite->tests, suite->test_count * sizeof(TestCase));
    suite->tests[suite->test_count - 1] = *test_case;
}

int RUN_ALL_TESTS(void) {
    printf("[==========] Running %zu test suites\n", test_registry.suite_count);

    size_t total_tests = 0;
    size_t total_passed = 0;
    size_t total_failed = 0;
    size_t total_skipped = 0;
    size_t total_errors = 0;

    for (size_t i = 0; i < test_registry.suite_count; i++) {
        TestSuite *suite = &test_registry.suites[i];
        printf(
            "[----------] %zu tests from %s\n", suite->test_count, suite->name);

        size_t suite_passed = 0;
        size_t suite_failed = 0;
        size_t suite_skipped = 0;
        size_t suite_errors = 0;

        for (size_t j = 0; j < suite->test_count; j++) {
            TestCase *test = &suite->tests[j];
            printf("[ RUN      ] %s.%s\n", suite->name, test->name);

            TestResult result = test->function();

            switch (result) {
            case TEST_PASS:
                printf("[       OK ] %s.%s\n", suite->name, test->name);
                suite_passed++;
                break;
            case TEST_FAIL:
                printf("[  FAILED  ] %s.%s\n", suite->name, test->name);
                suite_failed++;
                break;
            case TEST_SKIP:
                printf("[  SKIPPED ] %s.%s\n", suite->name, test->name);
                suite_skipped++;
                break;
            case TEST_ERROR:
                printf("[  ERROR   ] %s.%s\n", suite->name, test->name);
                suite_errors++;
                break;
            }
        }

        printf("[----------] %zu tests from %s (%zu ms total)\n\n",
               suite->test_count,
               suite->name,
               0); // Time tracking can be added

        total_tests += suite->test_count;
        total_passed += suite_passed;
        total_failed += suite_failed;
        total_skipped += suite_skipped;
        total_errors += suite_errors;
    }

    printf("[==========] %zu tests from %zu test suites ran.\n",
           total_tests,
           test_registry.suite_count);
    printf("[  PASSED  ] %zu tests.\n", total_passed);
    if (total_failed > 0) {
        printf("[  FAILED  ] %zu tests.\n", total_failed);
    }
    if (total_skipped > 0) {
        printf("[  SKIPPED ] %zu tests.\n", total_skipped);
    }
    if (total_errors > 0) {
        printf("[  ERRORS  ] %zu tests.\n", total_errors);
    }

    return (total_failed == 0 && total_errors == 0) ? EXIT_SUCCESS
                                                    : EXIT_FAILURE;
}
