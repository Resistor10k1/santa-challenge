
#include "Santa.hpp"
#include "misc.hpp"

Santa::Santa(void)
{

}

void Santa::load(const std::vector<Gift>& giftList)
{
    sleigh_current_weight = 0.0;

    for(auto& gift : giftList)
    {
        if((sleigh_current_weight+gift.weight()) > sleigh_max_load)
            throw std::runtime_error("Sleigh max load exceeded!");
        
        sleigh_current_weight += gift.weight();
    }
}

void Santa::travel(const Gift& g)
{
    for(auto gift_ptr : delivered_Gifts)
    {
        if(gift_ptr->ID() == g.ID()) throw std::runtime_error("Gift has already been delivered!");
    }

    delivered_Gifts.push_back(&g);
    updateReindeerWeariness();
}

void Santa::updateReindeerWeariness(void)
{
    WRW += (sleigh_weight + sleigh_current_weight) * haversine(**(delivered_Gifts.rbegin()+1), 
                                                               **delivered_Gifts.rbegin(), degree);
}
