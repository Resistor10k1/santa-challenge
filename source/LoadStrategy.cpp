
#include "LoadStrategy.hpp"
#include "misc.hpp"
#include <algorithm>

std::vector<Gift>::iterator NaiveLoadingStrategy::loadTourToSleigh(Santa& santa, std::vector<Gift>& giftList, 
                                                                const std::vector<Gift>::iterator& it_ref, 
                                                                unsigned int tour_nbr)
{
    auto gift = giftList.begin();

    santa.unloadSleigh();

    while((loadSleigh(santa, *gift, tour_nbr)==0) && (gift!=giftList.end()))
    {
        ++gift;
    }

    return gift;
}

void NearestLoadingStrategy::preprocessGifts(std::vector<Gift>& giftList)
{
    sort_distance(giftList);
}

std::vector<Gift>::iterator NearestLoadingStrategy::loadTourToSleigh(Santa& santa, std::vector<Gift>& giftList, 
                                                                const std::vector<Gift>::iterator& it_ref, 
                                                                unsigned int tour_nbr)
{
    // auto gift = it_start;

    auto gift = giftList.begin();
    auto it_end = giftList.end();

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
}

std::vector<Gift>::iterator NNLoadingStrategy::loadTourToSleigh(Santa& santa, std::vector<Gift>& giftList, 
                                                                const std::vector<Gift>::iterator& it_ref, 
                                                                unsigned int tour_nbr)
{
    auto ref_gift = it_ref;
    auto it_start = giftList.begin();
    auto it_end = giftList.end();

    santa.unloadSleigh();
    loadSleigh(santa, *it_ref, tour_nbr);

    for(auto neighbour=it_end, gift_it=it_start; ref_gift!=it_end; neighbour=it_end, gift_it=it_start)
    {
        double current_nearest = __DBL_MAX__;

        while(gift_it != it_end)
        {/* Find the nearest neighbour */
            if(((*gift_it).getTourNumber() == 0) && (gift_it != ref_gift))
            {/* Gift has not been loaded yet */
                double dist_neighbour = haversine((*ref_gift).getCoordinate(), (*gift_it).getCoordinate(), degree);
                if(current_nearest > dist_neighbour)
                {
                    neighbour = gift_it;
                    current_nearest = dist_neighbour;
                }
            }
            ++gift_it;
        }

        if(neighbour == it_end)
        {/* No gifts left */
            return it_end;
        }
        else
        {
            ref_gift = neighbour;
            if(loadSleigh(santa, *neighbour, tour_nbr) != 0) return ref_gift;
        }
    }

    return ref_gift;
}

void NNClusterLoadingStrategy::preprocessGifts(std::vector<Gift>& giftList)
{
    sort_distance(giftList);
}

std::vector<Gift>::iterator NNClusterLoadingStrategy::loadTourToSleigh(Santa& santa, std::vector<Gift>& giftList, 
                                                                       const std::vector<Gift>::iterator& it_ref, 
                                                                       unsigned int tour_nbr)
{
    auto ref_gift = it_ref;
    auto it_start = giftList.begin();
    auto it_end = giftList.end();
    auto local_giftList(giftList);
    

    santa.unloadSleigh();
    // loadSleigh(santa, *it_ref, tour_nbr);

    sort_distToRef(local_giftList, (*ref_gift).getCoordinate());

    for(auto neighbour=it_start; neighbour!=it_end; ++neighbour)
    {
        if((*neighbour).getTourNumber() == 0)
        {
            // int ret_val = loadSleigh(santa, *neighbour, tour_nbr);
            if(loadSleigh(santa, *neighbour, tour_nbr) != 0)
            {
                return neighbour;
            }
        }
    }

    return it_end;
}




void PilotNNLoadingStrategy::preprocessGifts(std::vector<Gift>& giftList)
{
    sort_distance(giftList);
}

std::vector<Gift>::iterator PilotNNLoadingStrategy::loadTourToSleigh(Santa& santa, std::vector<Gift>& giftList, 
                                                                     const std::vector<Gift>::iterator& it_ref, 
                                                                     unsigned int tour_nbr)
{
    auto ref_gift = it_ref;
    auto it_start = giftList.begin();
    auto it_end = giftList.end();

    santa.unloadSleigh();
    loadSleigh(santa, *it_ref, tour_nbr);

    for(auto neighbour=it_end, gift_it=it_start; ref_gift!=it_end; neighbour=it_end, gift_it=it_start)
    {
        double current_nearest = __DBL_MAX__;

        while(gift_it != it_end)
        {/* Find the nearest neighbour */
            if(((*gift_it).getTourNumber() == 0) && (gift_it != ref_gift))
            {/* Gift has not been loaded yet */
                double dist_neighbour = haversine((*ref_gift).getCoordinate(), (*gift_it).getCoordinate(), degree);
                if(current_nearest > dist_neighbour)
                {
                    neighbour = gift_it;
                    current_nearest = dist_neighbour;
                }
            }
            ++gift_it;
        }

        if(neighbour == it_end)
        {/* No gifts left */
            return it_end;
        }
        else
        {
            // ref_gift = neighbour;
            // candidateGifts = giftList;
            // sort_distToRef(candidateGifts, (*neighbour).getCoordinate());

            if(tryLoadSleigh(santa, *neighbour, *ref_gift, giftList, tour_nbr) != 0)
            {
                ref_gift = neighbour; // optimize out
                return ref_gift;
            }
            else
            {
                ref_gift = neighbour;
            }
        }
    }

    return ref_gift;
}

int PilotNNLoadingStrategy::tryLoadSleigh(Santa& santa, Gift& neighbour, const Gift& ref, std::vector<Gift>& giftList, unsigned int tour_nbr)
{
    std::vector<Gift> local_giftList(giftList);
    // std::vector<Gift> candidateGifts;
    // std::vector<Gift> excludedGifts;
    int ret_val = -1;

    if(loadSleigh(santa, neighbour, tour_nbr) != 0)
    {
        CompareIDStrategy cis;
        ICompareStrategy<Gift>* cmp_ptr = giftList.front().getCompareStrategy();

        sort_distToRef(local_giftList, ref.getCoordinate());

        for(auto& gift : giftList)
        {
            gift.setCompareStrategy(&cis);
        }

        /* Find neighbour in giftList -> neighbour-index => ni*/
        auto newNeighbour = ++std::find(local_giftList.begin(), local_giftList.end(), neighbour);

        for(auto& gift : giftList)
        {
            gift.setCompareStrategy(cmp_ptr);
        }

        if(newNeighbour != giftList.end())
        {
            ret_val = tryLoadSleigh(santa, *newNeighbour, ref, giftList, tour_nbr);
            if(ret_val == 0)
            {
                neighbour = *newNeighbour;
            }
        }
    }
    else
    {
        ret_val = 0;
    }

    return ret_val;
}
