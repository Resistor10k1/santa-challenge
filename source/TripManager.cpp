
#include "TripManager.hpp"
#include <iostream>

TripManager::TripManager(std::vector<Gift>& giftList, ILoadStrategy& ls, IDistributeStrategy& ds) : 
                gift_list(giftList), loadStrategy(ls), distributeStrategy(ds)
{
}

void TripManager::startDelivery(void)
{
    auto gift_ptr = this->gift_list.begin();
    this->global_WRW = 0.0;
    this->current_tour = 1;

    do
    {
        // std::cout << "Delivering tour number " << current_tour << " ... " << std::endl;
        gift_ptr = this->loadStrategy.loadSleigh(santa, gift_ptr, gift_list.end(), current_tour);
        this->distributeStrategy.distributeGifts(santa);

        this->global_WRW += this->santa.getWRW();
        ++this->current_tour;
    }
    while(gift_ptr != gift_list.end());
}