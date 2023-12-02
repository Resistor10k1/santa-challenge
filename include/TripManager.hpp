
#pragma once
#include <vector>
#include "Santa.hpp"
#include "Gift.hpp"
#include "LoadStrategy.hpp"
#include "DistributeStrategy.hpp"


/**
 * @brief Manages a santa and determines how the gifts are delivered by the injected ILoadStrategy and IDistributeStrategy.
*/
class TripManager
{
    public:
        TripManager(std::vector<Gift>& giftList, ILoadStrategy& ls, IDistributeStrategy& ds);
        void startDelivery(void);

        unsigned int getNumberOfTours(void) const { return this->current_tour-1; }
        double getTotalWRW(void) const { return this->total_WRW; }
        std::vector<Gift> getTotalBestTour(void) const { return total_best_tour; }

        bool verify_tour(void);
    
    private:
        IDistributeStrategy& distributeStrategy;
        ILoadStrategy& loadStrategy;
        Santa santa;
        std::vector<Gift>& gift_list;
        std::vector<unsigned int> giftID_list;
        unsigned int current_tour = 0;
        double total_WRW = 0.0;
        std::vector<Gift> total_best_tour;
};

