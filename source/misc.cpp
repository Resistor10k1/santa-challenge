
#include "misc.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>


void readGiftsFromFile(fs::path path, char separator, std::vector<Gift>& output)
{
    std::fstream readFile;
    std::string line;

    readFile.open(path);

    if(readFile.is_open())
    {
        size_t counter = 0;
        while(std::getline(readFile, line))
        {
            // Expected format of points: GiftId,Latitude,Longitude,Weight
            ++counter;

            size_t pos = 0;
            while((pos = line.find(separator)) != std::string::npos)
            {
                
            }

        }
    }

    readFile.close();
}
 
double haversine(const Gift& p1, const Gift& p2)
{
    double distance = 0.0;
    double r_earth = 6371.0087714;
    double term1 = sin((p2.lat - p1.lat)*(1/2.0))*sin((p2.lat - p1.lat)*(1/2.0));
    double term2 = cos(p1.lat)*cos(p2.lat)*sin((p2.lon - p1.lon)*(1/2.0))*sin((p2.lon - p1.lon)*(1/2.0));

    distance = 2*r_earth*asin(sqrt(term1 + term2));
    return distance;
}


