

#pragma once
#include <cmath>

namespace santa
{
    struct Point
    {
        size_t id = 0;
        double lat = 0.0;
        double lon = 0.0;
    };
    
    double haversine(const Point& p1, const Point& p2);
}