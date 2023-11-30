
#include "Santa.hpp"
#include "misc.hpp"

Santa::Santa(double max_load) : sleigh_max_load(max_load), current_pos({90.0, 0.0})
{

}

void Santa::reset_attributes(void)
{
    this->sleigh_current_load = 0.0;
    this->WRW = 0.0;
    this->current_pos = {90.0, 0.0};
    this->loaded_gifts.clear();
}

int Santa::add(const Gift& gift)
{
    // Check if a delivery is not running
    // if(gifts_to_deliver == loaded_gifts.size())
    // {
        if((sleigh_current_load+gift.weight()) > sleigh_max_load)
            return -1; //throw std::runtime_error("Sleigh max load exceeded!");
        
        sleigh_current_load += gift.weight();
        loaded_gifts.push_back(gift);
        // ++gifts_to_deliver;
    // }
    // else
    // {
    //     return -2;
    // }
    return 0;
}

int Santa::load(const std::vector<Gift>& giftList)
{
    int ret_val = 0;
    this->reset_attributes();

    for(auto& gift : giftList)
    {
        ret_val = add(gift);
        if(ret_val != 0) break;
    }
    return ret_val;
}

double Santa::calculateWRW(void)
{
    this->WRW = 0.0;
    
    auto gift = loaded_gifts.begin();
    for(; gift != loaded_gifts.end(); ++gift)
    {
        this->WRW += (sleigh_weight + sleigh_current_load) * haversine(current_pos, gift->getCoordinate(), degree);
        this->sleigh_current_load -= gift->weight();
        this->current_pos = gift->getCoordinate();
        // --gifts_to_deliver;
    }
    WRW += sleigh_weight * haversine(current_pos, {90.0, 0.0}, degree);
    this->current_pos = {90.0, 0.0};

    // Reset sleigh
    // loaded_gifts.clear();
    // sleigh_current_load = 0.0;
    // gifts_to_deliver = 0;

    return this->WRW;
}

