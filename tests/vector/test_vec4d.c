#include "nutest.h"
#include "vector/vec4d.h"
#include "utils/errors.h"

// helper function to compare two Vec4s with a tolerance
bool Vec4Near(const Vec4 *a, const Vec4 *b, float tolerance) {
    return (fabs(a->x - b->x) < tolerance) && (fabs(a->y - b->y) < tolerance) &&
           (fabs(a->z - b->z) < tolerance) && (fabs(a->w - b->w) < tolerance);
}

TEST(Vec4Test, Init) {
    Vec4 v;
    ASSERT_EQ(Vec4Init(1.0f, 2.0f, 3.0f, 4.0f, &v), NML_SUCCESS);
    ASSERT_FLOAT_EQ(v.x, 1.0f);
    ASSERT_FLOAT_EQ(v.y, 2.0f);
    ASSERT_FLOAT_EQ(v.z, 3.0f);
    ASSERT_FLOAT_EQ(v.w, 4.0f);
    return TEST_PASS;
}

TEST(Vec4Test, InitZero) {
    Vec4 v;
    ASSERT_EQ(Vec4InitZero(&v), NML_SUCCESS);
    ASSERT_FLOAT_EQ(v.x, 0.0f);
    ASSERT_FLOAT_EQ(v.y, 0.0f);
    ASSERT_FLOAT_EQ(v.z, 0.0f);
    ASSERT_FLOAT_EQ(v.w, 0.0f);
    return TEST_PASS;
}

TEST(Vec4Test, Length) {
    Vec4 v = {{1.0f, 2.0f, 3.0f, 4.0f}};
    ASSERT_FLOAT_EQ(Vec4Length(&v), sqrtf(1.0f + 4.0f + 9.0f + 16.0f));
    return TEST_PASS;
}

TEST(Vec4Test, LengthSqr) {
    Vec4 v = {{1.0f, 2.0f, 3.0f, 4.0f}};
    ASSERT_FLOAT_EQ(Vec4LengthSqr(&v), 1.0f + 4.0f + 9.0f + 16.0f);
    return TEST_PASS;
}

TEST(Vec4Test, Normalize) {
    Vec4 v = {{1.0f, 2.0f, 3.0f, 4.0f}};
    Vec4 out;
    ASSERT_EQ(Vec4Normalize(&v, &out), NML_SUCCESS);
    float len = Vec4Length(&v);
    ASSERT_FLOAT_EQ(out.x, v.x / len);
    ASSERT_FLOAT_EQ(out.y, v.y / len);
    ASSERT_FLOAT_EQ(out.z, v.z / len);
    ASSERT_FLOAT_EQ(out.w, v.w / len);
    return TEST_PASS;
}

TEST(Vec4Test, NormalizeZeroFails) {
    Vec4 zero = {{0.0f, 0.0f, 0.0f, 0.0f}};
    Vec4 out;
    ASSERT_EQ(Vec4Normalize(&zero, &out), NML_EZERODIV);
    return TEST_PASS;
}

TEST(Vec4Test, DotProduct) {
    Vec4 a = {{1.0f, 2.0f, 3.0f, 4.0f}};
    Vec4 b = {{4.0f, 3.0f, 2.0f, 1.0f}};
    ASSERT_FLOAT_EQ(Vec4Dot(&a, &b), 4.0f + 6.0f + 6.0f + 4.0f);
    return TEST_PASS;
}

TEST(Vec4Test, CrossProduct) {
    Vec4 a = {{1.0f, 0.0f, 0.0f, 0.0f}};
    Vec4 b = {{0.0f, 1.0f, 0.0f, 0.0f}};
    Vec4 out;
    ASSERT_EQ(Vec4Cross(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{0.0f, 0.0f, 1.0f, 0.0f}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Add) {
    Vec4 a = {{1.0f, 2.0f, 3.0f, 4.0f}};
    Vec4 b = {{4.0f, 3.0f, 2.0f, 1.0f}};
    Vec4 out;
    ASSERT_EQ(Vec4Add(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{5.0f, 5.0f, 5.0f, 5.0f}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Sub) {
    Vec4 a = {{1.0f, 2.0f, 3.0f, 4.0f}};
    Vec4 b = {{4.0f, 3.0f, 2.0f, 1.0f}};
    Vec4 out;
    ASSERT_EQ(Vec4Sub(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{-3.0f, -1.0f, 1.0f, 3.0f}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Mul) {
    Vec4 a = {{1.0f, 2.0f, 3.0f, 4.0f}};
    Vec4 b = {{4.0f, 3.0f, 2.0f, 1.0f}};
    Vec4 out;
    ASSERT_EQ(Vec4Mul(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{4.0f, 6.0f, 6.0f, 4.0f}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Div) {
    Vec4 a = {{4.0f, 9.0f, 16.0f, 25.0f}};
    Vec4 b = {{2.0f, 3.0f, 4.0f, 5.0f}};
    Vec4 out;
    ASSERT_EQ(Vec4Div(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{2.0f, 3.0f, 4.0f, 5.0f}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, DivByZeroFails) {
    Vec4 a = {{1.0f, 1.0f, 1.0f, 1.0f}};
    Vec4 b = {{0.0f, 1.0f, 1.0f, 1.0f}};
    Vec4 out;
    ASSERT_NE(Vec4Div(&a, &b, &out), NML_SUCCESS);
    return TEST_PASS;
}

TEST(Vec4Test, Scale) {
    Vec4 a = {{1.0f, 2.0f, 3.0f, 4.0f}};
    Vec4 out;
    ASSERT_EQ(Vec4Scale(&a, 2.0f, &out), NML_SUCCESS);
    Vec4 expected = {{2.0f, 4.0f, 6.0f, 8.0f}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Negate) {
    Vec4 a = {{1.0f, -2.0f, 3.0f, -4.0f}};
    Vec4 out;
    ASSERT_EQ(Vec4Negate(&a, &out), NML_SUCCESS);
    Vec4 expected = {{-1.0f, 2.0f, -3.0f, 4.0f}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Project) {
    Vec4 a = {{1.0f, 1.0f, 0.0f, 0.0f}};
    Vec4 b = {{2.0f, 0.0f, 0.0f, 0.0f}};
    Vec4 out;
    ASSERT_EQ(Vec4Project(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{1.0f, 0.0f, 0.0f, 0.0f}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Reject) {
    Vec4 a = {{1.0f, 1.0f, 0.0f, 0.0f}};
    Vec4 b = {{2.0f, 0.0f, 0.0f, 0.0f}};
    Vec4 out;
    ASSERT_EQ(Vec4Reject(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{0.0f, 1.0f, 0.0f, 0.0f}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Reflect) {
    Vec4 a = {{1.0f, -1.0f, 0.0f, 0.0f}};
    Vec4 n = {{0.0f, 1.0f, 0.0f, 0.0f}};
    Vec4 normalized_n;
    Vec4Normalize(&n, &normalized_n);
    Vec4 out;
    ASSERT_EQ(Vec4Reflect(&a, &normalized_n, &out), NML_SUCCESS);
    Vec4 expected = {{1.0f, 1.0f, 0.0f, 0.0f}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

int main(void) {
    return RUN_ALL_TESTS();
}
