
#include "gtest/gtest.h"
#include "Gift.hpp"

TEST(GiftTest, checkConstructors) {
    CompareIDStrategy cs;
    Gift g1(1, 0.1, 0.1, 0.1, &cs);
    g1.setTourNumber(3);
    Gift g2(g1);
    Gift g3({2, 0.2, 0.2, 0.2}, &cs);
    Gift g4(&cs);

    EXPECT_EQ(g1.ID(), 1);
    EXPECT_EQ(g1.latitude(), 0.1);
    EXPECT_EQ(g1.longitude(), 0.1);
    EXPECT_EQ(g1.weight(), 0.1);
    EXPECT_NEAR(g1.getDistance2Pole(), 9996.44, 0.009);
    EXPECT_EQ(g1.getTourNumber(), 3);

    EXPECT_EQ(g2.ID(), 1);
    EXPECT_EQ(g2.latitude(), 0.1);
    EXPECT_EQ(g2.longitude(), 0.1);
    EXPECT_EQ(g2.weight(), 0.1);
    EXPECT_NEAR(g2.getDistance2Pole(), 9996.44, 0.009);
    EXPECT_EQ(g2.getTourNumber(), 3);

    EXPECT_EQ(g3.ID(), 2);
    EXPECT_EQ(g3.latitude(), 0.2);
    EXPECT_EQ(g3.longitude(), 0.2);
    EXPECT_EQ(g3.weight(), 0.2);
    EXPECT_NEAR(g3.getDistance2Pole(), 9985.32, 0.009);
    EXPECT_EQ(g3.getTourNumber(), 0);

    EXPECT_EQ(g4.ID(), 0);
    EXPECT_EQ(g4.latitude(), 0.0);
    EXPECT_EQ(g4.longitude(), 0.0);
    EXPECT_EQ(g4.weight(), 0.0);
    EXPECT_NEAR(g4.getDistance2Pole(), 10007.56, 0.009);
    EXPECT_EQ(g4.getTourNumber(), 0);
}

TEST(GiftTest, assignOperator) {
    CompareIDStrategy cs;
    Gift g1(1, 0.1, 0.1, 0.1, &cs);
    Gift g2(2, 0.2, 0.2, 0.2, &cs);

    g2.setTourNumber(5);

    g1 = g2;
    EXPECT_EQ(g1.ID(), 2);
    EXPECT_EQ(g1.latitude(), 0.2);
    EXPECT_EQ(g1.longitude(), 0.2);
    EXPECT_EQ(g1.weight(), 0.2);
    EXPECT_NEAR(g1.getDistance2Pole(), 9985.32, 0.009);
    EXPECT_EQ(g1.getTourNumber(), 5);

    g2 = {3, 2.5, 1.3, 3.45};
    EXPECT_EQ(g2.ID(), 3);
    EXPECT_EQ(g2.latitude(), 2.5);
    EXPECT_EQ(g2.longitude(), 1.3);
    EXPECT_EQ(g2.weight(), 3.45);
    EXPECT_NEAR(g2.getDistance2Pole(), 9729.57, 0.009);
    EXPECT_EQ(g2.getTourNumber(), 0);
}

TEST(GiftTest, equalityOperator) {
    CompareIDStrategy cs;
    Gift g1(1, 0.1, 0.1, 0.1, &cs);
    Gift g2(g1);

    EXPECT_EQ(g1, g2);

    g2 = {2, 0.1, 0.1, 0.1};
    EXPECT_NE(g1, g2);
}

TEST(GiftTest, inequalityOperator) {
    CompareIDStrategy cs;
    Gift g1(1, 0.1, 0.1, 0.1, &cs);
    Gift g2(2, 0.2, 0.2, 0.2, &cs);

    EXPECT_NE(g1, g2);
}

TEST(GiftTest, compareOperator_weight) {
    CompareWeightStrategy cs;
    Gift g1(1, 0.1, 0.1, 0.1, &cs);
    Gift g2(2, 0.2, 0.2, 0.2, &cs);

    EXPECT_NE(g1, g2);

    g2 = {2, 0.1, 0.1, 0.1};
    EXPECT_EQ(g1, g2);
}

TEST(GiftTest, compareOperator_distToPole) {
    CompareDistanceStrategy cs;
    Gift g1(1, 0.1, 0.1, 0.1, &cs);
    Gift g2(2, 0.2, 0.2, 0.2, &cs);

    EXPECT_NE(g1, g2);

    g2 = {2, 0.1, 0.1, 0.1};
    EXPECT_EQ(g1, g2);
}

TEST(GiftTest, compareOperator_distToRef) {
    CompareDistToRefStrategy cs;
    Gift g1(1, 0.1, 0.1, 0.1, &cs);
    Gift g2(2, 0.2, 0.2, 0.2, &cs);

    Coordinate ref = {30, 40};

    g1.setDistToRef(ref);
    g2.setDistToRef(ref);

    EXPECT_NE(g1, g2);
    EXPECT_GT(g1, g2);

    g2 = {2, 0.1, 0.1, 0.1};
    g2.setDistToRef(ref);
    EXPECT_EQ(g1, g2);
}

TEST(CompareStrategyTest, changeStrategyRuntime) {
    CompareWeightStrategy cws;
    CompareDistanceStrategy cds;

    Gift g1(1, 0.1, 0.1, 3.1, &cws);
    Gift g2(2, 0.2, 0.2, 3.1, &cws);

    EXPECT_EQ(g1, g2);
    EXPECT_EQ(g2, g1);

    g1.setCompareStrategy(&cds);
    g2.setCompareStrategy(&cds);

    EXPECT_NE(g1, g2);
    EXPECT_NE(g2, g1);
}
