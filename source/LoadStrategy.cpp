
#include "LoadStrategy.hpp"

int KnapsackLoadingStrategy::loadSleigh(Santa santa, const Gift& gift)
{
    return santa.load(gift);
}

std::vector<Gift>::iterator KnapsackLoadingStrategy::loadSleigh(Santa santa, const std::vector<Gift>::iterator& it_start,
                                                                const std::vector<Gift>::iterator& it_end)
{
    auto gift = it_start;

    while((loadSleigh(santa, *gift)==0) && (gift!=it_end)) ++gift;

    return gift;
}