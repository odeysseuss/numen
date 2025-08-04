#include "matrix/mat3d.h"
#include "utils/errors.h"
#include "nutest.h"

TEST(Mat3Tests, Mat3Init) {
    // clang-format off
    nml_t test_arr[9] = {1.0, 0.0, 0.0,  // Column 0
                         0.0, 1.0, 0.0,  // Column 1
                         0.0, 0.0, 1.0}; // Column 2
    nml_t expected[9] = {1.0, 0.0, 0.0,
                         0.0, 1.0, 0.0,
                         0.0, 0.0, 1.0};
    // clang-format on
    Mat3 m;
    ASSERT_EQ(Mat3Init(test_arr, &m), NML_SUCCESS);
    for (int i = 0; i < 9; i++) {
        ASSERT_DOUBLE_EQ(m.Elements[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3InitZero) {
    nml_t expected[9] = {0};
    Mat3 m;
    ASSERT_EQ(Mat3InitZero(&m), NML_SUCCESS);
    for (int i = 0; i < 9; i++) {
        ASSERT_DOUBLE_EQ(m.Elements[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3Diagonal) {
    nml_t expected[9] = {5.0, 0.0, 0.0,
                         0.0, 5.0, 0.0,
                         0.0, 0.0, 5.0};
    Mat3 m;
    ASSERT_EQ(Mat3Diagonal(5.0, &m), NML_SUCCESS);
    for (int i = 0; i < 9; i++) {
        ASSERT_DOUBLE_EQ(m.Elements[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3Identity) {
    nml_t expected[9] = {1.0, 0.0, 0.0,
                         0.0, 1.0, 0.0,
                         0.0, 0.0, 1.0};
    Mat3 m;
    ASSERT_EQ(Mat3Identity(&m), NML_SUCCESS);
    for (int i = 0; i < 9; i++) {
        ASSERT_DOUBLE_EQ(m.Elements[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3Add) {
    // clang-format off
    nml_t arr1[9] = {1.0, 4.0, 7.0,
                     2.0, 5.0, 8.0,
                     3.0, 6.0, 9.0};
    nml_t arr2[9] = {9.0, 6.0, 3.0,
                     8.0, 5.0, 2.0,
                     7.0, 4.0, 1.0};
    nml_t expected[9] = {10.0, 10.0, 10.0,
                         10.0, 10.0, 10.0,
                         10.0, 10.0, 10.0};
    // clang-format on
    Mat3 m1, m2, result;
    Mat3Init(arr1, &m1);
    Mat3Init(arr2, &m2);

    ASSERT_EQ(Mat3Add(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 9; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3Sub) {
    // clang-format off
    nml_t arr1[9] = {1.0, 4.0, 7.0,
                     2.0, 5.0, 8.0,
                     3.0, 6.0, 9.0};
    nml_t arr2[9] = {9.0, 6.0, 3.0,
                     8.0, 5.0, 2.0,
                     7.0, 4.0, 1.0};
    nml_t expected[9] = {-8.0, -2.0, 4.0,
                         -6.0, 0.0, 6.0,
                         -4.0, 2.0, 8.0};
    // clang-format on
    Mat3 m1, m2, result;
    Mat3Init(arr1, &m1);
    Mat3Init(arr2, &m2);

    ASSERT_EQ(Mat3Sub(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 9; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3Scale) {
    // clang-format off
    nml_t arr1[9] = {1.0, 4.0, 7.0,
                     2.0, 5.0, 8.0,
                     3.0, 6.0, 9.0};
    nml_t expected[9] = {2.5, 10.0, 17.5,
                         5.0, 12.5, 20.0,
                         7.5, 15.0, 22.5};
    // clang-format on
    Mat3 m1, result;
    Mat3Init(arr1, &m1);
    nml_t scale = 2.5;

    ASSERT_EQ(Mat3Scale(&m1, scale, &result), NML_SUCCESS);
    for (int i = 0; i < 9; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3Negate) {
    // clang-format off
    nml_t arr1[9] = {1.0, 4.0, 7.0,
                     2.0, 5.0, 8.0,
                     3.0, 6.0, 9.0};
    nml_t expected[9] = {-1.0, -4.0, -7.0,
                         -2.0, -5.0, -8.0,
                         -3.0, -6.0, -9.0};
    // clang-format on
    Mat3 m1, result;
    Mat3Init(arr1, &m1);

    ASSERT_EQ(Mat3Negate(&m1, &result), NML_SUCCESS);
    for (int i = 0; i < 9; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3Hadamard) {
    // clang-format off
    nml_t arr1[9] = {1.0, 4.0, 7.0,
                     2.0, 5.0, 8.0,
                     3.0, 6.0, 9.0};
    nml_t arr2[9] = {9.0, 6.0, 3.0,
                     8.0, 5.0, 2.0,
                     7.0, 4.0, 1.0};
    nml_t expected[9] = {9.0, 24.0, 21.0,
                         16.0, 25.0, 16.0,
                         21.0, 24.0, 9.0};
    // clang-format on
    Mat3 m1, m2, result;
    Mat3Init(arr1, &m1);
    Mat3Init(arr2, &m2);

    ASSERT_EQ(Mat3Hadamard(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 9; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3MulVec3) {
    // clang-format off
    nml_t mat_arr[9] = {1.0, 4.0, 7.0,
                        2.0, 5.0, 8.0,
                        3.0, 6.0, 9.0};
    nml_t expected[3] = {20.0, 47.0, 74.0};
    // clang-format on
    Mat3 m;
    Vec3 v, result;
    Mat3Init(mat_arr, &m);
    Vec3Init(2.0, 3.0, 4.0, &v);

    ASSERT_EQ(Mat3MulVec3(&m, &v, &result), NML_SUCCESS);
    for (int i = 0; i < 3; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat3Tests, Mat3MulMat3) {
    // clang-format off
    // Column-major inputs
    nml_t arr1[9] = {1.0, 4.0, 7.0,  // Column 0
                     2.0, 5.0, 8.0,  // Column 1
                     3.0, 6.0, 9.0}; // Column 2
    nml_t arr2[9] = {9.0, 6.0, 3.0,  // Column 0
                     8.0, 5.0, 2.0,  // Column 1
                     7.0, 4.0, 1.0}; // Column 2
    // Correct column-major expected result
    nml_t expected[9] = {30.0, 84.0, 138.0,  // Column 0
                         24.0, 69.0, 114.0,  // Column 1
                         18.0, 54.0, 90.0};  // Column 2
    // clang-format on
    Mat3 m1, m2, result;
    Mat3Init(arr1, &m1);
    Mat3Init(arr2, &m2);

    ASSERT_EQ(Mat3MulMat3(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 9; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], expected[i]);
    }
    return TEST_PASS;
}

int main(void) {
    return RUN_ALL_TESTS();
}
