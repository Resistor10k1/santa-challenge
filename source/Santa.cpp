
#include "Santa.hpp"
#include "misc.hpp"

Santa::Santa(void) : current_pos({90.0, 0.0})
{

}

void Santa::load(const std::vector<Gift>& giftList)
{
    current_pos = {90.0, 0.0};
    sleigh_current_load = 0.0;
    this->loaded_gifts = giftList;

    for(auto& gift : giftList)
    {
        if((sleigh_current_load+gift.weight()) > sleigh_max_load)
            throw std::runtime_error("Sleigh max load exceeded!");
        
        sleigh_current_load += gift.weight();
    }
}

void Santa::start_delivering(void)
{
    auto gift = loaded_gifts.begin();
    for(; gift != loaded_gifts.end(); ++gift)
    {
        WRW += (sleigh_weight + sleigh_current_load) * haversine(current_pos, gift->getCoordinate(), degree);
        sleigh_current_load -= gift->weight();
        current_pos = gift->getCoordinate();
    }
    WRW += sleigh_weight * haversine(current_pos, {90.0, 0.0}, degree);
    current_pos = {90.0, 0.0};
}

