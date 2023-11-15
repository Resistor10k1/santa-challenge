

#pragma once
#include "formulas.hpp"
#include <vector>


class Santa
{
    public:
        Santa(const std::vector<santa::Point>& global_points);
        void travel(const santa::Point& p);
    
    private:
        double sleigh_weight = 10.0;
        double WRW = 0.0;
        std::vector<const santa::Point*> point_cluster;
        std::vector<size_t> visited_points;

        double haversine(const santa::Point& p1, const santa::Point& p2);
};
