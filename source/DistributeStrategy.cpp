
#include "DistributeStrategy.hpp"
#include "misc.hpp"
#include <vector>
#include <cmath>
#include <random>
#include <omp.h>
#include <iostream>


void NaiveStrategy::distributeGifts(Santa& santa)
{
    best_WRW = santa.calculateWRW();
}

void SimulatedAnnealingStrategy::distributeGifts(Santa& santa)
{
    double temp_WRW = __DBL_MAX__;
    double local_best;
    Santa local_santa = santa;
    std::vector<Gift> s;
    #pragma omp critical
    {
        local_best = local_santa.calculateWRW();
        this->best_WRW = local_best;
        // std::cout << "Start value " << omp_get_thread_num() << ": " << local_best << std::endl;
        s = local_santa.getLoadedGifts();
    }
    #pragma omp barrier
    auto s_star = s;
    double T = 100000;
    double T_final = 0.001;
    const double alpha = 0.9;
    unsigned int loop_cnt = 0;
    int nbr_improvements = 0;
    int nbr_reheats = 0;

    // TODO: Chose a different termination condition
    // for(unsigned int loop_cnt = 0; (T > T_final) && ((nbr_reheats-nbr_improvements) > 5); ++loop_cnt)
    while((T > T_final) /*&& ((nbr_reheats-nbr_improvements) < 15)*/)
    {
        applyRandomSwap(s, static_cast<unsigned int>(std::ceil(T)));

        #pragma omp critical
        {
            local_santa.load(s);
            temp_WRW = local_santa.calculateWRW();
        }

        double D = temp_WRW - local_best;

        if((D >= 0) || (std::exp(-D/T) <= rndU()))
        {/* Do not accept s */
            // #pragma omp critical
            // s = local_santa.getLoadedGifts();
            s = s_star;
        }

        if(temp_WRW < local_best)
        {
            s_star = s;
            local_best = temp_WRW;
            ++nbr_improvements;
        }

        if((loop_cnt+1)%51 == 0)
        {/* Reheat the system after 200 iterations */
            T *= 1.3;
            ++nbr_reheats;
        }
        else if((loop_cnt+1)%13 == 0)
        // else if((nbr_improvements+1)%4 == 0)
        {/* Decrease temperature after 12 iterations */
            T *= alpha;
        }

        // if(((loop_cnt-nbr_improvements)%100 == 0) && (loop_cnt > 100))
        // if((loop_cnt-nbr_improvements) > 100)
        // {/* Reset working solution to current best solution after 100 iterations without improvement */
        //     s = s_star;
        // }

        ++loop_cnt;
    }
    
    #pragma omp critical
    {/* Get the best solution over all threads */
        if(local_best < this->best_WRW)
        {
            std::cout <<"Thread-ID "<<omp_get_thread_num()<<": "<<T<<", "<<T_final<<", "<<nbr_reheats<<", "<<nbr_improvements<<", "<<loop_cnt<<", "<<this->best_WRW<<", "<<local_best<<std::endl;
            santa.load(s_star);
            this->best_WRW = local_best;
        }
    }
}

double SimulatedAnnealingStrategy::rndU(void)
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<> dist(0, 1);

    return dist(gen);
}

void SimulatedAnnealingStrategy::applyRandomSwap(std::vector<Gift>& giftList, unsigned int nbrOfPermutations)
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> init_dist(0, giftList.size()-1);
    std::uniform_int_distribution<> offset_dist(1, 15);

    for(unsigned int i=0; i<nbrOfPermutations; ++i)
    {
        int start_id = init_dist(gen);
        int offset_id = offset_dist(gen);

        if((start_id+offset_id) >= giftList.size())
        {
            offset_id *= -1;
        }

        std::iter_swap(giftList.begin()+start_id, giftList.begin()+start_id+offset_id);
    }
}