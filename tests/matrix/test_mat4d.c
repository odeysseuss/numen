#include "matrix/mat4d.h"
#include "utils/errors.h"
#include "nutest.h"

TEST(Mat4Tests, Mat4Init) {
    // clang-format off
    nml_t test_arr[16] = {1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0,
                          0.0, 0.0, 0.0, 1.0};
    // clang-format on
    Mat4 m;

    ASSERT_EQ(Mat4Init(test_arr, &m), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                ASSERT_DOUBLE_EQ(m.Elements[i * 4 + j], 1.0);
            } else {
                ASSERT_DOUBLE_EQ(m.Elements[i * 4 + j], 0.0);
            }
        }
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4InitZero) {
    Mat4 m;
    ASSERT_EQ(Mat4InitZero(&m), NML_SUCCESS);
    for (int i = 0; i < 16; i++) {
        ASSERT_DOUBLE_EQ(m.Elements[i], 0.0);
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4Diagonal) {
    Mat4 m;
    ASSERT_EQ(Mat4Diagonal(5.0, &m), NML_SUCCESS);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                ASSERT_DOUBLE_EQ(m.Elements[i * 4 + j], 5.0);
            } else {
                ASSERT_DOUBLE_EQ(m.Elements[i * 4 + j], 0.0);
            }
        }
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4Identity) {
    Mat4 m;
    ASSERT_EQ(Mat4Identity(&m), NML_SUCCESS);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                ASSERT_DOUBLE_EQ(m.Elements[i * 4 + j], 1.0);
            } else {
                ASSERT_DOUBLE_EQ(m.Elements[i * 4 + j], 0.0);
            }
        }
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4Add) {
    // clang-format off
    nml_t arr1[16] = {1.0, 2.0, 3.0, 4.0,
                      5.0, 6.0, 7.0, 8.0,
                      9.0, 10.0, 11.0, 12.0,
                      13.0, 14.0, 15.0, 16.0};
    nml_t arr2[16] = {16.0, 15.0, 14.0, 13.0,
                      12.0, 11.0, 10.0, 9.0,
                      8.0, 7.0, 6.0, 5.0,
                      4.0, 3.0, 2.0, 1.0};
    // clang-format on
    Mat4 m1, m2, result;
    Mat4Init(arr1, &m1);
    Mat4Init(arr2, &m2);

    ASSERT_EQ(Mat4Add(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 16; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], arr1[i] + arr2[i]);
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4Sub) {
    // clang-format off
    nml_t arr1[16] = {1.0, 2.0, 3.0, 4.0,
                      5.0, 6.0, 7.0, 8.0,
                      9.0, 10.0, 11.0, 12.0,
                      13.0, 14.0, 15.0, 16.0};
    nml_t arr2[16] = {16.0, 15.0, 14.0, 13.0,
                      12.0, 11.0, 10.0, 9.0,
                      8.0, 7.0, 6.0, 5.0,
                      4.0, 3.0, 2.0, 1.0};
    // clang-format on
    Mat4 m1, m2, result;
    Mat4Init(arr1, &m1);
    Mat4Init(arr2, &m2);

    ASSERT_EQ(Mat4Sub(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 16; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], arr1[i] - arr2[i]);
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4Hadamard) {
    // clang-format off
    nml_t arr1[16] = {1.0, 2.0, 3.0, 4.0,
                      5.0, 6.0, 7.0, 8.0,
                      9.0, 10.0, 11.0, 12.0,
                      13.0, 14.0, 15.0, 16.0};
    nml_t arr2[16] = {16.0, 15.0, 14.0, 13.0,
                      12.0, 11.0, 10.0, 9.0,
                      8.0, 7.0, 6.0, 5.0,
                      4.0, 3.0, 2.0, 1.0};
    // clang-format on
    Mat4 m1, m2, result;
    Mat4Init(arr1, &m1);
    Mat4Init(arr2, &m2);

    ASSERT_EQ(Mat4Hadamard(&m1, &m2, &result), NML_SUCCESS);
    for (int i = 0; i < 16; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], arr1[i] * arr2[i]);
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4Scale) {
    // clang-format off
    nml_t arr1[16] = {1.0, 2.0, 3.0, 4.0,
                      5.0, 6.0, 7.0, 8.0,
                      9.0, 10.0, 11.0, 12.0,
                      13.0, 14.0, 15.0, 16.0};
    // clang-format on
    Mat4 m1, result;
    Mat4Init(arr1, &m1);
    nml_t scale = 2.5;

    ASSERT_EQ(Mat4Scale(&m1, scale, &result), NML_SUCCESS);
    for (int i = 0; i < 16; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], arr1[i] * scale);
    }
    return TEST_PASS;
}

TEST(Mat4Tests, Mat4Negate) {
    // clang-format off
    nml_t arr1[16] = {1.0, 2.0, 3.0, 4.0,
                      5.0, 6.0, 7.0, 8.0,
                      9.0, 10.0, 11.0, 12.0,
                      13.0, 14.0, 15.0, 16.0};
    // clang-format on
    Mat4 m1, result;
    Mat4Init(arr1, &m1);

    ASSERT_EQ(Mat4Negate(&m1, &result), NML_SUCCESS);
    for (int i = 0; i < 16; i++) {
        ASSERT_DOUBLE_EQ(result.Elements[i], -arr1[i]);
    }
    return TEST_PASS;
}

int main(void) {
    return RUN_ALL_TESTS();
}
