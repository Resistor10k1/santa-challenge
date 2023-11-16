

#include "gtest/gtest.h"
#include <iostream>
#include <numbers>
#include <filesystem>
#include <vector>
#include "Gift.hpp"
#include "misc.hpp"

namespace fs = std::filesystem;


TEST(MiscTest, calcHaversineDistance) {
    Gift g1 = {1.0, 1.1, 2.2, 15.5};
    Gift g2 = {2, 1.1, 2.2, 100.2};

    double distance = haversine(g1, g2);
    
    EXPECT_NEAR(distance, 0.0, 1e-4);
}

TEST(MiscTest, calcHaversineDistance2) {
    Gift g1 = {1, 1.3, 2.1, 49};
    Gift g2 = {2, 1.3, 0.2, 34};

    double distance = haversine(g1, g2);
    
    EXPECT_NEAR(distance, 2794.863, 1e-4);
}

TEST(MiscTest, calcHaversineDistance3) {
    Gift g1 = {1, 0.0, 0.0, 9834};
    Gift g2 = {2, 0.0, std::numbers::pi, 82};

    double distance = haversine(g1, g2);
    
    EXPECT_NEAR(distance, 20015.114352, 1e-4);
}

TEST(MiscTest, readFile) {
    fs::path path = fs::current_path() / "data/example_data.csv";
    std::vector<Gift> giftList;
    // std::vector<Gift> giftList_val = {  {1,16.3457688674,6.30354512503,1.0},
    //                                     {2,12.494749307,28.6263955635,15.5244795726},
    //                                     {3,27.794615136,60.0324947881,8.05849862195},
    //                                     {4,44.4269923769,110.114216113,1.0},
    //                                     {5,-69.8540884125,87.9468778773,25.0888919163},
    //                                     {6,53.5679698071,-71.3593080866,38.0001512626},
    //                                     {7,12.9025840371,79.9669489093,44.2066162418},
    //                                     {8,-6.29109889296,-64.8917508931,1.0},
    //                                     {9,-2.68531605304,111.089758191,1.0},
    //                                     {10,38.4288618657,101.973670947,35.7013112369},
    //                                     {11,39.0901430146,72.6189278664,27.579921436},
    //                                     {12,-15.5749342275,39.5572954834,14.5519741369},
    //                                     {13,73.1896497296,-106.604219923,4.98356232888},
    //                                     {14,57.0682897236,134.171051275,23.6559977941},
    //                                     {15,-68.884672727,61.214391432,1.0}
    //                                 };

    // readGiftsFromFile(path, ',', giftList);
}
