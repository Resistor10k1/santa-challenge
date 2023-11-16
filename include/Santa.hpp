

#pragma once
#include "misc.hpp"
#include <vector>


class Santa
{
    public:
        Santa(const std::vector<Gift>& global_points);
        void travel(const Gift& p);
    
    private:
        const double sleigh_max_weight = 1000.0;
        double sleigh_weight = 10.0;
        double WRW = 0.0;
        std::vector<Gift* const> delivered_Gifts;
};
