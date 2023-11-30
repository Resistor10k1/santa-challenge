
#pragma once
#include <vector>
#include "Gift.hpp"
#include "Santa.hpp"

class ILoadStrategy
{
    public:
        virtual void preprocessGifts(std::vector<Gift>& giftList) {}
        int loadSleigh(Santa& santa, Gift& gift, unsigned int tour_nbr)
        {
            gift.setTourNumber(tour_nbr);
            return santa.add(gift);
        };
        virtual std::vector<Gift>::iterator loadTourToSleigh(Santa& santa, const std::vector<Gift>::iterator& gift_it, 
                                                        const std::vector<Gift>::iterator& it_end, 
                                                        unsigned int tour_nbr) = 0;
};

/**
 * @brief Loads the gifts one by one as they are given in the list without any optimization.
*/
class NaiveLoadingStrategy : public ILoadStrategy
{
    public:
        // int loadSleigh(Santa& santa, Gift& gift, unsigned int tour_nbr) override;
        // void preprocessGifts(std::vector<Gift>& giftList) override;
        std::vector<Gift>::iterator loadTourToSleigh(Santa& santa, const std::vector<Gift>::iterator& gift_it,
                                                const std::vector<Gift>::iterator& it_end, unsigned int tour_nbr) override;
};

class NearestLoadingStrategy : public ILoadStrategy
{
    public:
        void preprocessGifts(std::vector<Gift>& giftList) override;
        std::vector<Gift>::iterator loadTourToSleigh(Santa& santa, const std::vector<Gift>::iterator& gift_it,
                                                const std::vector<Gift>::iterator& it_end, unsigned int tour_nbr) override;
};

class NNLoadingStrategy : public ILoadStrategy
{
    public:
        void preprocessGifts(std::vector<Gift>& giftList) override;
        std::vector<Gift>::iterator loadTourToSleigh(Santa& santa, const std::vector<Gift>::iterator& gift_it,
                                                const std::vector<Gift>::iterator& it_end, unsigned int tour_nbr) override;
    private:
        std::vector<std::vector<Gift>> dist_matrix;
};