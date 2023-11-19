
#pragma once
#include <vector>
#include "misc.hpp"
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
};


class TripManager
{
    public:
        TripManager(const std::vector<Gift> giftList, ITripManagerStrategy& strategy);
        void startDelivery(void);
    
    private:
        ITripManagerStrategy& tripStrategy;
        Santa santa;
};

