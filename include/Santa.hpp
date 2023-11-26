

#pragma once
#include "Gift.hpp"
#include <vector>


class Santa
{
    public:
        Santa(void);
        void load(const std::vector<Gift>& giftList);
        void travel(const Gift& g);

        double getSleighMaxLoad(void) const { return sleigh_max_load; }
        double getSleighWeight(void) const { return sleigh_weight; }
        double getSleighCurrentWeight(void) const { return sleigh_current_weight; }
    
    private:
        const double sleigh_max_load = 1000.0;
        const double sleigh_weight = 10.0;
        double sleigh_current_weight = 0.0;
        double WRW = 0.0;
        std::vector<const Gift*> delivered_Gifts;

        void updateReindeerWeariness(void);
};
