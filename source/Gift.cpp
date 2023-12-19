

#include <exception>
#include "Gift.hpp"
#include "misc.hpp"

Gift::Gift(unsigned int id, double latitude, double longitude, double weight,
            ICompareStrategy<Gift>* cs) :
        id(id), coordinate({latitude, longitude}), w(weight), compareStrategy(cs)
{
    distance2pole = haversine(90, 0.0, this->coordinate, degree);
    distanceToRef = 0.0;
    tour_nr = 0;
}

Gift::Gift(const std::initializer_list<double> ilist, ICompareStrategy<Gift>* cs) :
        compareStrategy(cs)
{
    auto it = ilist.begin();
    unsigned int size = ilist.size();

    this->id = (size >= 1) ? static_cast<unsigned int>(*it) : 0;
    this->coordinate.latitude = (size >= 2) ? *(it+1) : 0.0;
    this->coordinate.longitude = (size >= 3) ? *(it+2) : 0.0;
    this->w = (size >= 4) ? *(it+3) : 0.0;

    distance2pole = haversine(90, 0.0, this->coordinate, degree);
    distanceToRef = 0.0;
    this->tour_nr = 0;
}

Gift::Gift(const Gift& g) :
        id(g.id), coordinate({g.coordinate.latitude, g.coordinate.longitude}), w(g.w), 
        distance2pole(g.distance2pole), distanceToRef(g.distanceToRef), tour_nr(g.tour_nr),
        compareStrategy(g.compareStrategy)
{}
Gift::Gift(ICompareStrategy<Gift>* cs) :
        id(0), w(0.0), distanceToRef(0.0), tour_nr(0), compareStrategy(cs)
{
    coordinate = {0.0, 0.0};
    distance2pole = haversine(90, 0.0, this->coordinate, degree);
}

void Gift::setDistToRef(const Coordinate& coo)
{
    this->distanceToRef = haversine(this->coordinate, coo, degree);
}

Gift& Gift::operator=(const Gift& g)
{
    if(this != &g)
    {
        this->id = g.id;
        this->coordinate.latitude = g.coordinate.latitude;
        this->coordinate.longitude = g.coordinate.longitude;
        this->w = g.w;
        this->distance2pole = g.distance2pole;
        this->distanceToRef = g.distanceToRef;
        this->compareStrategy = g.compareStrategy;
        this->tour_nr = g.tour_nr;
    }

    return *this;
}

Gift& Gift::operator=(const std::initializer_list<double> ilist)
{
    auto it = ilist.begin();
    unsigned int size = ilist.size();

    this->id = (size >= 1) ? static_cast<unsigned int>(*it) : 0;
    this->coordinate.latitude = (size >= 2) ? *(it+1) : 0.0;
    this->coordinate.longitude = (size >= 3) ? *(it+2) : 0.0;
    this->w = (size >= 4) ? *(it+3) : 0.0;

    distance2pole = haversine(90, 0.0, this->coordinate, degree);
    distanceToRef = 0.0;
    this->tour_nr = 0;

    return *this;
}

bool operator==(const Gift& g1, const Gift& g2)
{
    return g1.compareStrategy->equals(g1, g2);
}

bool operator!=(const Gift& g1, const Gift& g2)
{
    return g1.compareStrategy->nonEquals(g1, g2);
}

bool operator<(const Gift& g1, const Gift& g2)
{
    return g1.compareStrategy->lesserThan(g1, g2);
}
bool operator>(const Gift& g1, const Gift& g2)
{
    return g1.compareStrategy->greaterThan(g1, g2);
}
bool operator<=(const Gift& g1, const Gift& g2)
{
    return g1.compareStrategy->lessOrEqual(g1, g2);
}
bool operator>=(const Gift& g1, const Gift& g2)
{
    return g1.compareStrategy->greatOrEqual(g1, g2);
}

std::ostream& operator<<(std::ostream& os, const Gift& g)
{
    os << g.id << ", " << g.coordinate.latitude << ", " << g.coordinate.longitude << ", ";
    os << g.w << ", " << g.distance2pole << std::endl;

    return os;
}

