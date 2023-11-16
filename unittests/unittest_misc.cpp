

#include "misc.hpp"
#include "gtest/gtest.h"
#include <iostream>
#include <numbers>


TEST(MiscTest, calcHaversineDistance) {
    Gift g1 = {1, 1.1, 2.2, 15.5};
    Gift g2 = {2, 1.1, 2.2, 100.2};

    double distance = haversine(g1, g2);
    
    EXPECT_NEAR(distance, 0.0, 1e-9);
}

TEST(MiscTest, calcHaversineDistance2) {
    Gift g1 = {1, 1.3, 2.1};
    Gift g2 = {2, 1.3, 0.2};

    double distance = haversine(g1, g2);
    
    EXPECT_NEAR(distance, 2794.863, 1e-9);
}

TEST(MiscTest, calcHaversineDistance3) {
    Gift g1 = {1, 0.0, 0.0};
    Gift g2 = {2, 0.0, std::numbers::pi};

    double distance = haversine(g1, g2);
    
    EXPECT_NEAR(distance, 40075 / 2.0, 1e-9);
}
