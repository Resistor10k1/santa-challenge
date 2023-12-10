
#include "gtest/gtest.h"
#include "Santa.hpp"
#include "Gift.hpp"
#include <vector>
#include <iostream>
#include <map>
#include "GiftFactory.hpp"
#include "misc.hpp"

using namespace std;

TEST(SantaTest, testBasicConfig) {
    Santa santa(1000.0);

    EXPECT_EQ(santa.getSleighMaxLoad(), 1000.0);
    EXPECT_EQ(santa.getSleighWeight(), 10.0);
    EXPECT_EQ(santa.getSleighCurrentLoad(), 0.0);
}

TEST(SantaTest, testLoading) {
    Santa santa(1000.0);
    GiftWeightFactory gwf;
    vector<Gift> giftList = {   gwf.produceGift(1,16.3457688674,6.30354512503,   1.0),
                                gwf.produceGift(2,12.494749307,28.6263955635,    15.5),
                                gwf.produceGift(3,27.794615136,60.0324947881,    8.5),
                                gwf.produceGift(4,44.4269923769,110.114216113,   1.0),
                                gwf.produceGift(5,-69.8540884125,87.9468778773,  25.6),
                                gwf.produceGift(6,53.5679698071,-71.3593080866,  38.5),
                                gwf.produceGift(7,12.9025840371,79.9669489093,   44.2),
                                gwf.produceGift(8,-6.29109889296,-64.8917508931, 1.0),
                                gwf.produceGift(9,-2.68531605304,111.089758191,  1.0),
                                gwf.produceGift(10,38.4288618657,101.973670947,  35.6),
                                gwf.produceGift(11,39.0901430146,72.6189278664,  27.9),
                                gwf.produceGift(12,-15.5749342275,39.5572954834, 14.6),
                                gwf.produceGift(13,73.1896497296,-106.604219923, 4.1),
                                gwf.produceGift(14,57.0682897236,134.171051275,  23.6),
                                gwf.produceGift(15,-68.884672727,61.214391432,   1.0)
                            };
    double sleigh_load_val = 0.0;
    for(auto& gift : giftList)
    {
        sleigh_load_val += gift.weight();
    }
    
    EXPECT_NO_THROW(santa.load(giftList));
    EXPECT_EQ(santa.getSleighCurrentLoad(), sleigh_load_val);
}

TEST(SantaTest, testOverLoading) {
    Santa santa(1000.0);
    GiftWeightFactory gwf;
    vector<Gift> giftList = {   gwf.produceGift(1,16.3457688674,6.30354512503,   100.0),
                                gwf.produceGift(2,12.494749307,28.6263955635,    150.5),
                                gwf.produceGift(3,27.794615136,60.0324947881,    80.5),
                                gwf.produceGift(4,44.4269923769,110.114216113,   10.0),
                                gwf.produceGift(5,-69.8540884125,87.9468778773,  250.6),
                                gwf.produceGift(6,53.5679698071,-71.3593080866,  380.5),
                                gwf.produceGift(7,12.9025840371,79.9669489093,   440.2),
                                gwf.produceGift(8,-6.29109889296,-64.8917508931, 10.0),
                                gwf.produceGift(9,-2.68531605304,111.089758191,  10.0),
                                gwf.produceGift(10,38.4288618657,101.973670947,  350.6),
                                gwf.produceGift(11,39.0901430146,72.6189278664,  270.9),
                                gwf.produceGift(12,-15.5749342275,39.5572954834, 140.6),
                                gwf.produceGift(13,73.1896497296,-106.604219923, 40.1),
                                gwf.produceGift(14,57.0682897236,134.171051275,  230.6),
                                gwf.produceGift(15,-68.884672727,61.214391432,   10.0)
                            };
    double sleigh_load_val = 972.1;
    
    EXPECT_EQ(santa.load(giftList), -1);
    EXPECT_EQ(santa.getSleighCurrentLoad(), sleigh_load_val);
}

TEST(SantaTest, checkDelivering) {
    Santa santa(1000.0);
    GiftWeightFactory gwf;
    vector<Gift> giftList = {   gwf.produceGift(1, 16.3457688674, 6.30354512503,   10.0),
                                gwf.produceGift(2, 12.494749307, 28.6263955635,    20.0),
                                gwf.produceGift(3, 27.794615136, 60.0324947881,    30.0),
                                gwf.produceGift(4, 44.4269923769, 110.114216113,   40.0),
                                gwf.produceGift(5, -69.8540884125, 87.9468778773,  50.0),
                                gwf.produceGift(6, 53.5679698071, -71.3593080866,  60.0),
                                gwf.produceGift(7, 12.9025840371, 79.9669489093,   70.0),
                                gwf.produceGift(8, -6.29109889296, -64.8917508931, 80.0),
                                gwf.produceGift(9, -2.68531605304, 111.089758191,  90.0),
                                gwf.produceGift(10, 38.4288618657, 101.973670947,  100.0)
                            };
    std::map<double, double> dist_weight_pairs = {  {8189.98810356308149494, 550+10.0},
                                                    {2440.35296477037491059, 540+10.0},
                                                    {3676.97213982595530979, 520+10.0},
                                                    {4777.20016673689951858, 490+10.0},
                                                    {12835.1437926769358455, 450+10.0},
                                                    {17925.1968019729938533, 400+10.0},
                                                    {12138.2132394660711725, 340+10.0},
                                                    {16096.7580068354254763, 270+10.0},
                                                    {18921.8049224806381972, 190+10.0},
                                                    {4666.6489449150622022, 100+10.0},
                                                    {5734.4568168356336173, 10.0} };
                            
    double WRW_val = 0.0;
    for(const auto& [dist, weight] : dist_weight_pairs)
    {
        WRW_val += dist * weight;
    }

    santa.load(giftList);
    EXPECT_EQ(santa.getSleighCurrentLoad(), 550.0);
    EXPECT_EQ(santa.getCurrentPos().latitude, 90.0);
    EXPECT_EQ(santa.getCurrentPos().longitude, 0.0);
    EXPECT_EQ(santa.getWRW(), 0.0);

    santa.calculateWRW();

    EXPECT_EQ(santa.getSleighCurrentLoad(), 0.0);
    EXPECT_EQ(santa.getCurrentPos().latitude, 90.0);
    EXPECT_EQ(santa.getCurrentPos().longitude, 0.0);
    EXPECT_NEAR(santa.getWRW(), WRW_val, 0.009);
}
