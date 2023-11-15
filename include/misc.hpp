/**
 * @file    misc.hpp
 * @brief   Miscellaneous functions and classes
 * @date    2023-11-15
 * @author  Andri Trottmann
 */

#pragma once

#include <vector>
#include <iostream>

namespace misc
{
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
}

