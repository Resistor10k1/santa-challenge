/**
 * @file    TripManager.hpp
 * @date    2023-12-08
 * @author  Andri Trottmann
 */

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

        /**
         * @brief Starts searching for a best possible delivery pattern with the strategies given in the Ctor.
        */
        void startDelivery(void);

        unsigned int getNumberOfTours(void) const { return this->current_tour-1; }
        double getTotalWRW(void) const { return this->total_WRW; }
        std::vector<Gift> getTotalBestTour(void) const { return total_best_tour; }

        /**
         * @brief Verifies if the tour found with startDelivery is legit.
         * @return Returns true, if the tour is legit. Else returns false.
        */
        bool verify_tour(void);
    
    private:
        IDistributeStrategy& distributeStrategy; /**< Determines how an existing solution of a single tour is improved */
        ILoadStrategy& loadStrategy; /**< Determines how an initial soltuion is found */
        Santa santa; /**< Santa which is managed */
        std::vector<Gift>& gift_list; /**< List holding all the gifts which must be delivered */
        std::vector<unsigned int> giftID_list; /**< List of all the gifts' IDs. Used for verification */
        unsigned int current_tour = 0; /**< Counter for the tours */
        double total_WRW = 0.0; /**< Sum of all WRWs found with the tours */
        std::vector<Gift> total_best_tour; /**< Final sequence of delivery */
};

