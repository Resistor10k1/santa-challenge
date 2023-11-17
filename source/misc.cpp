
#include "misc.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <initializer_list>
using namespace std;

void str_split(const std::string& str, std::vector<std::string>& output, char separator)
{
    int pos = str.find(separator);

    if((pos != std::string::npos))
    {
        output.push_back(str.substr(0, pos));
        str_split(str.substr(pos+1), output, separator);
    }
    else if(!str.empty())
    {
        output.push_back(str);
    }
}

void readGiftsFromFile(fs::path path, char separator, std::vector<Gift>& output)
{
    std::fstream readFile;
    std::string line;
    unsigned int line_cntr = 0;

    readFile.open(path);

    if(readFile.is_open())
    {
        std::getline(readFile, line);
        if(line != "GiftId,Latitude,Longitude,Weight")
            throw std::domain_error("File seems not to contain gifts.");
        ++line_cntr;

        while(std::getline(readFile, line))
        {
            ++line_cntr;
            // Expected format of points: GiftId,Latitude,Longitude,Weight
            std::vector<std::string> ilist; 
            str_split(line, ilist, separator);

            if(ilist.size() == 4)
            {
                output.push_back(Gift(std::atol(ilist.at(0).c_str()), 
                                  std::atof(ilist.at(1).c_str()),
                                  std::atof(ilist.at(2).c_str()),
                                  std::atof(ilist.at(3).c_str())));
            }
            else
            {
                std::string msg("Invalid number of elements in file line " + std::to_string(line_cntr));
                throw std::length_error(msg);
            }
        }
    }

    readFile.close();
}
 
double haversine(const Gift& p1, const Gift& p2)
{
    double distance = 0.0;
    double r_earth = 6371.0087714;
    double term1 = sin((p2.latitude() - p1.latitude())*(1/2.0))*sin((p2.latitude() - p1.latitude())*(1/2.0));
    double term2 = cos(p1.latitude())*cos(p2.latitude())*sin((p2.longitude() - 
                    p1.longitude())*(1/2.0))*sin((p2.longitude() - p1.longitude())*(1/2.0));

    distance = 2*r_earth*asin(sqrt(term1 + term2));
    return distance;
}


