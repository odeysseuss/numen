#ifndef __NUTEST_H__
#define __NUTEST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <float.h>

// test result codes
typedef enum { TEST_PASS, TEST_FAIL, TEST_SKIP, TEST_ERROR } TestResult;

// test case function type
typedef TestResult (*TestFunc)(void);

// test case structure
typedef struct {
    const char *name;
    TestFunc function;
    const char *suite_name;
    const char *description;
} TestCase;

// test suite structure
typedef struct {
    const char *name;
    TestCase *tests;
    size_t test_count;
    const char *description;
} TestSuite;

// test registry
typedef struct {
    TestSuite *suites;
    size_t suite_count;
} TestRegistry;

// global test registry
static TestRegistry test_registry = {NULL, 0};

#define EXPECT_TRUE(condition)                                             \
    do {                                                                   \
        if (!(condition)) {                                                \
            fprintf(stderr,                                                \
                    "[  FAILED ] %s:%d: Expected: %s evaluates to true\n", \
                    __FILE__,                                              \
                    __LINE__,                                              \
                    #condition);                                           \
            return TEST_FAIL;                                              \
        }                                                                  \
    } while (0)

#define EXPECT_FALSE(condition)                                             \
    do {                                                                    \
        if (condition) {                                                    \
            fprintf(stderr,                                                 \
                    "[  FAILED ] %s:%d: Expected: %s evaluates to false\n", \
                    __FILE__,                                               \
                    __LINE__,                                               \
                    #condition);                                            \
            return TEST_FAIL;                                               \
        }                                                                   \
    } while (0)

#define EXPECT_EQ(expected, actual)                                       \
    do {                                                                  \
        if ((expected) != (actual)) {                                     \
            fprintf(stderr,                                               \
                    "[  FAILED ] %s:%d: Expected: %s == %s (%d vs %d)\n", \
                    __FILE__,                                             \
                    __LINE__,                                             \
                    #expected,                                            \
                    #actual,                                              \
                    (int)(expected),                                      \
                    (int)(actual));                                       \
            return TEST_FAIL;                                             \
        }                                                                 \
    } while (0)

#define EXPECT_NE(val1, val2)                                                \
    do {                                                                     \
        if ((val1) == (val2)) {                                              \
            fprintf(stderr,                                                  \
                    "[  FAILED ] %s:%d: Expected: %s != %s (both are %d)\n", \
                    __FILE__,                                                \
                    __LINE__,                                                \
                    #val1,                                                   \
                    #val2,                                                   \
                    (int)(val1));                                            \
            return TEST_FAIL;                                                \
        }                                                                    \
    } while (0)

#define EXPECT_FLOAT_EQ(expected, actual)                                   \
    do {                                                                    \
        float _expected = (expected);                                       \
        float _actual = (actual);                                           \
        float _diff = fabsf(_expected - _actual);                           \
        if (_diff > FLT_EPSILON) {                                          \
            fprintf(stderr,                                                 \
                    "[  FAILED ] %s:%d: Expected: %s == %s (%.9g vs %.9g, " \
                    "diff %.9g)\n",                                         \
                    __FILE__,                                               \
                    __LINE__,                                               \
                    #expected,                                              \
                    #actual,                                                \
                    _expected,                                              \
                    _actual,                                                \
                    _diff);                                                 \
            return TEST_FAIL;                                               \
        }                                                                   \
    } while (0)

#define EXPECT_DOUBLE_EQ(expected, actual)                                    \
    do {                                                                      \
        double _expected = (expected);                                        \
        double _actual = (actual);                                            \
        double _diff = fabs(_expected - _actual);                             \
        if (_diff > DBL_EPSILON) {                                            \
            fprintf(stderr,                                                   \
                    "[  FAILED ] %s:%d: Expected: %s == %s (%.17g vs %.17g, " \
                    "diff %.17g)\n",                                          \
                    __FILE__,                                                 \
                    __LINE__,                                                 \
                    #expected,                                                \
                    #actual,                                                  \
                    _expected,                                                \
                    _actual,                                                  \
                    _diff);                                                   \
            return TEST_FAIL;                                                 \
        }                                                                     \
    } while (0)

#define EXPECT_NEAR(expected, actual, tolerance)                              \
    do {                                                                      \
        double _expected = (expected);                                        \
        double _actual = (actual);                                            \
        double _diff = fabs(_expected - _actual);                             \
        if (_diff > (tolerance)) {                                            \
            fprintf(stderr,                                                   \
                    "[  FAILED ] %s:%d: Expected: %s ~= %s (%.17g vs %.17g, " \
                    "diff %.17g > tol %.17g)\n",                              \
                    __FILE__,                                                 \
                    __LINE__,                                                 \
                    #expected,                                                \
                    #actual,                                                  \
                    _expected,                                                \
                    _actual,                                                  \
                    _diff,                                                    \
                    (tolerance));                                             \
            return TEST_FAIL;                                                 \
        }                                                                     \
    } while (0)

// test registration macros
#define TEST_F(test_suite_name, test_name)                          \
    static TestResult test_suite_name##_##test_name(void);          \
    __attribute__((constructor)) static void                        \
    register_##test_suite_name##_##test_name(void) {                \
        static TestCase test_case = {#test_name,                    \
                                     test_suite_name##_##test_name, \
                                     #test_suite_name,              \
                                     NULL};                         \
        register_test_case(&test_case);                             \
    }                                                               \
    static TestResult test_suite_name##_##test_name(void)

#define TEST(test_suite_name, test_name) TEST_F(test_suite_name, test_name)

#define TEST_F_DESC(test_suite_name, test_name, description)        \
    static TestResult test_suite_name##_##test_name(void);          \
    __attribute__((constructor)) static void                        \
    register_##test_suite_name##_##test_name(void) {                \
        static TestCase test_case = {#test_name,                    \
                                     test_suite_name##_##test_name, \
                                     #test_suite_name,              \
                                     description};                  \
        register_test_case(&test_case);                             \
    }                                                               \
    static TestResult test_suite_name##_##test_name(void)

// fixture support
#define FIXTURE_TEST(test_suite_name, test_name) \
    TEST_F(test_suite_name, test_name)

// test registration function
void register_test_case(TestCase *test_case);

// test runner
int RUN_ALL_TESTS(void);

// fixture support
#define FIXTURE(test_suite_name)                                        \
    typedef struct test_suite_name##_Fixture test_suite_name##_Fixture; \
    struct test_suite_name##_Fixture

#define SET_UP() static void SetUp(test_suite_name##_Fixture *fixture)

#define TEAR_DOWN() static void TearDown(test_suite_name##_Fixture *fixture)

#define FIXTURE_TEST_F(test_suite_name, test_name)                          \
    static TestResult test_suite_name##_##test_name##_Impl(                 \
        test_suite_name##_Fixture *fixture);                                \
    static TestResult test_suite_name##_##test_name(void) {                 \
        test_suite_name##_Fixture fixture;                                  \
        memset(&fixture, 0, sizeof(fixture));                               \
        SetUp(&fixture);                                                    \
        TestResult result = test_suite_name##_##test_name##_Impl(&fixture); \
        TearDown(&fixture);                                                 \
        return result;                                                      \
    }                                                                       \
    TEST_F(test_suite_name, test_name) {                                    \
        return test_suite_name##_##test_name();                             \
    }                                                                       \
    static TestResult test_suite_name##_##test_name##_Impl(                 \
        test_suite_name##_Fixture *fixture)

// skip test macro
#define SKIP() return TEST_SKIP

// performance measurement macros
#define BENCHMARK_START()                     \
    struct timespec _bench_start, _bench_end; \
    clock_gettime(CLOCK_MONOTONIC, &_bench_start)

#define BENCHMARK_END(name)                                                 \
    clock_gettime(CLOCK_MONOTONIC, &_bench_end);                            \
    double _bench_time = (_bench_end.tv_sec - _bench_start.tv_sec) +        \
                         (_bench_end.tv_nsec - _bench_start.tv_nsec) / 1e9; \
    printf("[ BENCHMARK ] %s: %.9f seconds\n", name, _bench_time)

#endif // !__NUTEST_H__
