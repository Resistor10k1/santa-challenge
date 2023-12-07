
#include "DistributeStrategy.hpp"
#include "misc.hpp"
#include <vector>
#include <cmath>
#include <random>
#include <omp.h>
#include <iostream>


void NaiveStrategy::distributeGifts(Santa& santa)
{
    // std::vector<Gift> local_giftlist(santa.getLoadedGifts());
    // std::iter_swap(local_giftlist.begin()+5, local_giftlist.begin()+7);
    best_WRW = santa.calculateWRW();
}

void SimulatedAnnealingStrategy::distributeGifts(Santa& santa)
{
    double temp_WRW = __DBL_MAX__;
    double local_best;
    std::vector<Gift> s;
    #pragma omp critical
    {
        local_best = santa.calculateWRW();
        s = santa.getLoadedGifts();
    }

    auto s_star = s;
    double T = 10000;
    double T_final = 20;
    const double alpha = 0.99;
    unsigned int loop_cnt = 0;
    int nbr_improvements = 0;
    int nbr_reheats = 0;

    // TODO: Chose a different termination condition
    // for(unsigned int loop_cnt = 0; (T > T_final) && ((nbr_reheats-nbr_improvements) > 5); ++loop_cnt)
    while((T > T_final) && ((nbr_reheats-nbr_improvements) < 5))
    {
        applyRandomSwap(s);

        #pragma omp critical
        {
            santa.load(s);
            temp_WRW = santa.calculateWRW();
        }

        double D = temp_WRW - local_best;

        if((D < 0) || (std::exp(-D/T) > rndU()))
        {
            #pragma omp critical
            s = santa.getLoadedGifts();
        }

        if(temp_WRW < local_best)
        {
            s_star = s;
            local_best = temp_WRW;
        }

        if(loop_cnt == 200)
        {
            T *= 1.8;
            ++nbr_reheats;
        }
        else
        {
            T *= alpha;
        }
        ++loop_cnt;
    }
    
    #pragma omp critical
    {
        santa.load(s_star);
        this->best_WRW = local_best;
    }

    // #pragma omp critical
    // std::cout <<"Thread-ID "<<omp_get_thread_num()<<": "<<T<<", "<<T_final<<", "<<nbr_reheats<<", "<<nbr_improvements<<", "<<temp_WRW<<std::endl;
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