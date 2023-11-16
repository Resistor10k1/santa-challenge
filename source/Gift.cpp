

#include <exception>
#include "Gift.hpp"

Gift::Gift(unsigned int id, double latitude, double longitude, double weight) :
        id(id), lat(latitude), lon(longitude), w(weight)
{}

Gift::Gift(const Gift& g) :
        id(g.id), lat(g.lat), lon(g.lon), w(g.w)
{}

Gift::Gift(const std::initializer_list<double> ilist)
{
    auto it = ilist.begin();
    unsigned int size = ilist.size();

    this->id = (size >= 1) ? static_cast<unsigned int>(*it) : 0;
    this->lat = (size >= 2) ? *(it+1) : 0.0;
    this->lon = (size >= 3) ? *(it+2) : 0.0;
    this->w = (size >= 4) ? *(it+3) : 0.0;
}

Gift& Gift::operator=(const Gift& g)
{
    if(this != &g)
    {
        this->id = g.id;
        this->lat = g.lat;
        this->lon = g.lon;
        this->w = g.w;
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

    return *this;
}

bool operator==(const Gift& g1, const Gift& g2)
{
    bool ret_val = true;

    if((g1.id != g2.id) || (g1.lat != g2.lat) || (g1.lon != g2.lon) || (g1.w != g2.w))
    {
        ret_val = false;
    }

    return ret_val;
}

bool operator!=(const Gift& g1, const Gift& g2)
{
    return !(g1 == g2);
}