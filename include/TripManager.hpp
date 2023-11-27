
#pragma once
#include <vector>
#include "Santa.hpp"
#include "Gift.hpp"
#include "LoadStrategy.hpp"
#include "DistributeStrategy.hpp"


class TripManager
{
    public:
        TripManager(std::vector<Gift>& giftList, ILoadStrategy& ls, IDistributeStrategy& ds);
        void startDelivery(void);

        unsigned int getNumberOfTours(void) const { return this->current_tour; }
        double getSantasWRW(void) const { return this->global_WRW; }
    
    private:
        IDistributeStrategy& distributeStrategy;
        ILoadStrategy& loadStrategy;
        Santa santa;
        std::vector<Gift>& gift_list;
        unsigned int current_tour = 1;
        double global_WRW = 0.0;
};

