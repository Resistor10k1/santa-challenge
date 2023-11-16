

#pragma once
#include <initializer_list>

/**
 * @brief Location where a package is dropped.
*/
class Gift
{
    public:
        Gift(unsigned int id, double latitude, double longitude, double weight);
        Gift(const Gift& g);
        Gift(const std::initializer_list<double> ilist);

        double ID(void) const { return id;}
        double latitude(void) const { return lat; }
        double longitude(void) const { return lon; }
        double weight(void) const { return w; }

        Gift& operator=(const Gift& g);
        Gift& operator=(const std::initializer_list<double> ilist);
        friend bool operator==(const Gift& g1, const Gift& g2);
        friend bool operator!=(const Gift& g1, const Gift& g2);

    private:
        unsigned int id = 0;
        double lat = 0.0;
        double lon = 0.0;
        double w = 0.0;
};