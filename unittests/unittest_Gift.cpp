
#include "gtest/gtest.h"
#include "Gift.hpp"

TEST(GiftTest, checkConstructors) {
    Gift g1(1, 0.1, 0.1, 0.1);
    Gift g2(g1);
    Gift g3({2, 0.2, 0.2, 0.2});

    EXPECT_EQ(g1.ID(), 1);
    EXPECT_EQ(g1.latitude(), 0.1);
    EXPECT_EQ(g1.longitude(), 0.1);
    EXPECT_EQ(g1.weight(), 0.1);

    EXPECT_EQ(g2.ID(), 1);
    EXPECT_EQ(g2.latitude(), 0.1);
    EXPECT_EQ(g2.longitude(), 0.1);
    EXPECT_EQ(g2.weight(), 0.1);

    EXPECT_EQ(g3.ID(), 2);
    EXPECT_EQ(g3.latitude(), 0.2);
    EXPECT_EQ(g3.longitude(), 0.2);
    EXPECT_EQ(g3.weight(), 0.2);

}

TEST(GiftTest, assignOperator) {
    Gift g1(1, 0.1, 0.1, 0.1);
    Gift g2(2, 0.2, 0.2, 0.2);

    g1 = g2;
    EXPECT_EQ(g1.ID(), 2);
    EXPECT_EQ(g1.latitude(), 0.2);
    EXPECT_EQ(g1.longitude(), 0.2);
    EXPECT_EQ(g1.weight(), 0.2);

    g2 = {3, 2.5, 1.3, 3.45};
    EXPECT_EQ(g2.ID(), 3);
    EXPECT_EQ(g2.latitude(), 2.5);
    EXPECT_EQ(g2.longitude(), 1.3);
    EXPECT_EQ(g2.weight(), 3.45);
}

TEST(GiftTest, equalityOperator) {
    Gift g1(1, 0.1, 0.1, 0.1);
    Gift g2(g1);

    EXPECT_EQ(g1, g2);
}

TEST(GiftTest, inequalityOperator) {
    Gift g1(1, 0.1, 0.1, 0.1);
    Gift g2(2, 0.2, 0.2, 0.2);

    EXPECT_NE(g1, g2);
}
