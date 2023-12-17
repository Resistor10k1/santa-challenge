
#include "Santa.hpp"
#include "misc.hpp"

Santa::Santa(double max_load) : sleigh_max_load(max_load), current_pos({90.0, 0.0})
{

}

Santa::Santa(const Santa& s) :
    sleigh_max_load(s.sleigh_max_load), sleigh_weight(s.sleigh_weight), sleigh_current_load(s.sleigh_current_load), WRW(s.WRW)
{
    current_pos.latitude = s.current_pos.latitude;
    current_pos.longitude = s.current_pos.longitude;
    loaded_gifts = s.loaded_gifts;
}

void Santa::reset_attributes(void)
{
    this->sleigh_current_load = 0.0;
    this->WRW = 0.0;
    this->current_pos = {90.0, 0.0};
    this->loaded_gifts.clear();
}

int Santa::add(const Gift gift)
{
    if((sleigh_current_load+gift.weight()) > sleigh_max_load)
        return -1;
        
    sleigh_current_load += gift.weight();
    loaded_gifts.push_back(gift);
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
    }
    WRW += sleigh_weight * haversine(current_pos, {90.0, 0.0}, degree);
    this->current_pos = {90.0, 0.0};

    return this->WRW;
}

