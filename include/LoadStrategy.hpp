/**
 * @file    LoadStrategy.hpp
 * @brief   Contains different approaches on how to find an initial solution.
 * @date    2023-12-08
 * @author  Andri Trottmann
 */

#pragma once
#include <vector>
#include "Gift.hpp"
#include "Santa.hpp"

/**
 * @brief Abstract class providing an interface
*/
class ILoadStrategy
{
    public:
        /**
         * @brief Can be used to apply some pre-processing to the destinations.
         * @details Default pre-processing function does nothing.
        */
        virtual void preprocessGifts(std::vector<Gift>& giftList) {}

        /**
         * @brief Add a single gift to the tour and set the tour number of the gift
        */
        int loadSleigh(Santa& santa, Gift& gift, unsigned int tour_nbr)
        {
            gift.setTourNumber(tour_nbr);
            int ret_val = santa.add(gift);

            if(ret_val != 0)
            {/* Un-set tour number if gift has no space in sleigh */
                gift.setTourNumber(0);
            }

            return ret_val;
        };

        /**
         * @brief Adds multiple gifts to the tour.
         * @details The adding can be performed with an arbitrary algorithm. Only gifts from giftList with tour_nr-attribute = 0 are 
         * considered.
         * @returns Returns a gift which cannot be added anymore, because the sleigh is full.
         * Returns giftList.end(), if no candidates are left in giftList (The tour_nr-attributes of all gifts in giftList != 0).
        */
        virtual std::vector<Gift>::iterator loadTourToSleigh(Santa& santa, std::vector<Gift>& giftList, 
                                                            const std::vector<Gift>::iterator& it_ref, 
                                                            unsigned int tour_nbr) = 0;
};

/**
 * @brief Loads the gifts one by one as they are given in the list without any optimization.
*/
class NaiveLoadingStrategy : public ILoadStrategy
{
    public:
        /**
         * @brief Does not perform any optimization, rather loads the gifts to santa how they are ordered in giftList
        */
        virtual std::vector<Gift>::iterator loadTourToSleigh(Santa& santa, std::vector<Gift>& giftList, 
                                                            const std::vector<Gift>::iterator& it_ref, 
                                                            unsigned int tour_nbr) override;
};

/**
 * @brief Loads the gifts in order of their distance to the north pole.
*/
class NearestLoadingStrategy : public ILoadStrategy
{
    public:
        /**
         * @brief Sorts the gifts according to their distance to the north pole.
        */
        void preprocessGifts(std::vector<Gift>& giftList) override;

        /**
         * @brief Does not perform additional optimization, rather loads the gifts to santa how they are ordered in giftList
        */
        virtual std::vector<Gift>::iterator loadTourToSleigh(Santa& santa, std::vector<Gift>& giftList, 
                                                            const std::vector<Gift>::iterator& it_ref, 
                                                            unsigned int tour_nbr) override;
};

/**
 * @brief Applies Nearest-Neighbour algorithm to determine an initial solution.
*/
class NNLoadingStrategy : public ILoadStrategy
{
    public:
        /**
         * @brief Sorts the gifts according to their distance to the north pole.
        */
        void preprocessGifts(std::vector<Gift>& giftList) override;

        /**
         * @brief Performs Nearest-Neighbour algorithm to load gifts to santa.
        */
        virtual std::vector<Gift>::iterator loadTourToSleigh(Santa& santa, std::vector<Gift>& giftList, 
                                                            const std::vector<Gift>::iterator& it_ref, 
                                                            unsigned int tour_nbr) override;
};

class PilotNNLoadingStrategy : public ILoadStrategy
{
    public:
        /**
         * @brief
        */
        void preprocessGifts(std::vector<Gift>& giftList) override;

        /**
         * @brief Performs Nearest-Neighbour algorithm with some preview (pilot) strategy
        */
        virtual std::vector<Gift>::iterator loadTourToSleigh(Santa& santa, std::vector<Gift>& giftList, 
                                                            const std::vector<Gift>::iterator& it_ref, 
                                                            unsigned int tour_nbr) override;
};