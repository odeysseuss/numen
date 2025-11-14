#include "matrix/mat2d.h"
#include "utils/errors.h"
#include "nutest.h"

TEST(Mat2Tests, Mat2Init) {
    // clang-format off
    nml_t test_arr[4] = {1.0, 2.0,  // Column 0
                         3.0, 4.0}; // Column 1
    nml_t expected[4] = {1.0, 2.0,
                         3.0, 4.0};
    // clang-format on
    Mat2 m;
    ASSERT_EQ(mat2Init(test_arr, &m), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(m.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2InitZero) {
    nml_t expected[4] = {0};
    Mat2 m;
    ASSERT_EQ(mat2InitZero(&m), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(m.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2Diagonal) {
    nml_t expected[4] = {5.0, 0.0, 0.0, 5.0};
    Mat2 m;
    ASSERT_EQ(mat2Diagonal(5.0, &m), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(m.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2Identity) {
    nml_t expected[4] = {1.0, 0.0, 0.0, 1.0};
    Mat2 m;
    ASSERT_EQ(mat2Identity(&m), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(m.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2Add) {
    // clang-format off
    nml_t arr1[4] = {1.0, 3.0,
                     2.0, 4.0};
    nml_t arr2[4] = {4.0, 2.0,
                     3.0, 1.0};
    nml_t expected[4] = {5.0, 5.0,
                         5.0, 5.0};
    // clang-format on
    Mat2 m1, m2, result;
    mat2Init(arr1, &m1);
    mat2Init(arr2, &m2);

    ASSERT_EQ(mat2Add(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(result.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2Sub) {
    // clang-format off
    nml_t arr1[4] = {1.0, 3.0,
                     2.0, 4.0};
    nml_t arr2[4] = {4.0, 2.0,
                     3.0, 1.0};
    nml_t expected[4] = {-3.0, 1.0,
                         -1.0, 3.0};
    // clang-format on
    Mat2 m1, m2, result;
    mat2Init(arr1, &m1);
    mat2Init(arr2, &m2);

    ASSERT_EQ(mat2Sub(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(result.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2Scale) {
    // clang-format off
    nml_t arr1[4] = {1.0, 3.0,
                     2.0, 4.0};
    nml_t expected[4] = {2.5, 7.5,
                         5.0, 10.0};
    // clang-format on
    Mat2 m1, result;
    mat2Init(arr1, &m1);
    nml_t scale = 2.5;

    ASSERT_EQ(mat2Scale(&m1, scale, &result), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(result.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2Negate) {
    // clang-format off
    nml_t arr1[4] = {1.0, 3.0,
                     2.0, 4.0};
    nml_t expected[4] = {-1.0, -3.0,
                         -2.0, -4.0};
    // clang-format on
    Mat2 m1, result;
    mat2Init(arr1, &m1);

    ASSERT_EQ(mat2Negate(&m1, &result), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(result.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2Hadamard) {
    // clang-format off
    nml_t arr1[4] = {1.0, 3.0,
                     2.0, 4.0};
    nml_t arr2[4] = {4.0, 2.0,
                     3.0, 1.0};
    nml_t expected[4] = {4.0, 6.0,
                         6.0, 4.0};
    // clang-format on
    Mat2 m1, m2, result;
    mat2Init(arr1, &m1);
    mat2Init(arr2, &m2);

    ASSERT_EQ(mat2Hadamard(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(result.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2MulVec2) {
    // clang-format off
    nml_t arr[4] = {1.0, 3.0,
                     2.0, 4.0};
    nml_t expected[2] = {6.0, 14.0};
    // clang-format on
    Mat2 m;
    Vec2 v, result;
    mat2Init(arr, &m);
    vec2Init(2.0, 2.0, &v);

    ASSERT_EQ(mat2MulVec2(&m, &v, &result), NML_SUCCESS);
    for (int i = 0; i < 2; i++) {
        ASSERT_DOUBLE_EQ(result.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat2Tests, Mat2MulMat2) {
    // clang-format off
    nml_t arr1[4] = {1.0, 3.0,
                     2.0, 4.0};
    nml_t arr2[4] = {4.0, 2.0,
                     3.0, 1.0};
    nml_t expected[4] = {8.0, 20.0,
                         5.0, 13.0};
    // clang-format on
    Mat2 m1, m2, result;
    mat2Init(arr1, &m1);
    mat2Init(arr2, &m2);

    ASSERT_EQ(mat2MulMat2(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(result.elems[i], expected[i]);
    }
    return TEST_PASS;
}

int main(void) {
    return RUN_ALL_TESTS();
}
