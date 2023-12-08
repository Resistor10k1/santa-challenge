/**
 * @file    GiftFactory.hpp
 * @brief   Contains different gift-factories
 * @date    2023-12-08
 * @author  Andri Trottmann
 */

#pragma once
#include "Gift.hpp"

/**
 * @brief Interface to apply Factory-Pattern
*/
class IGiftFactory
{
    public:
        virtual Gift produceGift(unsigned int id, double latitude, double longitude, double weight) = 0;
};

/**
 * @brief Comparison operations of gifts produced with this factory are applied to the weight-attribute of Gift.
*/
class GiftWeightFactory : public IGiftFactory
{
    public:
        GiftWeightFactory(void) : g(&cs) {}
        Gift produceGift(unsigned int id, double latitude, double longitude, double weight) override
        {
            g = { static_cast<double>(id), latitude, longitude, weight };
            return g;
        }
    
    private:
        CompareWeightStrategy cs;
        Gift g;
};

/**
 * @brief Comparison operations of gifts produced with this factory are applied to the id-attribute of Gift.
*/
class GiftIDFactory : public IGiftFactory
{
    public:
        GiftIDFactory(void) : g(&cs) {}
        Gift produceGift(unsigned int id, double latitude, double longitude, double weight) override
        {
            g = { static_cast<double>(id), latitude, longitude, weight };
            return g;
        }
    
    private:
        CompareIDStrategy cs;
        Gift g;
};

/**
 * @brief Comparison operations of gifts produced with this factory are applied to the distance2pole-attribute of Gift.
*/
class GiftDistanceFactory : public IGiftFactory
{
    public:
        GiftDistanceFactory(void) : g(&cs) {}
        Gift produceGift(unsigned int id, double latitude, double longitude, double weight) override
        {
            g = { static_cast<double>(id), latitude, longitude, weight };
            return g;
        }
    
    private:
        CompareDistanceStrategy cs;
        Gift g;
};