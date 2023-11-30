
#include "TripManager.hpp"
#include <iostream>

TripManager::TripManager(std::vector<Gift>& giftList, ILoadStrategy& ls, IDistributeStrategy& ds) : 
                gift_list(giftList), loadStrategy(ls), distributeStrategy(ds), santa(1000.0)
{
}

void TripManager::startDelivery(void)
{
    this->loadStrategy.preprocessGifts(this->gift_list);

    auto gift_ptr = this->gift_list.begin();
    this->total_WRW = 0.0;
    this->current_tour = 0;

    do
    {
        std::cout << "Delivering tour number " << current_tour << " ... " << std::endl;
        ++this->current_tour;
        gift_ptr = this->loadStrategy.loadTourToSleigh(santa, gift_ptr, gift_list.end(), current_tour);
        this->distributeStrategy.distributeGifts(santa);

        this->total_WRW += this->distributeStrategy.getSolution();

        for(auto gift : santa.getLoadedGifts())
        {
            this->total_best_tour.push_back(gift);
        }
    }
    while(gift_ptr != gift_list.end());
}