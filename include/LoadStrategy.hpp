
#pragma once
#include <vector>
#include "Gift.hpp"
#include "Santa.hpp"

class ILoadStrategy
{
    public:
        virtual int loadSleigh(Santa& santa, Gift& gift, unsigned int tour_nbr) = 0;
        virtual std::vector<Gift>::iterator loadSleigh(Santa& santa, const std::vector<Gift>::iterator& gift_it, 
                                                        const std::vector<Gift>::iterator& it_end, 
                                                        unsigned int tour_nbr) = 0;
};

class NaiveLoadingStrategy : public ILoadStrategy
{
    public:
        int loadSleigh(Santa& santa, Gift& gift, unsigned int tour_nbr) override;
        std::vector<Gift>::iterator loadSleigh(Santa& santa, const std::vector<Gift>::iterator& gift_it,
                                                const std::vector<Gift>::iterator& it_end, unsigned int tour_nbr) override;
};