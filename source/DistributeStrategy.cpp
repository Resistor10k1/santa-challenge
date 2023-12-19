
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

SimulatedAnnealingStrategy::SimulatedAnnealingStrategy() { }
SimulatedAnnealingStrategy::SimulatedAnnealingStrategy(const std::initializer_list<double> ilist)
{
    this->setMagicNumbers(ilist);
}

void SimulatedAnnealingStrategy::setMagicNumbers(const std::initializer_list<double> ilist)
{
    auto it = ilist.begin();
    unsigned int size = ilist.size();

    this->rndSwap_min_offset = (size >= 1) ? static_cast<unsigned int>(std::ceil(*it)) : 1;
    this->rndSwap_max_offset = (size >= 2) ? static_cast<unsigned int>(std::ceil(*(it+1))) : 15;
    this->cool_intervall = (size >= 3) ? static_cast<unsigned int>(std::ceil(*(it+2))) : 13;
    this->reheat_intervall = (size >= 4) ? static_cast<unsigned int>(std::ceil(*(it+3))) : 51;
    this->inital_temperature = (size >= 5) ? *(it+4) : 100000.0;
    this->final_temperature = (size >= 6) ? *(it+5) : 0.001;
}

std::array<double, 6> SimulatedAnnealingStrategy::getMagicNumbers(void)
{
    return {static_cast<double>(this->rndSwap_min_offset),
            static_cast<double>(this->rndSwap_max_offset),
            static_cast<double>(this->cool_intervall),
            static_cast<double>(this->reheat_intervall),
            this->inital_temperature,
            this->final_temperature
            };
}

void SimulatedAnnealingStrategy::distributeGifts(Santa& santa)
{
    double temp_WRW = __DBL_MAX__;
    double local_best;
    Santa local_santa(santa);
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
    double T = this->inital_temperature;
    double T_final = this->final_temperature;
    const double alpha = 0.9;
    unsigned int loop_cnt = 0;
    int nbr_improvements = 0;
    int nbr_reheats = 0;

    // TODO: Chose a different termination condition
    // for(unsigned int loop_cnt = 0; (T > T_final) && ((nbr_reheats-nbr_improvements) > 5); ++loop_cnt)
    while((T > T_final) /*&& ((nbr_reheats-nbr_improvements) < 15)*/)
    {
        applyRandomSwap(s, static_cast<unsigned int>(std::ceil(T)));

        // #pragma omp critical
        // {
        local_santa.load(s);
        temp_WRW = local_santa.calculateWRW();
        // }

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

        if((loop_cnt+1)%this->reheat_intervall == 0)
        {/* Reheat the system after 200 iterations */
            T *= 1.3;
            ++nbr_reheats;
        }

        if((loop_cnt+1)%this->cool_intervall == 0)
        // else if((nbr_improvements+1)%4 == 0)
        {/* Decrease temperature after 12 iterations */
            T *= alpha;
        }

        // if((loop_cnt-nbr_improvements)%101 == 0)
        // {
        //     s = s_star;
        // }

        ++loop_cnt;
    }
    
    #pragma omp critical
    {/* Get the best solution over all threads */
        if(local_best < this->best_WRW)
        {
#ifndef EVAL_MAGIC_NUMBERS
            std::cout <<"Thread-ID "<<omp_get_thread_num()<<": "<<T<<", "<<T_final<<", "<<nbr_reheats<<", "<<nbr_improvements<<", "<<loop_cnt<<", "<<this->best_WRW<<", "<<local_best<<std::endl;
#endif
            santa.load(s_star);
            // std::cout << omp_get_thread_num() << " S_star loaded" << std::endl;
            this->best_WRW = local_best;
            // std::cout << omp_get_thread_num() << ": best_WRW updated" << std::endl;
        }

        // std::cout << "Thread " << omp_get_thread_num() << " done." << std::endl;
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
    std::uniform_int_distribution<> offset_dist(this->rndSwap_min_offset, this->rndSwap_max_offset);

    for(unsigned int i=0; i<nbrOfPermutations; ++i)
    {
        int start_id = init_dist(gen);
        int offset_id = offset_dist(gen);

        if(((start_id+offset_id) >= giftList.size()))
        {
            if((start_id-offset_id) < 0)
            {
                offset_id = -1*start_id;
            }
            else
            {
                offset_id *= -1;
            }
        }

        std::iter_swap(giftList.begin()+start_id, giftList.begin()+start_id+offset_id);
    }
}
