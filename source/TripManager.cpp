
#include "TripManager.hpp"
#include <iostream>

TripManager::TripManager(std::vector<Gift>& giftList, ILoadStrategy& ls, IDistributeStrategy& ds) : 
                gift_list(giftList), loadStrategy(ls), distributeStrategy(ds), santa(1000.0)
{
    for(auto gift : giftList)
    {
        giftID_list.push_back(gift.ID());
    }
}

void TripManager::startDelivery(void)
{
    this->loadStrategy.preprocessGifts(this->gift_list);

    auto gift_ptr = this->gift_list.begin();
    this->total_WRW = 0.0;
    this->current_tour = 1;

    for(; gift_ptr!=gift_list.end(); ++this->current_tour)
    {
        std::cout << "Delivering tour number " << this->current_tour << " ... " << std::endl;
        
        gift_ptr = this->loadStrategy.loadTourToSleigh(santa, gift_list, gift_ptr, current_tour);

        #pragma omp parallel default(none) shared(santa)
        this->distributeStrategy.distributeGifts(santa);

        this->total_WRW += this->distributeStrategy.getSolution();

        for(auto gift : santa.getLoadedGifts())
        {
            this->total_best_tour.push_back(gift);
        }

        // Sort gifts according to the disatnce to north pole
        this->loadStrategy.preprocessGifts(this->gift_list);

        for(int index=0; index<gift_list.size(); ++index)
        {/* Get closest gift not yet delivered */
            if(gift_list.at(index).getTourNumber() == 0)
            {
                gift_ptr = gift_list.begin() + index;
                break;
            }
        }
    }

    // Improve existing tours


}

bool TripManager::verify_tour(void)
{
    unsigned int hit_counter = 0;
    for(auto gift : total_best_tour)
    {
        if(std::find(giftID_list.begin(), giftID_list.end(), gift.ID()) != giftID_list.end())
        {
            ++hit_counter;
        }
    }

    return ((hit_counter == total_best_tour.size()) && (giftID_list.size() == total_best_tour.size()));
}