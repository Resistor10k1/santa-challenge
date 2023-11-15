/**
 * @file    main.cpp
 * @brief   Main application entry point.
 * @date    2023-03-23
 * @author  Andri Trottmann
 */


#include <iostream>
#include <vector>
#include "Module.h"
#include "Interface.h"

using namespace std;

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

int main(void)
{
    std::vector<double> some_vec(5);

    srandom(111);

    for(auto& elem : some_vec)
    {
        elem = random() % 200;
    }

    cout << "This is the application main" << endl;
    functions::vecmul(some_vec, 2.1);

    cout << "Result of multiplying the vector with 2.1: " << endl;
    printVector(some_vec);
    

    return 0;
}