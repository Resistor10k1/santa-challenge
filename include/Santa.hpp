

#pragma once
#include "Gift.hpp"
#include <vector>


class Santa
{
    public:
        Santa(void);
        void load(const std::vector<Gift>& giftList);
        void start_delivering(void);

        double getSleighMaxLoad(void) const { return sleigh_max_load; }
        double getSleighWeight(void) const { return sleigh_weight; }

        double getSleighCurrentLoad(void) const { return sleigh_current_load; }
        Coordinate getCurrentPos(void) const { return current_pos; }
        double getWRW(void) const { return WRW; }
    
    private:
        const double sleigh_max_load = 1000.0;
        const double sleigh_weight = 10.0;
        double sleigh_current_load = 0.0;
        double WRW = 0.0;
        Coordinate current_pos;
        std::vector<Gift> loaded_gifts;
};
