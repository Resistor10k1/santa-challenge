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

/**
 * @brief Prints the content of a vector to the console.
 * @details Print format: [ <i>elem_1</i>, <i>elem_2</i>, ..., <i>elem_n</i> ]
 * @param vec Vetor to print.
*/
template<typename T>
void printVector(const std::vector<T>& vec)
{
    if(vec.size() > 0)
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
}

/**
 * @brief Splits a string into sub-strings
 * @note If the string ends with a separator character, no empty string is added to the list.
 * @param str The string to split
 * @param output List contaning the sub-strings
 * @param separator Separator character to split the string
*/
void str_split(const std::string& str, std::vector<std::string>& output, char separator=';');

/**
 * @brief Reads the package drop locations from a CSV file.
 * @details The format of a location is: GiftId,Latitude,Longitude,Weight. The latitude and longitude can 
 * be in format 'degree' or 'radiant'.
 * @param path Path to the csv file containing the gift data
 * @param separator Separator character used in the csv file.
 * @param output List with the data extracted as Giff objects
 * @param giftFactory Factory which produces the Gift objects (see GiftFactory.hpp and Gift.hpp for more
 * information.)
*/
void readGiftsFromFile(fs::path path, char separator, std::vector<Gift>& output, IGiftFactory& giftFactory);

/**
 * @brief Coordinate format for calculation in haversine().
*/
enum CoordinateFormat
{
    radiant,
    degree
};

/**
 * @brief Calculates the Haversine distance of two points.
 * @details The earth radius is set to 6371.0087714 km.
 * @param lat1 Latitude of point 1
 * @param lon1 Longitude of point 1
 * @param lat2 Latitude of point 2
 * @param lon2 Longitude of point 2
 * @param cf Coordinate format in 'degree' or 'radiant'.
 * @return Returns the distance in km.
*/
double haversine(double lat1, double lon1, double lat2, double lon2, CoordinateFormat cf);
double haversine(const Coordinate& p1, const Coordinate& p2, CoordinateFormat cf);
double haversine(double lat, double lon, const Coordinate& p, CoordinateFormat cf);

/**
 * @brief Calculates the sum of the weights of the gifts in list g_vec.
*/
double sum_weight(const std::vector<Gift>& g_vec);

/**
 * @brief Calculates the mean of the weights of the gifts in list g_vec.
*/
double mean_weight(const std::vector<Gift>& g_vec);

/**
 * @brief Calculates the mean of the distances to the north pole of the gifts in list g_vec.
*/
double mean_distance(const std::vector<Gift>& g_vec);

/**
 * @brief Returns the median value of list vec.
*/
template<typename T>
T median(std::vector<T> vec)
{
    unsigned int i = vec.size() / 2;

    if(vec.size() > 0)
    {
        return vec.at(i);
    }
    else
    {
        throw std::range_error("Cannot calculate median of vector of size 0!");
    }
}

/**
 * @brief Sorts the list gift_list by id, using CompareIDStrategy.
*/
void sort_id(std::vector<Gift>& gift_list);

/**
 * @brief Sorts the list gift_list by weight, using CompareWeightStrategy.
*/
void sort_weight(std::vector<Gift>& gift_list);

/**
 * @brief Sorts the list gift_list by distance, using CompareDistanceStrategy.
*/
void sort_distance(std::vector<Gift>& gift_list);

void sort_distToRef(std::vector<Gift>& gift_list);

