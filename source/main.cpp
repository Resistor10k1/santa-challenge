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
#include "Gift.hpp"
#include "GiftFactory.hpp"

using namespace std;
namespace fs = std::filesystem;


int main(void)
{
    std::vector<Gift> giftList;
    GiftWeightFactory gwf;
    cout << "This is the application main" << endl;

    fs::path abs_path = fs::canonical("/proc/self/exe");
    fs::path caller_path = fs::current_path();

    cout << "Absolut path: " << abs_path << endl;
    cout << "Absolut path: " << caller_path << endl;

    cout << "Read some data:" << endl;
    readGiftsFromFile(caller_path/"data/example_data.csv", ',', giftList, gwf);

    for(auto& gift : giftList)
    {
        cout << gift;
    }

    cout << "Is g0 equals to g1? " << (giftList.at(0) == giftList.at(1)) << endl;
    cout << "Is g0 equals to g15? " << (giftList.at(0) == giftList.at(14)) << endl;

    return 0;
}