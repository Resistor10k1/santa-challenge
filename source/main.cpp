/**
 * @file    main.cpp
 * @brief   Main application entry point.
 * @date    2023-03-23
 * @author  Andri Trottmann
 */


#include <iostream>
#include <vector>
#include <filesystem>
#include "misc.hpp"


using namespace std;
namespace fs = std::filesystem;


int main(void)
{
    std::vector<Gift> giftList;
    cout << "This is the application main" << endl;

    fs::path abs_path = fs::canonical("/proc/self/exe");
    fs::path caller_path = fs::current_path();

    cout << "Absolut path: " << abs_path << endl;
    cout << "Absolut path: " << caller_path << endl;

    cout << "Read some data:" << endl;
    readGiftsFromFile(caller_path/"data/example_data.csv", ',', giftList);

    for(auto& gift : giftList)
    {
        cout << gift;
    }

    return 0;
}