

#include <exception>
#include "Gift.hpp"

Gift::Gift(unsigned int id, double latitude, double longitude, double weight,
            ICompareStrategy<Gift>* cs) :
        id(id), lat(latitude), lon(longitude), w(weight), compareStrategy(cs)
{}

Gift::Gift(const std::initializer_list<double> ilist, ICompareStrategy<Gift>* cs) :
        compareStrategy(cs)
{
    auto it = ilist.begin();
    unsigned int size = ilist.size();

    this->id = (size >= 1) ? static_cast<unsigned int>(*it) : 0;
    this->lat = (size >= 2) ? *(it+1) : 0.0;
    this->lon = (size >= 3) ? *(it+2) : 0.0;
    this->w = (size >= 4) ? *(it+3) : 0.0;
    this->distance2pole = (size >= 5) ? *(it+4) : 0.0;
}

Gift::Gift(const Gift& g) :
        id(g.id), lat(g.lat), lon(g.lon), w(g.w), distance2pole(g.distance2pole),
        compareStrategy(g.compareStrategy)
{}
Gift::Gift(ICompareStrategy<Gift>* cs) :
        id(0), lat(0.0), lon(0.0), w(0.0), compareStrategy(cs)
{}

Gift& Gift::operator=(const Gift& g)
{
    if(this != &g)
    {
        this->id = g.id;
        this->lat = g.lat;
        this->lon = g.lon;
        this->w = g.w;
        this->distance2pole = g.distance2pole;
        this->compareStrategy = g.compareStrategy;
    }

    return *this;
}

Gift& Gift::operator=(const std::initializer_list<double> ilist)
{
    auto it = ilist.begin();
    unsigned int size = ilist.size();

    this->id = (size >= 1) ? static_cast<unsigned int>(*it) : 0;
    this->lat = (size >= 2) ? *(it+1) : 0.0;
    this->lon = (size >= 3) ? *(it+2) : 0.0;
    this->w = (size >= 4) ? *(it+3) : 0.0;
    this->distance2pole = (size >= 5) ? *(it+4) : 0.0;

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
    // os << "Gift with ID " << g.id << ": " << std::endl;
    // os << "Latitude: " << g.lat << " deg" << std::endl;
    // os << "Longitude: " << g.lon << " deg" << std::endl;
    // os << "Weight: " << g.w << " kg" << std::endl;
    // os << "Distance2Pole: " << g.distance2pole << " km" << std::endl;

    os << g.id << ", " << g.lat << ", " << g.lon << ", " << g.w << ", " << g.distance2pole << std::endl;

    return os;
}
