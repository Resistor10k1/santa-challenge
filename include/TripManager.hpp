
#pragma once
#include <vector>
#include "Santa.hpp"
#include "Gift.hpp"


class ITripManagerStrategy
{
    public:
        virtual Gift calculateNextDelivery(void) = 0;
};

class PilotTSPStrategy : public ITripManagerStrategy
{
    public:
        Gift calculateNextDelivery(void) override;
    private:
        void _nearestNeighbourhood(void);
        void _2opt(void);
        void _bestImproving(void);
};


class TripManager
{
    public:
        TripManager(const std::vector<Gift>& giftList, ITripManagerStrategy& strategy);
        void startDelivery(void);
    
    private:
        ITripManagerStrategy& tripStrategy;
        Santa santa;
};

