
#include "DistributeStrategy.hpp"
#include "misc.hpp"
#include <vector>
#include <cmath>
#include <random>


void NaiveStrategy::distributeGifts(Santa& santa)
{
    // std::vector<Gift> local_giftlist(santa.getLoadedGifts());
    // std::iter_swap(local_giftlist.begin()+5, local_giftlist.begin()+7);
    best_WRW = santa.calculateWRW();
}

void SimulatedAnnealingStrategy::distributeGifts(Santa& santa)
{
    double temp_WRW = __DBL_MAX__;
    this->best_WRW = santa.calculateWRW();
    auto s = santa.getLoadedGifts();
    auto s_star = s;
    double T = 4000;
    double T_final = 100;
    double alpha = 0.99;
    unsigned int loop_cnt = 0;


    while(T > T_final)
    {
        applyRandomSwap(s);
        // santa.unloadSleigh();
        santa.load(s);
        temp_WRW = santa.calculateWRW();

        double D = temp_WRW - this->best_WRW;

        if((D >= 0) || (std::exp(-D/T) > rndU()))
        {
            s = santa.getLoadedGifts();
        }

        if(temp_WRW < this->best_WRW)
        {
            s_star = s;
        }

        if(loop_cnt == 100)
        {
            T *= 3;
        }
        else
        {
            T *= alpha;
        }
        ++loop_cnt;
    }

    santa.load(s_star);
}

double SimulatedAnnealingStrategy::rndU(void)
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<> dist(0, 1);

    return dist(gen);
}

void SimulatedAnnealingStrategy::applyRandomSwap(std::vector<Gift>& giftList)
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dist(0, giftList.size()-1);

    int id_1 = dist(gen);
    int id_2 = dist(gen);

    std::iter_swap(giftList.begin()+id_1, giftList.begin()+id_2);
}