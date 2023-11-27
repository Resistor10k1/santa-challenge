
#include "LoadStrategy.hpp"

int NaiveLoadingStrategy::loadSleigh(Santa& santa, Gift& gift, unsigned int tour_nbr)
{
    gift.setTourNumber(tour_nbr);
    return santa.load(gift);
}

std::vector<Gift>::iterator NaiveLoadingStrategy::loadSleigh(Santa& santa, const std::vector<Gift>::iterator& it_start,
                                                                const std::vector<Gift>::iterator& it_end,
                                                                unsigned int tour_nbr)
{
    auto gift = it_start;

    while((loadSleigh(santa, *gift, tour_nbr)==0) && (gift!=it_end))
    {
        ++gift;
    }

    return gift;
}