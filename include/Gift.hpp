

#pragma once
#include <initializer_list>
#include <iostream>
#include "ICompareStrategy.hpp"

/**
 * @brief Location where a package is dropped.
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

        void setDistance2Pole(double dist) { distance2pole = dist; }
        double getDistance2Pole(void) const { return distance2pole; }

        double ID(void) const { return id;}
        double latitude(void) const { return lat; }
        double longitude(void) const { return lon; }
        double weight(void) const { return w; }

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
        ICompareStrategy<Gift>* compareStrategy;
        unsigned int id = 0;
        double lat = 0.0;
        double lon = 0.0;
        double w = 0.0;
        double distance2pole = 0.0;
};

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
