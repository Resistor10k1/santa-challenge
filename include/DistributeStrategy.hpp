

#pragma one
#include "Santa.hpp"


class IDistributeStrategy
{
    public:
        virtual void distributeGifts(Santa& santa) = 0;
};

class NaiveStrategy : public IDistributeStrategy
{
    public:
        void distributeGifts(Santa& santa) override;
    // private:
    //     void _nearestNeighbourhood(void);
    //     void _2opt(void);
    //     void _bestImproving(void);
};