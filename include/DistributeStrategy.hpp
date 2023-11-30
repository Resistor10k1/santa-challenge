

#pragma one
#include "Santa.hpp"
#include "Gift.hpp"
#include <vector>


class IDistributeStrategy
{
    public:
        virtual void distributeGifts(Santa& santa) = 0;
        virtual double getSolution(void) const { return best_WRW; };
    protected:
        double best_WRW = __DBL_MAX__;
};

/**
 * @brief Distributes the gifts as they are loaded in santa's sleigh without any optimization.
*/
class NaiveStrategy : public IDistributeStrategy
{
    public:
        void distributeGifts(Santa& santa) override;
    // private:
    //     void _nearestNeighbourhood(void);
    //     void _2opt(void);
    //     void _bestImproving(void);
};

class SimulatedAnnealingStrategy : public IDistributeStrategy
{
    public:
        void distributeGifts(Santa& santa) override;
    
    private:
        void applyRandomSwap(std::vector<Gift>& giftList);
        double rndU(void);
};