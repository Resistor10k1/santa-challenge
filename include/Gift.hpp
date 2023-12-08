/**
 * @file    Gift.hpp
 * @date    2023-12-08
 * @author  Andri Trottmann
 */

#pragma once
#include <initializer_list>
#include <iostream>
#include <vector>
#include "ICompareStrategy.hpp"


struct Coordinate
{
    double latitude = 0.0;
    double longitude = 0.0;
};

/**
 * @brief Data abstraction of location where a package is dropped.
*/
class Gift
{
    public:
        Gift(unsigned int id, double latitude, double longitude, double weight,
             ICompareStrategy<Gift>* cs);
        Gift(const std::initializer_list<double> ilist, ICompareStrategy<Gift>* cs);
        Gift(const Gift& g);
        Gift(ICompareStrategy<Gift>* cs);

        void setCompareStrategy(ICompareStrategy<Gift>* cs) { compareStrategy = cs; }
        ICompareStrategy<Gift>* getCompareStrategy(void) { return compareStrategy; }

        double getDistance2Pole(void) const { return distance2pole; }
        unsigned int ID(void) const { return id;}
        double latitude(void) const { return coordinate.latitude; }
        double longitude(void) const { return coordinate.longitude; }
        double weight(void) const { return w; }
        Coordinate getCoordinate(void) const { return coordinate; }

        void setTourNumber(unsigned int nbr) { tour_nr = nbr; }
        unsigned int getTourNumber(void) const { return tour_nr; }

        void setDistToRef(const Coordinate& coo);
        double getDistToRef(void) const { return distanceToRef; };

        Gift& operator=(const Gift& g);
        Gift& operator=(const std::initializer_list<double> ilist);
        friend bool operator==(const Gift& g1, const Gift& g2);
        friend bool operator!=(const Gift& g1, const Gift& g2);
        friend bool operator<(const Gift& g1, const Gift& g2);
        friend bool operator>(const Gift& g1, const Gift& g2);
        friend bool operator<=(const Gift& g1, const Gift& g2);
        friend bool operator>=(const Gift& g1, const Gift& g2);

        friend std::ostream& operator<<(std::ostream& os, const Gift& g);

    private:
        ICompareStrategy<Gift>* compareStrategy; /**< Compare strategy applied with the operator-functions*/
        unsigned int id = 0; /**< ID of the gift*/
        Coordinate coordinate; /**< Coordinate where the gift is dropped */
        double w = 0.0; /**< Weight of the gift*/
        double distance2pole = 0.0; /**< Distance from the north pole to the gift*/
        unsigned int tour_nr = 0; /**< Number indicating the tour in which the gift is delivered */
        double distanceToRef = 0.0;
};

/**
 * @brief Sets the operator-functions of Gift-Class to be applied to the id attribute.
*/
class CompareIDStrategy : public ICompareStrategy<Gift>
{
    public:
        bool equals(const Gift& t1, const Gift& t2) override { return (t1.ID() == t2.ID()); }
        bool nonEquals(const Gift& t1, const Gift& t2) override { return (t1.ID() != t2.ID()); }
        bool lesserThan(const Gift& t1, const Gift& t2) override { return (t1.ID() < t2.ID()); }
        bool greaterThan(const Gift& t1, const Gift& t2) override { return (t1.ID() > t2.ID()); }
        bool lessOrEqual(const Gift& t1, const Gift& t2) override { return (t1.ID() <= t2.ID()); }
        bool greatOrEqual(const Gift& t1, const Gift& t2) override { return (t1.ID() >= t2.ID()); }
};

/**
 * @brief Sets the operator-functions of Gift-Class to be applied to the weight attribute.
*/
class CompareWeightStrategy : public ICompareStrategy<Gift>
{
    public:
        bool equals(const Gift& t1, const Gift& t2) override { return (t1.weight() == t2.weight()); }
        bool nonEquals(const Gift& t1, const Gift& t2) override { return (t1.weight() != t2.weight()); }
        bool lesserThan(const Gift& t1, const Gift& t2) override { return (t1.weight() < t2.weight()); }
        bool greaterThan(const Gift& t1, const Gift& t2) override { return (t1.weight() > t2.weight()); }
        bool lessOrEqual(const Gift& t1, const Gift& t2) override { return (t1.weight() <= t2.weight()); }
        bool greatOrEqual(const Gift& t1, const Gift& t2) override { return (t1.weight() >= t2.weight()); }
};

/**
 * @brief Sets the operator-functions of Gift-Class to be applied to the distance2Pole attribute.
*/
class CompareDistanceStrategy : public ICompareStrategy<Gift>
{
    public:
        bool equals(const Gift& t1, const Gift& t2) override
        { return (t1.getDistance2Pole() == t2.getDistance2Pole()); }

        bool nonEquals(const Gift& t1, const Gift& t2) override 
        { return (t1.getDistance2Pole() != t2.getDistance2Pole()); }

        bool lesserThan(const Gift& t1, const Gift& t2) override 
        { return (t1.getDistance2Pole() < t2.getDistance2Pole()); }

        bool greaterThan(const Gift& t1, const Gift& t2) override 
        { return (t1.getDistance2Pole() > t2.getDistance2Pole()); }

        bool lessOrEqual(const Gift& t1, const Gift& t2) override 
        { return (t1.getDistance2Pole() <= t2.getDistance2Pole()); }

        bool greatOrEqual(const Gift& t1, const Gift& t2) override 
        { return (t1.getDistance2Pole() >= t2.getDistance2Pole()); }
};

/**
 * @brief Sets the operator-functions of Gift-Class to be applied to the distance2Ref attribute.
*/
class CompareDistToRefStrategy : public ICompareStrategy<Gift>
{
    public:
        bool equals(const Gift& t1, const Gift& t2) override
        { return (t1.getDistToRef() == t2.getDistToRef()); }

        bool nonEquals(const Gift& t1, const Gift& t2) override 
        { return (t1.getDistToRef() != t2.getDistToRef()); }

        bool lesserThan(const Gift& t1, const Gift& t2) override 
        { return (t1.getDistToRef() < t2.getDistToRef()); }

        bool greaterThan(const Gift& t1, const Gift& t2) override 
        { return (t1.getDistToRef() > t2.getDistToRef()); }

        bool lessOrEqual(const Gift& t1, const Gift& t2) override 
        { return (t1.getDistToRef() <= t2.getDistToRef()); }

        bool greatOrEqual(const Gift& t1, const Gift& t2) override 
        { return (t1.getDistToRef() >= t2.getDistToRef()); }
};
