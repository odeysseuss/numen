#include "nutest.h"
#include "vector/vec4d.h"
#include "utils/errors.h"

// helper function to compare two Vec4s with a tolerance
bool vec4Near(const Vec4 *a, const Vec4 *b, float tolerance) {
    return (fabs(a->x - b->x) < tolerance) && (fabs(a->y - b->y) < tolerance) &&
           (fabs(a->z - b->z) < tolerance) && (fabs(a->w - b->w) < tolerance);
}

TEST(Vec4Test, Init) {
    Vec4 v;
    ASSERT_EQ(vec4Init(1.0, 2.0, 3.0, 4.0, &v), NML_SUCCESS);
    ASSERT_DOUBLE_EQ(v.x, 1.0);
    ASSERT_DOUBLE_EQ(v.y, 2.0);
    ASSERT_DOUBLE_EQ(v.z, 3.0);
    ASSERT_DOUBLE_EQ(v.w, 4.0);
    return TEST_PASS;
}

TEST(Vec4Test, Initzero) {
    Vec4 v;
    ASSERT_EQ(vec4InitZero(&v), NML_SUCCESS);
    ASSERT_DOUBLE_EQ(v.x, 0.0);
    ASSERT_DOUBLE_EQ(v.y, 0.0);
    ASSERT_DOUBLE_EQ(v.z, 0.0);
    ASSERT_DOUBLE_EQ(v.w, 0.0);
    return TEST_PASS;
}

TEST(Vec4Test, Length) {
    Vec4 v = {{1.0, 2.0, 3.0, 4.0}};
    ASSERT_DOUBLE_EQ(vec4Length(&v), sqrtf(1.0 + 4.0 + 9.0 + 16.0));
    return TEST_PASS;
}

TEST(Vec4Test, LengthSqr) {
    Vec4 v = {{1.0, 2.0, 3.0, 4.0}};
    ASSERT_DOUBLE_EQ(vec4LengthSqr(&v), 1.0 + 4.0 + 9.0 + 16.0);
    return TEST_PASS;
}

TEST(Vec4Test, Normalize) {
    Vec4 v = {{1.0, 2.0, 3.0, 4.0}};
    Vec4 out;
    ASSERT_EQ(vec4Normalize(&v, &out), NML_SUCCESS);
    float len = vec4Length(&v);
    ASSERT_DOUBLE_EQ(out.x, v.x / len);
    ASSERT_DOUBLE_EQ(out.y, v.y / len);
    ASSERT_DOUBLE_EQ(out.z, v.z / len);
    ASSERT_DOUBLE_EQ(out.w, v.w / len);
    return TEST_PASS;
}

TEST(Vec4Test, NormalizezeroFails) {
    Vec4 zero = {{0.0, 0.0, 0.0, 0.0}};
    Vec4 out;
    ASSERT_EQ(vec4Normalize(&zero, &out), NML_EZERODIV);
    return TEST_PASS;
}

TEST(Vec4Test, DotProduct) {
    Vec4 a = {{1.0, 2.0, 3.0, 4.0}};
    Vec4 b = {{4.0, 3.0, 2.0, 1.0}};
    ASSERT_DOUBLE_EQ(vec4Dot(&a, &b), 4.0 + 6.0 + 6.0 + 4.0);
    return TEST_PASS;
}

TEST(Vec4Test, CrossProduct) {
    Vec4 a = {{1.0, 0.0, 0.0, 0.0}};
    Vec4 b = {{0.0, 1.0, 0.0, 0.0}};
    Vec4 out;
    ASSERT_EQ(vec4Cross(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{0.0, 0.0, 1.0, 0.0}};
    ASSERT_TRUE(vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Add) {
    Vec4 a = {{1.0, 2.0, 3.0, 4.0}};
    Vec4 b = {{4.0, 3.0, 2.0, 1.0}};
    Vec4 out;
    ASSERT_EQ(vec4Add(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{5.0, 5.0, 5.0, 5.0}};
    ASSERT_TRUE(vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Sub) {
    Vec4 a = {{1.0, 2.0, 3.0, 4.0}};
    Vec4 b = {{4.0, 3.0, 2.0, 1.0}};
    Vec4 out;
    ASSERT_EQ(vec4Sub(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{-3.0, -1.0, 1.0, 3.0}};
    ASSERT_TRUE(vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Mul) {
    Vec4 a = {{1.0, 2.0, 3.0, 4.0}};
    Vec4 b = {{4.0, 3.0, 2.0, 1.0}};
    Vec4 out;
    ASSERT_EQ(vec4Mul(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{4.0, 6.0, 6.0, 4.0}};
    ASSERT_TRUE(vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Div) {
    Vec4 a = {{4.0, 9.0, 16.0, 25.0}};
    Vec4 b = {{2.0, 3.0, 4.0, 5.0}};
    Vec4 out;
    ASSERT_EQ(vec4Div(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{2.0, 3.0, 4.0, 5.0}};
    ASSERT_TRUE(vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, DivByzeroFails) {
    Vec4 a = {{1.0, 1.0, 1.0, 1.0}};
    Vec4 b = {{0.0, 1.0, 1.0, 1.0}};
    Vec4 out;
    ASSERT_NE(vec4Div(&a, &b, &out), NML_SUCCESS);
    return TEST_PASS;
}

TEST(Vec4Test, Scale) {
    Vec4 a = {{1.0, 2.0, 3.0, 4.0}};
    Vec4 out;
    ASSERT_EQ(vec4Scale(&a, 2.0, &out), NML_SUCCESS);
    Vec4 expected = {{2.0, 4.0, 6.0, 8.0}};
    ASSERT_TRUE(vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Negate) {
    Vec4 a = {{1.0, -2.0, 3.0, -4.0}};
    Vec4 out;
    ASSERT_EQ(vec4Negate(&a, &out), NML_SUCCESS);
    Vec4 expected = {{-1.0, 2.0, -3.0, 4.0}};
    ASSERT_TRUE(vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Project) {
    Vec4 a = {{1.0, 1.0, 0.0, 0.0}};
    Vec4 b = {{2.0, 0.0, 0.0, 0.0}};
    Vec4 out;
    ASSERT_EQ(vec4Project(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{1.0, 0.0, 0.0, 0.0}};
    ASSERT_TRUE(vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Reject) {
    Vec4 a = {{1.0, 1.0, 0.0, 0.0}};
    Vec4 b = {{2.0, 0.0, 0.0, 0.0}};
    Vec4 out;
    ASSERT_EQ(vec4Reject(&a, &b, &out), NML_SUCCESS);
    Vec4 expected = {{0.0, 1.0, 0.0, 0.0}};
    ASSERT_TRUE(vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec4Test, Reflect) {
    Vec4 a = {{1.0, -1.0, 0.0, 0.0}};
    Vec4 n = {{0.0, 1.0, 0.0, 0.0}};
    Vec4 normalized_n;
    vec4Normalize(&n, &normalized_n);
    Vec4 out;
    ASSERT_EQ(vec4Reflect(&a, &normalized_n, &out), NML_SUCCESS);
    Vec4 expected = {{1.0, 1.0, 0.0, 0.0}};
    ASSERT_TRUE(vec4Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

int main(void) {
    return RUN_ALL_TESTS();
}
