

#pragma once
#include "Gift.hpp"
#include <vector>


class Santa
{
    public:
        Santa(void);
        int load(const Gift& gift);
        int load(const std::vector<Gift>& giftList);
        void start_delivering(void);

        double getSleighMaxLoad(void) const { return this->sleigh_max_load; }
        double getSleighWeight(void) const { return this->sleigh_weight; }
        double getSleighCurrentLoad(void) const { return this->sleigh_current_load; }
        Coordinate getCurrentPos(void) const { return this->current_pos; }
        double getWRW(void) const { return this->WRW; }
        unsigned int getGiftToDeliver(void) const { return this->gifts_to_deliver; }
        std::vector<Gift>& getLoadedGifts(void) { return this->loaded_gifts; }
    
    private:
        const double sleigh_max_load = 1000.0;
        const double sleigh_weight = 10.0;
        double sleigh_current_load = 0.0;
        double WRW = 0.0;
        Coordinate current_pos;
        std::vector<Gift> loaded_gifts;
        unsigned int gifts_to_deliver = 0;
};
