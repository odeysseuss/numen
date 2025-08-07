#include "nutest.h"
#include "vector/vec4d.h"
#include "utils/errors.h"

// helper function to compare two Vec4s with a tolerance
bool Vec4Near(const Vec4 *a, const Vec4 *b, float tolerance) {
    return (fabs(a->X - b->X) < tolerance) && (fabs(a->Y - b->Y) < tolerance) &&
           (fabs(a->Z - b->Z) < tolerance) && (fabs(a->W - b->W) < tolerance);
}

TEST(Vec4Test, Init) {
    Vec4 v;
    ASSERT_EQ(Vec4Init(1.0, 2.0, 3.0, 4.0, &v), NML_SUCCESS);
    ASSERT_DOUBLE_EQ(v.X, 1.0);
    ASSERT_DOUBLE_EQ(v.Y, 2.0);
    ASSERT_DOUBLE_EQ(v.Z, 3.0);
    ASSERT_DOUBLE_EQ(v.W, 4.0);
    return TEST_PASS;
}

TEST(Vec4Test, InitZero) {
    Vec4 v;
    ASSERT_EQ(Vec4InitZero(&v), NML_SUCCESS);
    ASSERT_DOUBLE_EQ(v.X, 0.0);
    ASSERT_DOUBLE_EQ(v.Y, 0.0);
    ASSERT_DOUBLE_EQ(v.Z, 0.0);
    ASSERT_DOUBLE_EQ(v.W, 0.0);
    return TEST_PASS;
}

TEST(Vec4Test, Length) {
    Vec4 v = {{1.0, 2.0, 3.0, 4.0}};
    ASSERT_DOUBLE_EQ(Vec4Length(&v), sqrtf(1.0 + 4.0 + 9.0 + 16.0));
    return TEST_PASS;
}

TEST(Vec4Test, LengthSqr) {
    Vec4 v = {{1.0, 2.0, 3.0, 4.0}};
    ASSERT_DOUBLE_EQ(Vec4LengthSqr(&v), 1.0 + 4.0 + 9.0 + 16.0);
    return TEST_PASS;
}

TEST(Vec4Test, Normalize) {
    Vec4 v = {{1.0, 2.0, 3.0, 4.0}};
    Vec4 out;
    ASSERT_EQ(Vec4Normalize(&v, &out), NML_SUCCESS);
    float len = Vec4Length(&v);
    ASSERT_DOUBLE_EQ(out.X, v.X / len);
    ASSERT_DOUBLE_EQ(out.Y, v.Y / len);
    ASSERT_DOUBLE_EQ(out.Z, v.Z / len);
    ASSERT_DOUBLE_EQ(out.W, v.W / len);
    return TEST_PASS;
}

TEST(Vec4Test, NormalizeZeroFails) {
    Vec4 zero = {{0.0, 0.0, 0.0, 0.0}};
    Vec4 out;
    ASSERT_EQ(Vec4Normalize(&zero, &out), NML_EZERODIV);
    return TEST_PASS;
}

TEST(Vec4Test, DotProduct) {
    Vec4 a = {{1.0, 2.0, 3.0, 4.0}};
    Vec4 b = {{4.0, 3.0, 2.0, 1.0}};
    ASSERT_DOUBLE_EQ(Vec4Dot(&a, &b), 4.0 + 6.0 + 6.0 + 4.0);
    return TEST_PASS;
}

TEST(Vec4Test, CrossProduct) {
    Vec4 a = {{1.0, 0.0, 0.0, 0.0}};
    Vec4 b = {{0.0, 1.0, 0.0, 0.0}};
    Vec4 out;
    ASSERT_EQ(Vec4Cross(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{0.0, 0.0, 1.0, 0.0}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Add) {
    Vec4 a = {{1.0, 2.0, 3.0, 4.0}};
    Vec4 b = {{4.0, 3.0, 2.0, 1.0}};
    Vec4 out;
    ASSERT_EQ(Vec4Add(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{5.0, 5.0, 5.0, 5.0}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Sub) {
    Vec4 a = {{1.0, 2.0, 3.0, 4.0}};
    Vec4 b = {{4.0, 3.0, 2.0, 1.0}};
    Vec4 out;
    ASSERT_EQ(Vec4Sub(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{-3.0, -1.0, 1.0, 3.0}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Mul) {
    Vec4 a = {{1.0, 2.0, 3.0, 4.0}};
    Vec4 b = {{4.0, 3.0, 2.0, 1.0}};
    Vec4 out;
    ASSERT_EQ(Vec4Mul(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{4.0, 6.0, 6.0, 4.0}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Div) {
    Vec4 a = {{4.0, 9.0, 16.0, 25.0}};
    Vec4 b = {{2.0, 3.0, 4.0, 5.0}};
    Vec4 out;
    ASSERT_EQ(Vec4Div(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{2.0, 3.0, 4.0, 5.0}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, DivByZeroFails) {
    Vec4 a = {{1.0, 1.0, 1.0, 1.0}};
    Vec4 b = {{0.0, 1.0, 1.0, 1.0}};
    Vec4 out;
    ASSERT_NE(Vec4Div(&a, &b, &out), NML_SUCCESS);
    return TEST_PASS;
}

TEST(Vec4Test, Scale) {
    Vec4 a = {{1.0, 2.0, 3.0, 4.0}};
    Vec4 out;
    ASSERT_EQ(Vec4Scale(&a, 2.0, &out), NML_SUCCESS);
    Vec4 expected = {{2.0, 4.0, 6.0, 8.0}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Negate) {
    Vec4 a = {{1.0, -2.0, 3.0, -4.0}};
    Vec4 out;
    ASSERT_EQ(Vec4Negate(&a, &out), NML_SUCCESS);
    Vec4 expected = {{-1.0, 2.0, -3.0, 4.0}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Project) {
    Vec4 a = {{1.0, 1.0, 0.0, 0.0}};
    Vec4 b = {{2.0, 0.0, 0.0, 0.0}};
    Vec4 out;
    ASSERT_EQ(Vec4Project(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{1.0, 0.0, 0.0, 0.0}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Reject) {
    Vec4 a = {{1.0, 1.0, 0.0, 0.0}};
    Vec4 b = {{2.0, 0.0, 0.0, 0.0}};
    Vec4 out;
    ASSERT_EQ(Vec4Reject(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{0.0, 1.0, 0.0, 0.0}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Reflect) {
    Vec4 a = {{1.0, -1.0, 0.0, 0.0}};
    Vec4 n = {{0.0, 1.0, 0.0, 0.0}};
    Vec4 normalized_n;
    Vec4Normalize(&n, &normalized_n);
    Vec4 out;
    ASSERT_EQ(Vec4Reflect(&a, &normalized_n, &out), NML_SUCCESS);
    Vec4 expected = {{1.0, 1.0, 0.0, 0.0}};
    ASSERT_TRUE(Vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

int main(void) {
    return RUN_ALL_TESTS();
}
