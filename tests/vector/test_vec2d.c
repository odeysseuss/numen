#include "nutest.h"
#include "vector/vec2d.h"
#include "utils/errors.h"

// helper function to compare two Vec2s with a tolerance
bool vec2Near(const Vec2 *a, const Vec2 *b, float tolerance) {
    return (fabs(a->x - b->x) < tolerance) && (fabs(a->y - b->y) < tolerance);
}

TEST(Vec2Test, Init) {
    Vec2 v;
    ASSERT_EQ(vec2Init(1.0, 2.0, &v), NML_SUCCESS);
    ASSERT_FLOAT_EQ(v.x, 1.0);
    ASSERT_FLOAT_EQ(v.y, 2.0);
    return TEST_PASS;
}

TEST(Vec2Test, InitZero) {
    Vec2 v;
    ASSERT_EQ(vec2InitZero(&v), NML_SUCCESS);
    ASSERT_FLOAT_EQ(v.x, 0.0);
    ASSERT_FLOAT_EQ(v.y, 0.0);
    return TEST_PASS;
}

TEST(Vec2Test, Length) {
    Vec2 v = {{1.0, 2.0}};
    ASSERT_FLOAT_EQ(vec2Length(&v), sqrtf(1.0 + 4.0));
    return TEST_PASS;
}

TEST(Vec2Test, LengthSqr) {
    Vec2 v = {{1.0, 2.0}};
    ASSERT_FLOAT_EQ(vec2LengthSqr(&v), 1.0 + 4.0);
    return TEST_PASS;
}

TEST(Vec2Test, Normalize) {
    Vec2 v = {{1.0, 2.0}};
    Vec2 out;
    ASSERT_EQ(vec2Normalize(&v, &out), NML_SUCCESS);
    float len = vec2Length(&v);
    ASSERT_FLOAT_EQ(out.x, v.x / len);
    ASSERT_FLOAT_EQ(out.y, v.y / len);
    return TEST_PASS;
}

TEST(Vec2Test, NormalizeZeroFails) {
    Vec2 zero = {{0.0, 0.0}};
    Vec2 out;
    ASSERT_EQ(vec2Normalize(&zero, &out), NML_EZERODIV);
    return TEST_PASS;
}

TEST(Vec2Test, DotProduct) {
    Vec2 a = {{1.0, 2.0}};
    Vec2 b = {{4.0, 3.0}};
    ASSERT_FLOAT_EQ(vec2Dot(&a, &b), 4.0 + 6.0);
    return TEST_PASS;
}

TEST(Vec2Test, CrossProduct) {
    Vec2 a = {{1.0, 0.0}};
    Vec2 b = {{0.0, 1.0}};
    nml_t cross = vec2Cross(&a, &b);

    ASSERT_FLOAT_EQ(cross, 1.0);
    return TEST_PASS;
}

TEST(Vec2Test, Add) {
    Vec2 a = {{1.0, 2.0}};
    Vec2 b = {{4.0, 3.0}};
    Vec2 out;
    ASSERT_EQ(vec2Add(&a, &b, &out), NML_SUCCESS);
    Vec2 expected = {{5.0, 5.0}};
    ASSERT_TRUE(vec2Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec2Test, Sub) {
    Vec2 a = {{1.0, 2.0}};
    Vec2 b = {{4.0, 3.0}};
    Vec2 out;
    ASSERT_EQ(vec2Sub(&a, &b, &out), NML_SUCCESS);
    Vec2 expected = {{-3.0, -1.0}};
    ASSERT_TRUE(vec2Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec2Test, Mul) {
    Vec2 a = {{1.0, 2.0}};
    Vec2 b = {{4.0, 3.0}};
    Vec2 out;
    ASSERT_EQ(vec2Mul(&a, &b, &out), NML_SUCCESS);
    Vec2 expected = {{4.0, 6.0}};
    ASSERT_TRUE(vec2Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec2Test, Div) {
    Vec2 a = {{4.0, 9.0}};
    Vec2 b = {{2.0, 3.0}};
    Vec2 out;
    ASSERT_EQ(vec2Div(&a, &b, &out), NML_SUCCESS);
    Vec2 expected = {{2.0, 3.0}};
    ASSERT_TRUE(vec2Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec2Test, DivByZeroFails) {
    Vec2 a = {{1.0, 1.0}};
    Vec2 b = {{0.0, 1.0}};
    Vec2 out;
    ASSERT_NE(vec2Div(&a, &b, &out), NML_SUCCESS);
    return TEST_PASS;
}

TEST(Vec2Test, Scale) {
    Vec2 a = {{1.0, 2.0}};
    Vec2 out;
    ASSERT_EQ(vec2Scale(&a, 2.0, &out), NML_SUCCESS);
    Vec2 expected = {{2.0, 4.0}};
    ASSERT_TRUE(vec2Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec2Test, Negate) {
    Vec2 a = {{1.0, -2.0}};
    Vec2 out;
    ASSERT_EQ(vec2Negate(&a, &out), NML_SUCCESS);
    Vec2 expected = {{-1.0, 2.0}};
    ASSERT_TRUE(vec2Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec2Test, Project) {
    Vec2 a = {{1.0, 1.0}};
    Vec2 b = {{2.0, 0.0}};
    Vec2 out;
    ASSERT_EQ(vec2Project(&a, &b, &out), NML_SUCCESS);
    Vec2 expected = {{1.0, 0.0}};
    ASSERT_TRUE(vec2Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec2Test, Reject) {
    Vec2 a = {{1.0, 1.0}};
    Vec2 b = {{2.0, 0.0}};
    Vec2 out;
    ASSERT_EQ(vec2Reject(&a, &b, &out), NML_SUCCESS);
    Vec2 expected = {{0.0, 1.0}};
    ASSERT_TRUE(vec2Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

TEST(Vec2Test, Reflect) {
    Vec2 a = {{1.0, -1.0}};
    Vec2 n = {{0.0, 1.0}};
    Vec2 normalized_n;
    vec2Normalize(&n, &normalized_n);
    Vec2 out;
    ASSERT_EQ(vec2Reflect(&a, &normalized_n, &out), NML_SUCCESS);
    Vec2 expected = {{1.0, 1.0}};
    ASSERT_TRUE(vec2Near(&out, &expected, kEPSILON));
    return TEST_PASS;
}

int main(void) {
    return RUN_ALL_TESTS();
}
