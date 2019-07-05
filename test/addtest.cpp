#include "testdir/add.h"
#include "gtest/gtest.h"

TEST(AddTest, BaseTest) {
    EXPECT_EQ(2, add(1, 1));
}