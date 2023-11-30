
#include "LoadStrategy.hpp"
#include "misc.hpp"

std::vector<Gift>::iterator NaiveLoadingStrategy::loadTourToSleigh(Santa& santa, const std::vector<Gift>::iterator& it_start,
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

/**
 * @paragraph Loads the gifts in ascending order of the distance to the north pole.
*/

void NearestLoadingStrategy::preprocessGifts(std::vector<Gift>& giftList)
{
    sort_distance(giftList);
}

std::vector<Gift>::iterator NearestLoadingStrategy::loadTourToSleigh(Santa& santa, const std::vector<Gift>::iterator& it_start,
                                                                const std::vector<Gift>::iterator& it_end,
                                                                unsigned int tour_nbr)
{
    auto gift = it_start;
    santa.unloadSleigh();

    while((loadSleigh(santa, *gift, tour_nbr)==0) && (gift!=it_end))
    {
        ++gift;
    }

    return gift;
}


void NNLoadingStrategy::preprocessGifts(std::vector<Gift>& giftList)
{
    sort_distance(giftList);

    for(auto gift : giftList)
    {
        this->dist_matrix.push_back(std::vector<Gift>(giftList.size()));

        for(auto other : giftList)
        {
            
        }
    }
}

std::vector<Gift>::iterator NNLoadingStrategy::loadTourToSleigh(Santa& santa, const std::vector<Gift>::iterator& it_start,
                                                                const std::vector<Gift>::iterator& it_end,
                                                                unsigned int tour_nbr)
{
    auto gift = it_start;
    santa.unloadSleigh();

    while((loadSleigh(santa, *gift, tour_nbr)==0) && (gift!=it_end))
    {
        ++gift;
    }

    return gift;
}