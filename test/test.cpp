#include <gtest/gtest.h>
#include "Binary.h"

TEST(BinaryTest, SizeValueConstructor) {
    Binary bin(5, 1);
    EXPECT_EQ(bin.equals(Binary({1, 1, 1, 1, 1})), true);
    
    EXPECT_THROW(Binary(0, 1), std::invalid_argument);
    EXPECT_THROW(Binary(3, 2), std::invalid_argument);
}

TEST(BinaryTest, InitializerListConstructor) {
    Binary bin({1, 0, 1, 1});
    EXPECT_EQ(bin.equals(Binary({1, 0, 1, 1})), true);
    
    EXPECT_THROW(Binary({1, 2, 0}), std::invalid_argument);
}

TEST(BinaryTest, StringConstructor) {
    Binary bin("1011");
    
    EXPECT_EQ(bin.equals(Binary({1, 0, 1, 1})), true);
    EXPECT_THROW(Binary(""), std::invalid_argument);
    EXPECT_THROW(Binary("1021"), std::invalid_argument);
}

TEST(BinaryTest, CopyConstructor) {
    Binary orig({1, 0, 1});
    Binary copy(orig);
    EXPECT_EQ(orig.equals(copy), true);
}

TEST(BinaryTest, MoveConstructor) {
    Binary orig({1, 0, 1});
    Binary moved(std::move(orig));
    EXPECT_EQ(moved.equals(Binary({1, 0, 1})), true);
}

TEST(BinaryTest, Equals) {
    Binary bin1({1, 0, 1});
    Binary bin2({1, 0, 1});
    Binary bin3({1, 1, 0});
    
    EXPECT_TRUE(bin1.equals(bin2));
    EXPECT_FALSE(bin1.equals(bin3));
    
    Binary bin4({0, 0, 1, 0, 1});
    Binary bin5({1, 0, 1});
    EXPECT_TRUE(bin4.equals(bin5));
}

TEST(BinaryTest, LessThan) {
    Binary bin1({1, 0, 1});    // 5
    Binary bin2({1, 1, 0});    // 6
    Binary bin3({1, 0, 1, 0}); // 10
    
    EXPECT_TRUE(bin1.lessThan(bin2));
    EXPECT_TRUE(bin1.lessThan(bin3));
    EXPECT_FALSE(bin2.lessThan(bin1));
    EXPECT_FALSE(bin3.lessThan(bin1));
    
    Binary bin4({0, 0, 1, 0, 1}); // 5
    EXPECT_FALSE(bin4.lessThan(bin1));
    EXPECT_TRUE(bin1.equals(bin4));
}

TEST(BinaryTest, GreaterThan) {
    Binary bin1({1, 0, 1});    // 5
    Binary bin2({1, 1, 0});    // 6
    Binary bin3({1, 0, 0});    // 4
    
    EXPECT_TRUE(bin2.greaterThan(bin1));
    EXPECT_TRUE(bin1.greaterThan(bin3));
    EXPECT_FALSE(bin3.greaterThan(bin1));
    EXPECT_FALSE(bin1.greaterThan(bin2));
}

// Тесты арифметических операций
TEST(BinaryTest, Add) {
    Binary bin1({1, 1});    // 3
    Binary bin2({1, 0});    // 2
    Binary result1 = bin1.add(bin2);
    EXPECT_TRUE(result1.equals(Binary({1, 0, 1}))); // 5
    
    Binary bin3({1, 0, 1}); // 5
    Binary bin4({1, 1});    // 3
    Binary result2 = bin3.add(bin4);
    EXPECT_TRUE(result2.equals(Binary({1, 0, 0, 0}))); // 8
    
    Binary bin5({1});       // 1
    Binary result3 = bin5.add(bin5);
    EXPECT_TRUE(result3.equals(Binary({1, 0}))); // 2
}

TEST(BinaryTest, Subtract) {
    Binary bin1({1, 0, 1}); // 5
    Binary bin2({1, 1});    // 3
    Binary result1 = bin1.subtract(bin2);
    EXPECT_TRUE(result1.equals(Binary({1, 0}))); // 2

    Binary bin3({1, 0, 0, 0}); // 8
    Binary bin4({1, 0, 1});    // 5
    Binary result2 = bin3.subtract(bin4);
    EXPECT_TRUE(result2.equals(Binary({1, 1}))); // 3
    
    Binary bin5({1});       // 1
    Binary bin6({1, 0});    // 2
    EXPECT_THROW(bin5.subtract(bin6), std::invalid_argument);
}

TEST(BinaryTest, Copy) {
    Binary orig({1, 0, 1, 1});
    Binary copy = orig.copy();
    
    EXPECT_TRUE(orig.equals(copy));
    EXPECT_NE(orig.equals(Binary({1, 0, 1, 0})), true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}