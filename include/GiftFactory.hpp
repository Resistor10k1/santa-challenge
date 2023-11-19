

#pragma once
#include "Gift.hpp"

class IGiftFactory
{
    public:
        virtual Gift produceGift(unsigned int id, double latitude, double longitude, double weight) = 0;
};

class GiftWeightFactory : public IGiftFactory
{
    public:
        GiftWeightFactory(void) : g(cs) {}
        Gift produceGift(unsigned int id, double latitude, double longitude, double weight) override
        {
            g = { static_cast<double>(id), latitude, longitude, weight };
            return g;
        }
    
    private:
        CompareWeightStrategy cs;
        Gift g;
};