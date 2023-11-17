/**
 * @file    misc.hpp
 * @brief   Miscellaneous functions and classes
 * @date    2023-11-15
 * @author  Andri Trottmann
 */

#pragma once

#include <vector>
#include <iostream>
#include <filesystem>
#include "Gift.hpp"

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
void readGiftsFromFile(fs::path path, char separator, std::vector<Gift>& output);

/**
 * @brief Calculates the Hversine distance of two points.
*/
double haversine(const Gift& p1, const Gift& p2);

