/**
 * @file    main.cpp
 * @brief   Main application entry point.
 * @date    2023-11-19
 * @author  Andri Trottmann
 */


#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include "misc.hpp"
#include "Gift.hpp"
#include "GiftFactory.hpp"

using namespace std;
namespace fs = std::filesystem;


int main(void)
{
    std::vector<Gift> giftList;
    GiftWeightFactory gwf;
    CompareDistanceStrategy cds;
    std::vector<double> test_dist;
    ofstream output_file;
    cout << "This is the application main" << endl;

    fs::path abs_path = fs::canonical("/proc/self/exe");
    fs::path caller_path = fs::current_path();

    cout << "Absolut path: " << abs_path << endl;
    cout << "Absolut path: " << caller_path << endl;

    cout << "Read some data:" << endl;
    readGiftsFromFile(caller_path/"data/example_data.csv", ',', giftList, gwf);

    cout << "Unsorted gifts: " << endl;
    printVector(giftList);

    std::sort(giftList.begin(), giftList.end());
    cout << "Sorted gifts by weight: " << endl;
    printVector(giftList);

    for(auto& gift : giftList)
    {
        // cout << gift;
        test_dist.push_back(haversine(90.0, 0.0, gift, degree));
        gift.setDistance2Pole(test_dist.back());
        gift.setCompareStrategy(&cds);
    }

    cout << *giftList.begin() << endl;
    cout << *(giftList.end()-1) << endl;
    cout << (giftList.at(0) > giftList.at(1)) << endl;
    cout << giftList.at(0).getCompareStrategy() << "=?=" << &cds << endl;

    // cout << "== : " << (giftList.at(0) == giftList.at(1)) << endl;
    // cout << "!= : " << (giftList.at(0) != giftList.at(1)) << endl;
    // cout << ">  : " << (giftList.at(0) > giftList.at(1)) << endl;
    // cout << "<  : " << (giftList.at(0) < giftList.at(1)) << endl;
    // cout << ">= : " << (giftList.at(0) >= giftList.at(1)) << endl;
    // cout << "<= : " << (giftList.at(0) <= giftList.at(1)) << endl;

    cout << "giftList pre-sorting: " << endl;
    printVector(giftList);

    std::sort(giftList.begin(), giftList.end());
    cout << "Sorted gifts by distance to the north pole: " << endl;
    printVector(giftList);

    output_file.open(caller_path/"data/output_dist.txt");
    if(output_file.is_open())
    {
        for(auto& dist : test_dist)
        {
            output_file << std::setprecision(21) << dist << "\n";
        }
    }
    output_file.close();

    cout << "Is g0 equal to g1? " << (giftList.at(0) == giftList.at(1)) << endl;
    cout << "Is g0 equal to g15? " << (giftList.at(0) == giftList.at(14)) << endl;

    return 0;
}