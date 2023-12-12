/**
 * @file    DistributeStrategy.hpp
 * @brief   Contains different approaches on how to improve an existing solution.
 * @date    2023-12-08
 * @author  Andri Trottmann
 */

#pragma once
#include "Santa.hpp"
#include "Gift.hpp"
#include <vector>

/**
 * @brief Abstract class providing an interface to optimization strategies of all kind.
*/
class IDistributeStrategy
{
    public:
        /**
         * @brief Executes the optimization algorithm to improve an existing solution.
         * @param santa Holds the data
        */
        virtual void distributeGifts(Santa& santa) = 0;

        /**
         * @brief Returns the best found solution of the strategy
        */
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
};

/**
 * @brief Applies Simulated-Annealing optimization algorithm to an existing solution.
*/
class SimulatedAnnealingStrategy : public IDistributeStrategy
{
    public:
        void distributeGifts(Santa& santa) override;
    
    private:

        /**
         * @brief Swaps two destinations in a tour.
         * @details The destinations to swap are chosen randomly, but underlie some constraints.
         * The destinations can lie 1-5 positions apart from each other (index in the list).
         * @param nbrOfPermutations Determines how many random swaps are performed
        */
        void applyRandomSwap(std::vector<Gift>& giftList, unsigned int nbrOfPermutations);

        /**
         * @brief Returns uniformly distributes random value [0,1]
        */
        double rndU(void);
};