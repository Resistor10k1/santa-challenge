

#include "gtest/gtest.h"
#include <iostream>
#include <numbers>
#include <filesystem>
#include <vector>
#include "Gift.hpp"
#include "misc.hpp"
#include "GiftFactory.hpp"

namespace fs = std::filesystem;


TEST(MiscTest, calcHaversineDistance) {
    Coordinate p1 = {1.1, 2.2};
    Coordinate p2 = {1.1, 2.2};

    double distance = haversine(p1, p2, radiant);
    
    EXPECT_NEAR(distance, 0.0, 1e-4);
}

TEST(MiscTest, calcHaversineDistance2) {
    Coordinate p1 = {1.3, 2.1};
    Coordinate p2 = {1.3, 0.2};

    double distance = haversine(p1, p2, radiant);
    
    EXPECT_NEAR(distance, 2794.863, 1e-4);
}

TEST(MiscTest, calcHaversineDistance3) {
    Coordinate p1 = {0.0, 0.0};
    Coordinate p2 = {0.0, std::numbers::pi};

    double distance = haversine(p1, p2, radiant);
    
    EXPECT_NEAR(distance, 20015.114352, 1e-4);
}

TEST(MiscTest, calcHaversineDistanceDegree1) {
    Coordinate p1 = {0.0, 0.0};
    Coordinate p2 = {0.0, 180.0};

    double distance = haversine(p1, p2, degree);
    
    EXPECT_NEAR(distance, 20015.114352, 1e-4);
}

TEST(MiscTest, calcHaversineDistanceDegree2) {
    Coordinate p1 = {90.0, 0.0};
    Coordinate p2 = {53.5679698071,-71.3593080866};

    double distance = haversine(p1, p2, degree);
    
    EXPECT_NEAR(distance, 4051.0625021844452931, 1e-4);
}

TEST(MiscTest, calcHaversineDistanceDegree3) {
    Coordinate p1 = {90.0, 0.0};
    Coordinate p2 = {-68.884672727,61.214391432};

    double distance = haversine(p1, p2, degree);
    
    EXPECT_NEAR(distance, 17667.1938524478464387, 1e-4);
}

TEST(MiscTest, calcHaversineDistanceDegree4) {
    Coordinate p1 = {0.0, 175};
    Coordinate p2 = {0.0, -175};

    double distance = haversine(p1, p2, degree);
    
    EXPECT_NEAR(distance, 1111.95, 0.009);
}

TEST(MiscTest, readFile) {
    GiftWeightFactory gwf;
    fs::path path = "../data/example_data.csv";
    std::vector<Gift> giftList;
    std::vector<Gift> giftList_val = {  gwf.produceGift(1,16.3457688674,6.30354512503,1.0),
                                        gwf.produceGift(2,12.494749307,28.6263955635,15.5244795726),
                                        gwf.produceGift(3,27.794615136,60.0324947881,8.05849862195),
                                        gwf.produceGift(4,44.4269923769,110.114216113,1.0),
                                        gwf.produceGift(5,-69.8540884125,87.9468778773,25.0888919163),
                                        gwf.produceGift(6,53.5679698071,-71.3593080866,38.0001512626),
                                        gwf.produceGift(7,12.9025840371,79.9669489093,44.2066162418),
                                        gwf.produceGift(8,-6.29109889296,-64.8917508931,1.0),
                                        gwf.produceGift(9,-2.68531605304,111.089758191,1.0),
                                        gwf.produceGift(10,38.4288618657,101.973670947,35.7013112369),
                                        gwf.produceGift(11,39.0901430146,72.6189278664,27.579921436),
                                        gwf.produceGift(12,-15.5749342275,39.5572954834,14.5519741369),
                                        gwf.produceGift(13,73.1896497296,-106.604219923,4.98356232888),
                                        gwf.produceGift(14,57.0682897236,134.171051275,23.6559977941),
                                        gwf.produceGift(15,-68.884672727,61.214391432,1.0)
                                    };

    readGiftsFromFile(path, ',', giftList, gwf);

    for(int i=0; i<15; ++i)
    {
        EXPECT_EQ(giftList.at(i).ID(), giftList_val.at(i).ID());
        EXPECT_EQ(giftList.at(i).latitude(), giftList_val.at(i).latitude());
        EXPECT_EQ(giftList.at(i).longitude(), giftList_val.at(i).longitude());
        EXPECT_EQ(giftList.at(i).weight(), giftList_val.at(i).weight());
    }
}

TEST(MiscTest, meanWeight) {
    GiftWeightFactory gwf;
    std::vector<Gift> giftList = {  gwf.produceGift(1,16.3457688674,6.30354512503,1.0),
                                    gwf.produceGift(2,12.494749307,28.6263955635,15.5244795726),
                                    gwf.produceGift(3,27.794615136,60.0324947881,8.05849862195),
                                    gwf.produceGift(4,44.4269923769,110.114216113,1.0),
                                    gwf.produceGift(5,-69.8540884125,87.9468778773,25.0888919163),
                                    gwf.produceGift(6,53.5679698071,-71.3593080866,38.0001512626),
                                    gwf.produceGift(7,12.9025840371,79.9669489093,44.2066162418),
                                    gwf.produceGift(8,-6.29109889296,-64.8917508931,1.0),
                                    gwf.produceGift(9,-2.68531605304,111.089758191,1.0),
                                    gwf.produceGift(10,38.4288618657,101.973670947,35.7013112369),
                                    gwf.produceGift(11,39.0901430146,72.6189278664,27.579921436),
                                    gwf.produceGift(12,-15.5749342275,39.5572954834,14.5519741369),
                                    gwf.produceGift(13,73.1896497296,-106.604219923,4.98356232888),
                                    gwf.produceGift(14,57.0682897236,134.171051275,23.6559977941),
                                    gwf.produceGift(15,-68.884672727,61.214391432,1.0)
                                };
    double weight_val = 16.15676;

    EXPECT_NEAR(mean_weight(giftList), weight_val, 1e-6);
}

TEST(MiscTest, meanDistance) {
    GiftWeightFactory gwf;
    std::vector<Gift> giftList = {  gwf.produceGift(1,16.3457688674,6.30354512503,1.0),
                                    gwf.produceGift(2,12.494749307,28.6263955635,15.5244795726),
                                    gwf.produceGift(3,27.794615136,60.0324947881,8.05849862195),
                                    gwf.produceGift(4,44.4269923769,110.114216113,1.0),
                                    gwf.produceGift(5,-69.8540884125,87.9468778773,25.0888919163),
                                    gwf.produceGift(6,53.5679698071,-71.3593080866,38.0001512626),
                                    gwf.produceGift(7,12.9025840371,79.9669489093,44.2066162418),
                                    gwf.produceGift(8,-6.29109889296,-64.8917508931,1.0),
                                    gwf.produceGift(9,-2.68531605304,111.089758191,1.0),
                                    gwf.produceGift(10,38.4288618657,101.973670947,35.7013112369),
                                    gwf.produceGift(11,39.0901430146,72.6189278664,27.579921436),
                                    gwf.produceGift(12,-15.5749342275,39.5572954834,14.5519741369),
                                    gwf.produceGift(13,73.1896497296,-106.604219923,4.98356232888),
                                    gwf.produceGift(14,57.0682897236,134.171051275,23.6559977941),
                                    gwf.produceGift(15,-68.884672727,61.214391432,1.0)
                                };
    double distance_val = 8435.855395;

    EXPECT_NEAR(mean_distance(giftList), distance_val, 1e-6);
}

TEST(MiscTest, sortByID) {
    GiftWeightFactory gwf;
    std::vector<Gift> giftList = {  gwf.produceGift(30, 16.3457688674, 6.30354512503, 1.0),
                                    gwf.produceGift(34, 12.494749307, 28.6263955635, 15.5244795726),
                                    gwf.produceGift(37, 27.794615136, 60.0324947881, 8.05849862195),
                                    gwf.produceGift(4, 44.4269923769, 110.114216113, 1.0),
                                    gwf.produceGift(80, -69.8540884125, 87.9468778773, 25.0888919163),
                                    gwf.produceGift(112, 53.5679698071, -71.3593080866, 38.0001512626),
                                    gwf.produceGift(7, 12.9025840371, 79.9669489093, 44.2066162418),
                                    gwf.produceGift(81, -6.29109889296, -64.8917508931, 1.0),
                                    gwf.produceGift(9, -2.68531605304, 111.089758191, 1.0),
                                    gwf.produceGift(1, 38.4288618657, 101.973670947, 35.7013112369),
                                    gwf.produceGift(101, 39.0901430146, 72.6189278664, 27.579921436),
                                    gwf.produceGift(2, -15.5749342275, 39.5572954834, 14.5519741369),
                                    gwf.produceGift(17, 73.1896497296, -106.604219923, 4.98356232888),
                                    gwf.produceGift(18, 57.0682897236, 134.171051275, 23.6559977941),
                                    gwf.produceGift(15, -68.884672727, 61.214391432, 1.0)
                                };

    sort_id(giftList);

    unsigned int id = 0;
    for(auto& gift : giftList)
    {
        EXPECT_GT(gift.ID(), id);
        id = gift.ID();
    }
}

TEST(MiscTest, sortByWeight) {
    GiftDistanceFactory gwf;
    std::vector<Gift> giftList = {  gwf.produceGift(30, 16.3457688674, 6.30354512503, 1.0),
                                    gwf.produceGift(34, 12.494749307, 28.6263955635, 15.5244795726),
                                    gwf.produceGift(37, 27.794615136, 60.0324947881, 8.05849862195),
                                    gwf.produceGift(4, 44.4269923769, 110.114216113, 1.0),
                                    gwf.produceGift(80, -69.8540884125, 87.9468778773, 25.0888919163),
                                    gwf.produceGift(112, 53.5679698071, -71.3593080866, 38.0001512626),
                                    gwf.produceGift(7, 12.9025840371, 79.9669489093, 44.2066162418),
                                    gwf.produceGift(81, -6.29109889296, -64.8917508931, 1.0),
                                    gwf.produceGift(9, -2.68531605304, 111.089758191, 1.0),
                                    gwf.produceGift(1, 38.4288618657, 101.973670947, 35.7013112369),
                                    gwf.produceGift(101, 39.0901430146, 72.6189278664, 27.579921436),
                                    gwf.produceGift(2, -15.5749342275, 39.5572954834, 14.5519741369),
                                    gwf.produceGift(17, 73.1896497296, -106.604219923, 4.98356232888),
                                    gwf.produceGift(18, 57.0682897236, 134.171051275, 23.6559977941),
                                    gwf.produceGift(15, -68.884672727, 61.214391432, 1.0)
                                };

    sort_weight(giftList);

    double weight_val = 0.0;
    for(auto& gift : giftList)
    {
        EXPECT_GE(gift.weight(), weight_val);
        weight_val = gift.weight();
    }
}

TEST(MiscTest, sortByDistance) {
    GiftWeightFactory gwf;
    std::vector<Gift> giftList = {  gwf.produceGift(30, 16.3457688674, 6.30354512503, 1.0),
                                    gwf.produceGift(34, 12.494749307, 28.6263955635, 15.5244795726),
                                    gwf.produceGift(37, 27.794615136, 60.0324947881, 8.05849862195),
                                    gwf.produceGift(4, 44.4269923769, 110.114216113, 1.0),
                                    gwf.produceGift(80, -69.8540884125, 87.9468778773, 25.0888919163),
                                    gwf.produceGift(112, 53.5679698071, -71.3593080866, 38.0001512626),
                                    gwf.produceGift(7, 12.9025840371, 79.9669489093, 44.2066162418),
                                    gwf.produceGift(81, -6.29109889296, -64.8917508931, 1.0),
                                    gwf.produceGift(9, -2.68531605304, 111.089758191, 1.0),
                                    gwf.produceGift(1, 38.4288618657, 101.973670947, 35.7013112369),
                                    gwf.produceGift(101, 39.0901430146, 72.6189278664, 27.579921436),
                                    gwf.produceGift(2, -15.5749342275, 39.5572954834, 14.5519741369),
                                    gwf.produceGift(17, 73.1896497296, -106.604219923, 4.98356232888),
                                    gwf.produceGift(18, 57.0682897236, 134.171051275, 23.6559977941),
                                    gwf.produceGift(15, -68.884672727, 61.214391432, 1.0)
                                };
    
    sort_distance(giftList);

    double distance_val = 0.0;
    for(auto& gift : giftList)
    {
        EXPECT_GT(gift.getDistance2Pole(), distance_val);
        distance_val = gift.getDistance2Pole();
    }
}

TEST(MiscTest, sortByDistance2Ref) {
    GiftWeightFactory gwf;
    std::vector<Gift> giftList = {  gwf.produceGift(30, 16.3457688674, 6.30354512503, 1.0),             //  2867.98 x
                                    gwf.produceGift(34, 12.494749307, 28.6263955635, 15.5244795726),    //  4099.4 x
                                    gwf.produceGift(37, 27.794615136, 60.0324947881, 8.05849862195),    //  5315.51 x
                                    gwf.produceGift(4, 44.4269923769, 110.114216113, 1.0),              //  7972.73 x
                                    gwf.produceGift(80, -69.8540884125, 87.9468778773, 25.0888919163),  // 14145.29 x
                                    gwf.produceGift(112, 53.5679698071, -71.3593080866, 38.0001512626), //  5450.26 x
                                    gwf.produceGift(7, 12.9025840371, 79.9669489093, 44.2066162418),    //  7964.36 x
                                    gwf.produceGift(81, -6.29109889296, -64.8917508931, 1.0),           //  8709.81 x
                                    gwf.produceGift(9, -2.68531605304, 111.089758191, 1.0),             // 11679.2 x
                                    gwf.produceGift(1, 38.4288618657, 101.973670947, 35.7013112369),    //  7884.56 x
                                    gwf.produceGift(101, 39.0901430146, 72.6189278664, 27.579921436),   //  5708.92 x
                                    gwf.produceGift(2, -15.5749342275, 39.5572954834, 14.5519741369),   //  7407.7 x
                                    gwf.produceGift(17, 73.1896497296, -106.604219923, 4.98356232888),  //  6161.17 x
                                    gwf.produceGift(18, 57.0682897236, 134.171051275, 23.6559977941),   //  8088.26 x
                                    gwf.produceGift(15, -68.884672727, 61.214391432, 1.0)               // 13214.62 x
                                };
    std::vector<unsigned int> giftIDs_val = { 
        30, 34, 37, 112, 101, 17, 2, 1, 7, 4, 18, 81, 9, 15, 80
    };
    
    sort_distToRef(giftList, {42.0, 3.2});

    for(unsigned int i=0; i<giftList.size(); ++i)
    {
        EXPECT_EQ(giftList.at(i).ID(), giftIDs_val.at(i));
    }
}



