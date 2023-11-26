
#include "TripManager.hpp"

TripManager::TripManager(const std::vector<Gift>& giftList, ITripManagerStrategy& strategy) :
        tripStrategy(strategy)
{

}
       

void TripManager::startDelivery(void)
{
    
}