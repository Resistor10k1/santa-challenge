

#include "formulas.hpp"
#include "gtest/gtest.h"
#include <iostream>
#include <numbers>


TEST(FormulasTest, calcHaversineDistance) {
    santa::Point p1 = {1, 1.1, 2.2};
    santa::Point p2 = {2, 1.1, 2.2};

    double distance = santa::haversine(p1, p2);
    
    EXPECT_NEAR(distance, 0.0, 1e-9);
}

TEST(FormulasTest, calcHaversineDistance2) {
    santa::Point p1 = {1, 1.3, 2.1};
    santa::Point p2 = {2, 1.3, 0.2};

    double distance = santa::haversine(p1, p2);
    
    EXPECT_NEAR(distance, 2794.863, 1e-9);
}

TEST(FormulasTest, calcHaversineDistance3) {
    santa::Point p1 = {1, 0.0, 0.0};
    santa::Point p2 = {2, 0.0, std::numbers::pi};

    double distance = santa::haversine(p1, p2);
    
    EXPECT_NEAR(distance, 40075 / 2.0, 1e-9);
}
