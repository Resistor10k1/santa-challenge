

#include "formulas.hpp"
#include <cmath>
#include <iostream>

namespace santa
{    
    double haversine(const Point& p1, const Point& p2)
    {
        double distance = 0.0;
        double r_earth = 6371.0087714;
        double term1 = sin((p2.lat - p1.lat)*(1/2.0))*sin((p2.lat - p1.lat)*(1/2.0));
        double term2 = cos(p1.lat)*cos(p2.lat)*sin((p2.lon - p1.lon)*(1/2.0))*sin((p2.lon - p1.lon)*(1/2.0));

        distance = 2*r_earth*asin(sqrt(term1 + term2));
        return distance;
    }
}