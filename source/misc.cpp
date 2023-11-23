
#include "misc.hpp"
#include "GiftFactory.hpp"
#include <string>
#include <iostream>
#include <cmath>
#include <exception>
#include <algorithm>

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

void readGiftsFromFile(fs::path path, char separator, std::vector<Gift>& output, IGiftFactory& giftFactory)
{
    std::fstream readFile;
    std::string line;
    unsigned int line_cntr = 0;

    readFile.open(path);

    if(readFile.is_open())
    {
        std::getline(readFile, line);
        if(line != "GiftId,Latitude,Longitude,Weight")
            throw std::domain_error("File seems to not contain gifts.");
        ++line_cntr;

        while(std::getline(readFile, line))
        {
            ++line_cntr;
            // Expected format of points: GiftId,Latitude,Longitude,Weight
            std::vector<std::string> ilist; 
            str_split(line, ilist, separator);

            if(ilist.size() == 4)
            {
                output.push_back(giftFactory.produceGift(std::atol(ilist.at(0).c_str()), 
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
    else
    {
        throw runtime_error("Could not open file!");
    }

    readFile.close();
}

double haversine(double lat1, double lon1, double lat2, double lon2, CoordinateFormat cf)
{
    double distance = 0.0;
    double r_earth = 6371.0087714;

    if(cf == degree)
    {
        lat1 *= (2*std::numbers::pi / 360);
        lon1 *= (2*std::numbers::pi / 360);
        lat2 *= (2*std::numbers::pi / 360);
        lon2 *= (2*std::numbers::pi / 360);
    }

    double term1 = sin((lat2 - lat1)*(1/2.0))*sin((lat2 - lat1)*(1/2.0));
    double term2 = cos(lat1)*cos(lat2)*sin((lon2 - lon1)*(1/2.0))*sin((lon2 - lon1)*(1/2.0));

    distance = 2*r_earth*asin(sqrt(term1 + term2));
    return distance;
}
 
double haversine(const Gift& g1, const Gift& g2, CoordinateFormat cf)
{
    return haversine(g1.latitude(), g1.longitude(), g2.latitude(), g2.longitude(), cf);
}

double haversine(double lat, double lon, const Gift& g, CoordinateFormat cf)
{
    return haversine(lat, lon, g.latitude(), g.longitude(), cf);
}

double mean_weight(std::vector<Gift> g_vec)
{
    double ret_val = 0.0;

    if(g_vec.size() > 0)
    {
        for(auto& gift : g_vec)
        {
            ret_val += gift.weight();
        }
        ret_val /= g_vec.size();
    }

    return ret_val;
}

double mean_distance(std::vector<Gift> g_vec)
{
    double ret_val = 0.0;

    if(g_vec.size() > 0)
    {
        for(auto& gift : g_vec)
        {
            ret_val += gift.getDistance2Pole();
        }
        ret_val /= g_vec.size();
    }

    return ret_val;
}

void sort_id(std::vector<Gift>& gift_list)
{
    if(gift_list.size() > 0)
    {
        CompareIDStrategy cds;
        for(auto& gift : gift_list)
        {
            // ICompareStrategy<Gift>* temp_cs = gift.getCompareStrategy();
            gift.setCompareStrategy(&cds);
        }
        std::sort(gift_list.begin(), gift_list.end());
    }
}

void sort_weight(std::vector<Gift>& gift_list)
{
    if(gift_list.size() > 0)
    {
        CompareWeightStrategy cds;
        for(auto& gift : gift_list)
        {
            // ICompareStrategy<Gift>* temp_cs = gift.getCompareStrategy();
            gift.setCompareStrategy(&cds);
        }
        std::sort(gift_list.begin(), gift_list.end());
    }
}

void sort_distance(std::vector<Gift>& gift_list)
{
    if(gift_list.size() > 0)
    {
        CompareDistanceStrategy cds;
        for(auto& gift : gift_list)
        {
            // ICompareStrategy<Gift>* temp_cs = gift.getCompareStrategy();
            gift.setCompareStrategy(&cds);
        }
        std::sort(gift_list.begin(), gift_list.end());
    }
}

