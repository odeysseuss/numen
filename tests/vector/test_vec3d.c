#include "nutest.h"
#include "vector/vec3d.h"
#include "utils/errors.h"

// helper function to compare two Vec3s with a tolerance
bool Vec3Near(const Vec3 *a, const Vec3 *b, float tolerance) {
    return (fabs(a->x - b->x) < tolerance) && (fabs(a->y - b->y) < tolerance) &&
           (fabs(a->z - b->z) < tolerance);
}

TEST(Vec3Test, Init) {
    Vec3 v;
    ASSERT_EQ(Vec3Init(1.0f, 2.0f, 3.0f, &v), NML_SUCCESS);
    ASSERT_FLOAT_EQ(v.x, 1.0f);
    ASSERT_FLOAT_EQ(v.y, 2.0f);
    ASSERT_FLOAT_EQ(v.z, 3.0f);
    return TEST_PASS;
}

TEST(Vec3Test, InitZero) {
    Vec3 v;
    ASSERT_EQ(Vec3InitZero(&v), NML_SUCCESS);
    ASSERT_FLOAT_EQ(v.x, 0.0f);
    ASSERT_FLOAT_EQ(v.y, 0.0f);
    ASSERT_FLOAT_EQ(v.z, 0.0f);
    return TEST_PASS;
}

TEST(Vec3Test, Length) {
    Vec3 v = {{1.0f, 2.0f, 3.0f}};
    ASSERT_FLOAT_EQ(Vec3Length(&v), sqrtf(1.0f + 4.0f + 9.0f));
    return TEST_PASS;
}

TEST(Vec3Test, LengthSqr) {
    Vec3 v = {{1.0f, 2.0f, 3.0f}};
    ASSERT_FLOAT_EQ(Vec3LengthSqr(&v), 1.0f + 4.0f + 9.0f);
    return TEST_PASS;
}

TEST(Vec3Test, Normalize) {
    Vec3 v = {{1.0f, 2.0f, 3.0f}};
    Vec3 out;
    ASSERT_EQ(Vec3Normalize(&v, &out), NML_SUCCESS);
    float len = Vec3Length(&v);
    ASSERT_FLOAT_EQ(out.x, v.x / len);
    ASSERT_FLOAT_EQ(out.y, v.y / len);
    ASSERT_FLOAT_EQ(out.z, v.z / len);
    return TEST_PASS;
}

TEST(Vec3Test, NormalizeZeroFails) {
    Vec3 zero = {{0.0f, 0.0f, 0.0f}};
    Vec3 out;
    ASSERT_EQ(Vec3Normalize(&zero, &out), NML_EZERODIV);
    return TEST_PASS;
}

TEST(Vec3Test, DotProduct) {
    Vec3 a = {{1.0f, 2.0f, 3.0f}};
    Vec3 b = {{4.0f, 3.0f, 2.0f}};
    ASSERT_FLOAT_EQ(Vec3Dot(&a, &b), 4.0f + 6.0f + 6.0f);
    return TEST_PASS;
}

TEST(Vec3Test, CrossProduct) {
    Vec3 a = {{1.0f, 0.0f, 0.0f}};
    Vec3 b = {{0.0f, 1.0f, 0.0f}};
    Vec3 out;
    ASSERT_EQ(Vec3Cross(&a, &b, &out), NML_SUCCESS);
    Vec3 expected = {{0.0f, 0.0f, 1.0f}};
    ASSERT_TRUE(Vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, Add) {
    Vec3 a = {{1.0f, 2.0f, 3.0f}};
    Vec3 b = {{4.0f, 3.0f, 2.0f}};
    Vec3 out;
    ASSERT_EQ(Vec3Add(&a, &b, &out), NML_SUCCESS);
    Vec3 expected = {{5.0f, 5.0f, 5.0f}};
    ASSERT_TRUE(Vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, Sub) {
    Vec3 a = {{1.0f, 2.0f, 3.0f}};
    Vec3 b = {{4.0f, 3.0f, 2.0f}};
    Vec3 out;
    ASSERT_EQ(Vec3Sub(&a, &b, &out), NML_SUCCESS);
    Vec3 expected = {{-3.0f, -1.0f, 1.0f}};
    ASSERT_TRUE(Vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, Mul) {
    Vec3 a = {{1.0f, 2.0f, 3.0f}};
    Vec3 b = {{4.0f, 3.0f, 2.0f}};
    Vec3 out;
    ASSERT_EQ(Vec3Mul(&a, &b, &out), NML_SUCCESS);
    Vec3 expected = {{4.0f, 6.0f, 6.0f}};
    ASSERT_TRUE(Vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, Div) {
    Vec3 a = {{4.0f, 9.0f, 25.0f}};
    Vec3 b = {{2.0f, 3.0f, 5.0f}};
    Vec3 out;
    ASSERT_EQ(Vec3Div(&a, &b, &out), NML_SUCCESS);
    Vec3 expected = {{2.0f, 3.0f, 5.0f}};
    ASSERT_TRUE(Vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, DivByZeroFails) {
    Vec3 a = {{1.0f, 1.0f, 1.0f}};
    Vec3 b = {{0.0f, 1.0f, 1.0f}};
    Vec3 out;
    ASSERT_NE(Vec3Div(&a, &b, &out), NML_SUCCESS);
    return TEST_PASS;
}

TEST(Vec3Test, Scale) {
    Vec3 a = {{1.0f, 2.0f, 3.0f}};
    Vec3 out;
    ASSERT_EQ(Vec3Scale(&a, 2.0f, &out), NML_SUCCESS);
    Vec3 expected = {{2.0f, 4.0f, 6.0f}};
    ASSERT_TRUE(Vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, Negate) {
    Vec3 a = {{1.0f, -2.0f, 3.0f}};
    Vec3 out;
    ASSERT_EQ(Vec3Negate(&a, &out), NML_SUCCESS);
    Vec3 expected = {{-1.0f, 2.0f, -3.0f}};
    ASSERT_TRUE(Vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, Project) {
    Vec3 a = {{1.0f, 1.0f, 0.0f}};
    Vec3 b = {{2.0f, 0.0f, 0.0f}};
    Vec3 out;
    ASSERT_EQ(Vec3Project(&a, &b, &out), NML_SUCCESS);
    Vec3 expected = {{1.0f, 0.0f, 0.0f}};
    ASSERT_TRUE(Vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, Reject) {
    Vec3 a = {{1.0f, 1.0f, 0.0f}};
    Vec3 b = {{2.0f, 0.0f, 0.0f}};
    Vec3 out;
    ASSERT_EQ(Vec3Reject(&a, &b, &out), NML_SUCCESS);
    Vec3 expected = {{0.0f, 1.0f, 0.0f}};
    ASSERT_TRUE(Vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, Reflect) {
    Vec3 a = {{1.0f, -1.0f, 0.0f}};
    Vec3 n = {{0.0f, 1.0f, 0.0f}};
    Vec3 normalized_n;
    Vec3Normalize(&n, &normalized_n);
    Vec3 out;
    ASSERT_EQ(Vec3Reflect(&a, &normalized_n, &out), NML_SUCCESS);
    Vec3 expected = {{1.0f, 1.0f, 0.0f}};
    ASSERT_TRUE(Vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

int main(void) {
    return RUN_ALL_TESTS();
}
