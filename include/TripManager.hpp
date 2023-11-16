
#pragma once
#include "misc.hpp"


class ITripManagerStrategy
{
    public:
        virtual Gift calculateNextDelivery(void) = 0;
};

class RandomTSPStrategy : public ITripManagerStrategy
{
    public:
        Gift calculateNextDelivery(void) override;
};


class TripManager
{
    public:
        TripManager(ITripManagerStrategy& strategy) : tripStrategy(strategy) {}
    
    private:
        ITripManagerStrategy& tripStrategy;
};

