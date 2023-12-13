
#include "gtest/gtest.h"
#include "DistributeStrategy.hpp"


TEST(SATest, settingMagicNumbers) {
    std::initializer_list<double> default_nbrs = {1, 15, 13, 51, 100000.0, 0.001};
    std::initializer_list<double> new_nbrs = {1.3, 43.1, 139.9, 981.34, 2, 1234.001};
    std::initializer_list<double> new_nbrs_val = {2, 44, 140, 982, 2.0, 1234.001};
    std::array<double, 6> temp;

    SimulatedAnnealingStrategy sa_strat;
    temp = sa_strat.getMagicNumbers();
    for(auto it=default_nbrs.begin(), temp_it=temp.cbegin(); it!=default_nbrs.end(); ++it, ++temp_it)
    {
        EXPECT_EQ(*temp_it, *it);
    }
    sa_strat.setMagicNumbers(new_nbrs);
    temp = sa_strat.getMagicNumbers();
    for(auto it=new_nbrs_val.begin(), temp_it=temp.cbegin(); it!=new_nbrs_val.end(); ++it, ++temp_it)
    {
        EXPECT_EQ(*temp_it, *it);
    }
}
