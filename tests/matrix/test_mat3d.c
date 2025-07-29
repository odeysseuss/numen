#include "matrix/mat3d.h"
#include "utils/errors.h"
#include "nutest.h"

TEST(Mat3Tests, Mat3Init) {
    // clang-format off
    nml_t test_arr[9] = {1.0, 0.0, 0.0,
                         0.0, 1.0, 0.0,
                         0.0, 0.0, 1.0};
    // clang-format on
    Mat3 m;

    ASSERT_EQ(Mat3Init(test_arr, &m), NML_SUCCESS);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                ASSERT_DOUBLE_EQ(m.Elements[i * 3 + j], 1.0);
            } else {
                ASSERT_DOUBLE_EQ(m.Elements[i * 3 + j], 0.0);
            }
        }
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3InitZero) {
    Mat3 m;
    ASSERT_EQ(Mat3InitZero(&m), NML_SUCCESS);
    for (int i = 0; i < 9; i++) {
        ASSERT_DOUBLE_EQ(m.Elements[i], 0.0);
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3Diagonal) {
    Mat3 m;
    ASSERT_EQ(Mat3Diagonal(5.0, &m), NML_SUCCESS);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                ASSERT_DOUBLE_EQ(m.Elements[i * 3 + j], 5.0);
            } else {
                ASSERT_DOUBLE_EQ(m.Elements[i * 3 + j], 0.0);
            }
        }
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3Identity) {
    Mat3 m;
    ASSERT_EQ(Mat3Identity(&m), NML_SUCCESS);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                ASSERT_DOUBLE_EQ(m.Elements[i * 3 + j], 1.0);
            } else {
                ASSERT_DOUBLE_EQ(m.Elements[i * 3 + j], 0.0);
            }
        }
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3Add) {
    // clang-format off
    nml_t arr1[9] = {1.0, 2.0, 3.0,
                     4.0, 5.0, 6.0,
                     7.0, 8.0, 9.0};
    nml_t arr2[9] = {9.0, 8.0, 7.0,
                     6.0, 5.0, 4.0,
                     3.0, 2.0, 1.0};
    // clang-format on
    Mat3 m1, m2, result;
    Mat3Init(arr1, &m1);
    Mat3Init(arr2, &m2);

    ASSERT_EQ(Mat3Add(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 9; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], arr1[i] + arr2[i]);
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3Sub) {
    // clang-format off
    nml_t arr1[9] = {1.0, 2.0, 3.0,
                     4.0, 5.0, 6.0,
                     7.0, 8.0, 9.0};
    nml_t arr2[9] = {9.0, 8.0, 7.0,
                     6.0, 5.0, 4.0,
                     3.0, 2.0, 1.0};
    // clang-format on
    Mat3 m1, m2, result;
    Mat3Init(arr1, &m1);
    Mat3Init(arr2, &m2);

    ASSERT_EQ(Mat3Sub(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 9; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], arr1[i] - arr2[i]);
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3Hadamard) {
    // clang-format off
    nml_t arr1[9] = {1.0, 2.0, 3.0,
                     4.0, 5.0, 6.0,
                     7.0, 8.0, 9.0};
    nml_t arr2[9] = {9.0, 8.0, 7.0,
                     6.0, 5.0, 4.0,
                     3.0, 2.0, 1.0};
    // clang-format on
    Mat3 m1, m2, result;
    Mat3Init(arr1, &m1);
    Mat3Init(arr2, &m2);

    ASSERT_EQ(Mat3Hadamard(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 9; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], arr1[i] * arr2[i]);
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3Scale) {
    // clang-format off
    nml_t arr1[9] = {1.0, 2.0, 3.0,
                     4.0, 5.0, 6.0,
                     7.0, 8.0, 9.0};
    // clang-format on
    Mat3 m1, result;
    Mat3Init(arr1, &m1);
    nml_t scale = 2.5;

    ASSERT_EQ(Mat3Scale(&m1, scale, &result), NML_SUCCESS);
    for (int i = 0; i < 9; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], arr1[i] * scale);
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3Negate) {
    // clang-format off
    nml_t arr1[9] = {1.0, 2.0, 3.0,
                     4.0, 5.0, 6.0,
                     7.0, 8.0, 9.0};
    // clang-format on
    Mat3 m1, result;
    Mat3Init(arr1, &m1);

    ASSERT_EQ(Mat3Negate(&m1, &result), NML_SUCCESS);
    for (int i = 0; i < 9; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], -arr1[i]);
    }
    return TEST_PASS;
}

int main(void) {
    return RUN_ALL_TESTS();
}
