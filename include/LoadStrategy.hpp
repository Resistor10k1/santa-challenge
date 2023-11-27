
#pragma once
#include <vector>
#include "Gift.hpp"
#include "Santa.hpp"

class ILoadStrategy
{
    public:
        virtual int loadSleigh(Santa santa, const Gift& gift) = 0;
        virtual std::vector<Gift>::iterator loadSleigh(Santa santa, const std::vector<Gift>::iterator& gift_it, 
                                                        const std::vector<Gift>::iterator& it_end) = 0;
};

class KnapsackLoadingStrategy : public ILoadStrategy
{
    public:
        int loadSleigh(Santa santa, const Gift& gift) override;
        std::vector<Gift>::iterator loadSleigh(Santa santa, const std::vector<Gift>::iterator& gift_it,
                                                const std::vector<Gift>::iterator& it_end) override;
};