#include "nutest.h"
#include "vector/vec3d.h"
#include "utils/errors.h"

// helper function to compare two Vec3s with a tolerance
bool vec3Near(const Vec3 *a, const Vec3 *b, float tolerance) {
    return (fabs(a->x - b->x) < tolerance) && (fabs(a->y - b->y) < tolerance) &&
           (fabs(a->z - b->z) < tolerance);
}

TEST(Vec3Test, Init) {
    Vec3 v;
    ASSERT_EQ(vec3Init(1.0, 2.0, 3.0, &v), NML_SUCCESS);
    ASSERT_DOUBLE_EQ(v.x, 1.0);
    ASSERT_DOUBLE_EQ(v.y, 2.0);
    ASSERT_DOUBLE_EQ(v.z, 3.0);
    return TEST_PASS;
}

TEST(Vec3Test, Initzero) {
    Vec3 v;
    ASSERT_EQ(vec3InitZero(&v), NML_SUCCESS);
    ASSERT_DOUBLE_EQ(v.x, 0.0);
    ASSERT_DOUBLE_EQ(v.y, 0.0);
    ASSERT_DOUBLE_EQ(v.z, 0.0);
    return TEST_PASS;
}

TEST(Vec3Test, Length) {
    Vec3 v = {{1.0, 2.0, 3.0}};
    ASSERT_DOUBLE_EQ(vec3Length(&v), sqrtf(1.0 + 4.0 + 9.0));
    return TEST_PASS;
}

TEST(Vec3Test, LengthSqr) {
    Vec3 v = {{1.0, 2.0, 3.0}};
    ASSERT_DOUBLE_EQ(vec3LengthSqr(&v), 1.0 + 4.0 + 9.0);
    return TEST_PASS;
}

TEST(Vec3Test, Normalize) {
    Vec3 v = {{1.0, 2.0, 3.0}};
    Vec3 out;
    ASSERT_EQ(vec3Normalize(&v, &out), NML_SUCCESS);
    float len = vec3Length(&v);
    ASSERT_DOUBLE_EQ(out.x, v.x / len);
    ASSERT_DOUBLE_EQ(out.y, v.y / len);
    ASSERT_DOUBLE_EQ(out.z, v.z / len);
    return TEST_PASS;
}

TEST(Vec3Test, NormalizezeroFails) {
    Vec3 zero = {{0.0, 0.0, 0.0}};
    Vec3 out;
    ASSERT_EQ(vec3Normalize(&zero, &out), NML_EZERODIV);
    return TEST_PASS;
}

TEST(Vec3Test, DotProduct) {
    Vec3 a = {{1.0, 2.0, 3.0}};
    Vec3 b = {{4.0, 3.0, 2.0}};
    ASSERT_DOUBLE_EQ(vec3Dot(&a, &b), 4.0 + 6.0 + 6.0);
    return TEST_PASS;
}

TEST(Vec3Test, CrossProduct) {
    Vec3 a = {{1.0, 0.0, 0.0}};
    Vec3 b = {{0.0, 1.0, 0.0}};
    Vec3 out;
    ASSERT_EQ(vec3Cross(&a, &b, &out), NML_SUCCESS);
    Vec3 expected = {{0.0, 0.0, 1.0}};
    ASSERT_TRUE(vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, Add) {
    Vec3 a = {{1.0, 2.0, 3.0}};
    Vec3 b = {{4.0, 3.0, 2.0}};
    Vec3 out;
    ASSERT_EQ(vec3Add(&a, &b, &out), NML_SUCCESS);
    Vec3 expected = {{5.0, 5.0, 5.0}};
    ASSERT_TRUE(vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, Sub) {
    Vec3 a = {{1.0, 2.0, 3.0}};
    Vec3 b = {{4.0, 3.0, 2.0}};
    Vec3 out;
    ASSERT_EQ(vec3Sub(&a, &b, &out), NML_SUCCESS);
    Vec3 expected = {{-3.0, -1.0, 1.0}};
    ASSERT_TRUE(vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, Mul) {
    Vec3 a = {{1.0, 2.0, 3.0}};
    Vec3 b = {{4.0, 3.0, 2.0}};
    Vec3 out;
    ASSERT_EQ(vec3Mul(&a, &b, &out), NML_SUCCESS);
    Vec3 expected = {{4.0, 6.0, 6.0}};
    ASSERT_TRUE(vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, Div) {
    Vec3 a = {{4.0, 9.0, 25.0}};
    Vec3 b = {{2.0, 3.0, 5.0}};
    Vec3 out;
    ASSERT_EQ(vec3Div(&a, &b, &out), NML_SUCCESS);
    Vec3 expected = {{2.0, 3.0, 5.0}};
    ASSERT_TRUE(vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, DivByzeroFails) {
    Vec3 a = {{1.0, 1.0, 1.0}};
    Vec3 b = {{0.0, 1.0, 1.0}};
    Vec3 out;
    ASSERT_NE(vec3Div(&a, &b, &out), NML_SUCCESS);
    return TEST_PASS;
}

TEST(Vec3Test, Scale) {
    Vec3 a = {{1.0, 2.0, 3.0}};
    Vec3 out;
    ASSERT_EQ(vec3Scale(&a, 2.0, &out), NML_SUCCESS);
    Vec3 expected = {{2.0, 4.0, 6.0}};
    ASSERT_TRUE(vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, Negate) {
    Vec3 a = {{1.0, -2.0, 3.0}};
    Vec3 out;
    ASSERT_EQ(vec3Negate(&a, &out), NML_SUCCESS);
    Vec3 expected = {{-1.0, 2.0, -3.0}};
    ASSERT_TRUE(vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, Project) {
    Vec3 a = {{1.0, 1.0, 0.0}};
    Vec3 b = {{2.0, 0.0, 0.0}};
    Vec3 out;
    ASSERT_EQ(vec3Project(&a, &b, &out), NML_SUCCESS);
    Vec3 expected = {{1.0, 0.0, 0.0}};
    ASSERT_TRUE(vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, Reject) {
    Vec3 a = {{1.0, 1.0, 0.0}};
    Vec3 b = {{2.0, 0.0, 0.0}};
    Vec3 out;
    ASSERT_EQ(vec3Reject(&a, &b, &out), NML_SUCCESS);
    Vec3 expected = {{0.0, 1.0, 0.0}};
    ASSERT_TRUE(vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec3Test, Reflect) {
    Vec3 a = {{1.0, -1.0, 0.0}};
    Vec3 n = {{0.0, 1.0, 0.0}};
    Vec3 normalized_n;
    vec3Normalize(&n, &normalized_n);
    Vec3 out;
    ASSERT_EQ(vec3Reflect(&a, &normalized_n, &out), NML_SUCCESS);
    Vec3 expected = {{1.0, 1.0, 0.0}};
    ASSERT_TRUE(vec3Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

int main(void) {
    return RUN_ALL_TESTS();
}
