/**
 * @file    misc.hpp
 * @brief   Miscellaneous functions and classes
 * @date    2023-11-15
 * @author  Andri Trottmann
 */

#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <initializer_list>
#include "Gift.hpp"
#include "GiftFactory.hpp"

namespace fs = std::filesystem;

template<typename T>
void printVector(const std::vector<T>& vec)
{
    std::cout << "[ ";
    
    for(auto& elem : vec)
    {
        std::cout << elem;

        if(elem == vec.back())
        {
            std::cout << " ]" << std::endl;
        }
        else
        {
            std::cout << ", ";
        }
    }
}

void str_split(const std::string& str, std::vector<std::string>& output, char separator=';');

/**
 * @brief Reads the package drop locations from a CSV file.
 * @details The format of a location is: GiftId,Latitude,Longitude,Weight
*/
void readGiftsFromFile(fs::path path, char separator, std::vector<Gift>& output, IGiftFactory& giftFactory);


enum CoordinateFormat
{
    radian,
    degree
};

/**
 * @brief Calculates the Haversine distance of two points.
*/
double haversine(double lat1, double lon1, double lat2, double lon2, CoordinateFormat cf);
double haversine(const Gift& g1, const Gift& g2, CoordinateFormat cf);
double haversine(double lat, double lon, const Gift& g, CoordinateFormat cf);

