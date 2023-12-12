
#include "LoadStrategy.hpp"
#include "misc.hpp"

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

    std::vector<Gift> local_giftList(giftList);

    santa.unloadSleigh();
    loadSleigh(santa, *it_ref, tour_nbr);

    sort_distToRef(local_giftList, (*ref_gift).getCoordinate());
}