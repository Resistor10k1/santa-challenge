/**
 * @file    Santa.hpp
 * @date    2023-12-08
 * @author  Andri Trottmann
 */

#pragma once
#include "Gift.hpp"
#include <vector>
#include <iostream>


/**
 * @brief Class abstracting santa.
*/
class Santa
{
    public:
        Santa(double max_load);

        Santa(const Santa& s);

        /**
         * @brief Adds a single gift to the sleigh.
         * @return Returns 0 if gift could be added.
         * Returns -1 if sleigh_max_load-attribute is exceeded.
        */
        int add(const Gift gift);

        /**
         * @brief Adds a list of gifts to the sleigh.
         * @return Returns 0 if all gifts could be added.
         * Returns -1 if not all gifts could be added.
        */
        int load(const std::vector<Gift>& giftList);

        int debug_load(const std::vector<Gift>& giftList, int thread_id)
        {
            std::cout << "Loading thread: " << thread_id << std::endl;
            return this->load(giftList);
        }

        /**
         * @brief 'Delivers' the gifts by calculating the WRW with the gifts in loaded_gifts-attribute.
        */
        double calculateWRW(void);

        double getSleighMaxLoad(void) const { return this->sleigh_max_load; }
        double getSleighWeight(void) const { return this->sleigh_weight; }
        double getSleighCurrentLoad(void) const { return this->sleigh_current_load; }
        Coordinate getCurrentPos(void) const { return this->current_pos; }
        double getWRW(void) const { return this->WRW; }

        std::vector<Gift> getLoadedGifts(void) { return this->loaded_gifts; }
        void setLoadedGifts(std::vector<Gift> giftList) { this->loaded_gifts = giftList; }

        /**
         * @brief Resets all attributes to initializing state.
        */
        void unloadSleigh(void)
        {
            this->reset_attributes();
        }
    
    private:
        const double sleigh_max_load = 1000.0;
        const double sleigh_weight = 10.0;
        double sleigh_current_load = 0.0;
        double WRW = 0.0;
        Coordinate current_pos;
        std::vector<Gift> loaded_gifts;

        void reset_attributes(void);
};
