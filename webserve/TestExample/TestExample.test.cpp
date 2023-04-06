//
// Created by Sehoon Jang on 3/29/23.
//

#include "TestExample.hpp"
#include <iostream>
#include "gtest/gtest.h"

TEST(TestExampleTest, TestExampleSum)
{
    // given
    TestExample testExample(8);
    int test1 = 1;
    int test2 = 2;
    int test3 = 3;

    // when
    int result1 = testExample.sum(test1);
    int result2 = testExample.sum(test2);
    int result3 = testExample.sum(test3);

    // then
    EXPECT_EQ(result1, 9);
    EXPECT_EQ(result2, 10);
    EXPECT_EQ(result3, 11);
}


TEST(TestExampleTest, TestExampleSub)
{
    // given
    TestExample testExample(8);
    int test1 = 1;
    int test2 = 2;
    int test3 = 3;

    // when
    int result1 = testExample.sub(test1);
    int result2 = testExample.sub(test2);
    int result3 = testExample.sub(test3);

    // then
    EXPECT_EQ(result1, 7);
    EXPECT_EQ(result2, 6);
    EXPECT_EQ(result3, -45);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}