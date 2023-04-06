#include "ft.hpp"
#include <iostream>
#include "gtest/gtest.h"

TEST(libftUnitTest, splitStirngTest)
{
    // given
    std::string a = "1, 2, 3, 4";
    std::string b = "1, 2,, 3, 4";

    // when
    std::vector<std::string> result1 = ft::splitString(a, ", ");
    std::vector<std::string> result2 = ft::splitString(a, "2");
    std::vector<std::string> result3 = ft::splitString(b, ",");

    // then
    EXPECT_EQ(result1.size(), 4);
    EXPECT_EQ(result1[2].compare("3"), 0);
    EXPECT_EQ(result2.size(), 2);
    EXPECT_EQ(result2[1].compare(", 3, 4"), 0);
    EXPECT_EQ(result3.size(), 4);
    EXPECT_EQ(result3[2].compare(" 3"), 0);
}

TEST(libftUnitTest, splitBlockStirngTest)
{
 // given
 std::string a = "block1 {1, 2, 3, 4} block2 {1, 2, 3, 4} block3 {1, 2, 3, 4}";

 // when
 std::vector<std::string> result1 = ft::splitBlockString(a);

 // then
 EXPECT_EQ(result1.size(), 3);
 EXPECT_EQ(result1[0].compare("1, 2, 3, 4"), 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}