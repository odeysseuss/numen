#include "matrix/mat4d.h"
#include "utils/errors.h"
#include "nutest.h"

TEST(Mat4Tests, Mat4Init) {
    // clang-format off
    nml_t test_arr[16] = {1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0,
                          0.0, 0.0, 0.0, 1.0};
    nml_t expected[16] = {1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0,
                          0.0, 0.0, 0.0, 1.0};
    // clang-format on
    Mat4 m;
    ASSERT_EQ(mat4Init(test_arr, &m), NML_SUCCESS);
    for (int i = 0; i < 16; i++) {
        ASSERT_DOUBLE_EQ(m.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4InitZero) {
    nml_t expected[16] = {0};
    Mat4 m;
    ASSERT_EQ(mat4InitZero(&m), NML_SUCCESS);
    for (int i = 0; i < 16; i++) {
        ASSERT_DOUBLE_EQ(m.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4Diagonal) {
    // clang-format off
    nml_t expected[16] = {5.0, 0.0, 0.0, 0.0,
                          0.0, 5.0, 0.0, 0.0,
                          0.0, 0.0, 5.0, 0.0,
                          0.0, 0.0, 0.0, 5.0};
    // clang-format on
    Mat4 m;
    ASSERT_EQ(mat4Diagonal(5.0, &m), NML_SUCCESS);
    for (int i = 0; i < 16; i++) {
        ASSERT_DOUBLE_EQ(m.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4Identity) {
    // clang-format off
    nml_t expected[16] = {1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0,
                          0.0, 0.0, 0.0, 1.0};
    // clang-format on
    Mat4 m;
    ASSERT_EQ(mat4Identity(&m), NML_SUCCESS);
    for (int i = 0; i < 16; i++) {
        ASSERT_DOUBLE_EQ(m.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4Add) {
    // clang-format off
    nml_t arr1[16] = {1.0, 5.0, 9.0, 13.0,
                      2.0, 6.0, 10.0, 14.0,
                      3.0, 7.0, 11.0, 15.0,
                      4.0, 8.0, 12.0, 16.0};
    nml_t arr2[16] = {16.0, 12.0, 8.0, 4.0,
                      15.0, 11.0, 7.0, 3.0,
                      14.0, 10.0, 6.0, 2.0,
                      13.0, 9.0, 5.0, 1.0};
    nml_t expected[16] = {17.0, 17.0, 17.0, 17.0,
                          17.0, 17.0, 17.0, 17.0,
                          17.0, 17.0, 17.0, 17.0,
                          17.0, 17.0, 17.0, 17.0};
    // clang-format on
    Mat4 m1, m2, result;
    mat4Init(arr1, &m1);
    mat4Init(arr2, &m2);

    ASSERT_EQ(mat4Add(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 16; i++) {
        ASSERT_DOUBLE_EQ(result.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4Sub) {
    // clang-format off
    nml_t arr1[16] = {1.0, 5.0, 9.0, 13.0,
                      2.0, 6.0, 10.0, 14.0,
                      3.0, 7.0, 11.0, 15.0,
                      4.0, 8.0, 12.0, 16.0};
    nml_t arr2[16] = {16.0, 12.0, 8.0, 4.0,
                      15.0, 11.0, 7.0, 3.0,
                      14.0, 10.0, 6.0, 2.0,
                      13.0, 9.0, 5.0, 1.0};
    nml_t expected[16] = {-15.0, -7.0, 1.0, 9.0,
                          -13.0, -5.0, 3.0, 11.0,
                          -11.0, -3.0, 5.0, 13.0,
                          -9.0, -1.0, 7.0, 15.0};
    // clang-format on
    Mat4 m1, m2, result;
    mat4Init(arr1, &m1);
    mat4Init(arr2, &m2);

    ASSERT_EQ(mat4Sub(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 16; i++) {
        ASSERT_DOUBLE_EQ(result.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4Scale) {
    // clang-format off
    nml_t arr1[16] = {1.0, 5.0, 9.0, 13.0,
                      2.0, 6.0, 10.0, 14.0,
                      3.0, 7.0, 11.0, 15.0,
                      4.0, 8.0, 12.0, 16.0};
    nml_t expected[16] = {2.5, 12.5, 22.5, 32.5,
                          5.0, 15.0, 25.0, 35.0,
                          7.5, 17.5, 27.5, 37.5,
                          10.0, 20.0, 30.0, 40.0};
    // clang-format on
    Mat4 m1, result;
    mat4Init(arr1, &m1);
    nml_t scale = 2.5;

    ASSERT_EQ(mat4Scale(&m1, scale, &result), NML_SUCCESS);
    for (int i = 0; i < 16; i++) {
        ASSERT_DOUBLE_EQ(result.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4Negate) {
    // clang-format off
    nml_t arr1[16] = {1.0, 5.0, 9.0, 13.0,
                      2.0, 6.0, 10.0, 14.0,
                      3.0, 7.0, 11.0, 15.0,
                      4.0, 8.0, 12.0, 16.0};
    nml_t expected[16] = {-1.0, -5.0, -9.0, -13.0,
                          -2.0, -6.0, -10.0, -14.0,
                          -3.0, -7.0, -11.0, -15.0,
                          -4.0, -8.0, -12.0, -16.0};
    // clang-format on
    Mat4 m1, result;
    mat4Init(arr1, &m1);

    ASSERT_EQ(mat4Negate(&m1, &result), NML_SUCCESS);
    for (int i = 0; i < 16; i++) {
        ASSERT_DOUBLE_EQ(result.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4Hadamard) {
    // clang-format off
    nml_t arr1[16] = {1.0, 5.0, 9.0, 13.0,
                      2.0, 6.0, 10.0, 14.0,
                      3.0, 7.0, 11.0, 15.0,
                      4.0, 8.0, 12.0, 16.0};
    nml_t arr2[16] = {16.0, 12.0, 8.0, 4.0,
                      15.0, 11.0, 7.0, 3.0,
                      14.0, 10.0, 6.0, 2.0,
                      13.0, 9.0, 5.0, 1.0};
    nml_t expected[16] = {16.0, 60.0, 72.0, 52.0,
                          30.0, 66.0, 70.0, 42.0,
                          42.0, 70.0, 66.0, 30.0,
                          52.0, 72.0, 60.0, 16.0};
    // clang-format on
    Mat4 m1, m2, result;
    mat4Init(arr1, &m1);
    mat4Init(arr2, &m2);

    ASSERT_EQ(mat4Hadamard(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 16; i++) {
        ASSERT_DOUBLE_EQ(result.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4MulVec4) {
    // clang-format off
    nml_t mat_arr[16] = {1.0, 5.0, 9.0, 13.0,
                         2.0, 6.0, 10.0, 14.0,
                         3.0, 7.0, 11.0, 15.0,
                         4.0, 8.0, 12.0, 16.0};
    nml_t expected[4] = {30.0, 70.0, 110.0, 150.0};
    // clang-format on
    Mat4 m;
    Vec4 v, result;
    mat4Init(mat_arr, &m);
    vec4Init(1.0, 2.0, 3.0, 4.0, &v);

    ASSERT_EQ(mat4MulVec4(&m, &v, &result), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        ASSERT_DOUBLE_EQ(result.elems[i], expected[i]);
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4MulMat4) {
    // clang-format off
    nml_t arr1[16] = {1.0, 5.0, 9.0, 13.0,
                      2.0, 6.0, 10.0, 14.0,
                      3.0, 7.0, 11.0, 15.0,
                      4.0, 8.0, 12.0, 16.0};
    nml_t arr2[16] = {16.0, 12.0, 8.0, 4.0,
                      15.0, 11.0, 7.0, 3.0,
                      14.0, 10.0, 6.0, 2.0,
                      13.0, 9.0, 5.0, 1.0};
    nml_t expected[16] = {80.0, 240.0, 400.0, 560.0,
                          70.0, 214.0, 358.0, 502.0,
                          60.0, 188.0, 316.0, 444.0,
                          50.0, 162.0, 274.0, 386.0};
    // clang-format on
    Mat4 m1, m2, result;
    mat4Init(arr1, &m1);
    mat4Init(arr2, &m2);

    ASSERT_EQ(mat4MulMat4(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 16; i++) {
        ASSERT_DOUBLE_EQ(result.elems[i], expected[i]);
    }
    return TEST_PASS;
}

int main(void) {
    return RUN_ALL_TESTS();
}
