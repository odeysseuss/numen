#include "matrix/mat2d.h"
#include "utils/errors.h"
#include "nutest.h"

TEST(Mat2Tests, Mat2Init) {
    // clang-format off
    nml_t test_arr[4] = {1.0, 0.0,
                         0.0, 1.0};
    // clang-format on
    Mat2 m;

    ASSERT_EQ(Mat2Init(test_arr, &m), NML_SUCCESS);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (i == j) {
                ASSERT_DOUBLE_EQ(m.Elements[i * 2 + j], 1.0);
            } else {
                ASSERT_DOUBLE_EQ(m.Elements[i * 2 + j], 0.0);
            }
        }
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2InitZero) {
    Mat2 m;
    ASSERT_EQ(Mat2InitZero(&m), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(m.Elements[i], 0.0);
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2Diagonal) {
    Mat2 m;
    ASSERT_EQ(Mat2Diagonal(5.0, &m), NML_SUCCESS);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (i == j) {
                ASSERT_DOUBLE_EQ(m.Elements[i * 2 + j], 5.0);
            } else {
                ASSERT_DOUBLE_EQ(m.Elements[i * 2 + j], 0.0);
            }
        }
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2Identity) {
    Mat2 m;
    ASSERT_EQ(Mat2Identity(&m), NML_SUCCESS);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (i == j) {
                ASSERT_DOUBLE_EQ(m.Elements[i * 2 + j], 1.0);
            } else {
                ASSERT_DOUBLE_EQ(m.Elements[i * 2 + j], 0.0);
            }
        }
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2Add) {
    // clang-format off
    nml_t arr1[4] = {1.0, 2.0,
                     3.0, 4.0};
    nml_t arr2[4] = {4.0, 3.0,
                     2.0, 1.0};
    // clang-format on
    Mat2 m1, m2, result;
    Mat2Init(arr1, &m1);
    Mat2Init(arr2, &m2);

    ASSERT_EQ(Mat2Add(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], arr1[i] + arr2[i]);
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2Sub) {
    // clang-format off
    nml_t arr1[4] = {1.0, 2.0,
                     3.0, 4.0};
    nml_t arr2[4] = {4.0, 3.0,
                     2.0, 1.0};
    // clang-format on
    Mat2 m1, m2, result;
    Mat2Init(arr1, &m1);
    Mat2Init(arr2, &m2);

    ASSERT_EQ(Mat2Sub(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], arr1[i] - arr2[i]);
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2Hadamard) {
    // clang-format off
    nml_t arr1[4] = {1.0, 2.0,
                     3.0, 4.0};
    nml_t arr2[4] = {4.0, 3.0,
                     2.0, 1.0};
    // clang-format on
    Mat2 m1, m2, result;
    Mat2Init(arr1, &m1);
    Mat2Init(arr2, &m2);

    ASSERT_EQ(Mat2Hadamard(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], arr1[i] * arr2[i]);
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2Scale) {
    // clang-format off
    nml_t arr1[4] = {1.0, 2.0,
                     3.0, 4.0};
    // clang-format on
    Mat2 m1, result;
    Mat2Init(arr1, &m1);
    nml_t scale = 2.5;

    ASSERT_EQ(Mat2Scale(&m1, scale, &result), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], arr1[i] * scale);
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2Negate) {
    // clang-format off
    nml_t arr1[4] = {1.0, 2.0,
                     3.0, 4.0};
    // clang-format on
    Mat2 m1, result;
    Mat2Init(arr1, &m1);

    ASSERT_EQ(Mat2Negate(&m1, &result), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], -arr1[i]);
    }
    return TEST_PASS;
}

int main(void) {
    return RUN_ALL_TESTS();
}
