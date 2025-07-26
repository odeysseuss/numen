#include "nutest.h"

TEST(simple, add) {
    ASSERT_EQ(2, 1 + 1);
    ASSERT_EQ(5, 2 + 3);
    return TEST_PASS;
}

TEST(simple, sub) {
    ASSERT_EQ(2, 2 - 1);
    ASSERT_EQ(5, 8 - 3);
    return TEST_PASS;
}

int main(void) {
    return RUN_ALL_TESTS();
}
