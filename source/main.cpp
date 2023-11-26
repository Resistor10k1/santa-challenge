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
#include <chrono>
#include "misc.hpp"
#include "Gift.hpp"
#include "GiftFactory.hpp"

using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;


int main(int argc, char* argv[])
{
    std::vector<Gift> giftList;
    GiftWeightFactory gwf;

    ofstream output_file;
    fs::path gift_file_path;
    fs::path abs_path = fs::canonical("/proc/self/exe");
    fs::path caller_path = fs::current_path();
    double duration_ms = 0.0;
    auto start = high_resolution_clock::now();

    cout << "This is the application main" << endl;
    
    if(argc > 1)
    {
        gift_file_path = argv[1];
    }
    else
    {
        gift_file_path = "../data/example_data.csv";
    }

    cout << "Absolut path: " << abs_path << endl;
    cout << "Caller path: " << caller_path << endl;

    cout << "Read some data..." << endl;
    readGiftsFromFile(gift_file_path, ',', giftList, gwf);
    cout << "Size gift-list: " << giftList.size() << endl;

    sort_weight(giftList);
    cout << "Sort gifts by weight" << endl;

    cout << "Min. weight: " << giftList.front().weight() << endl;
    cout << "Max. weight: " << giftList.back().weight() << endl;
    cout << "Avg. weight: " << mean_weight(giftList) << endl;
    cout << "Med. weight: " << median(giftList).weight() << endl;

    for(auto& gift : giftList)
    {
        gift.setDistance2Pole(haversine(90.0, 0.0, gift, degree));
    }

    sort_distance(giftList);
    cout << "Sort gifts by distance to the north pole" << endl;

    cout << "Min. dist: " << giftList.front().getDistance2Pole() << endl;
    cout << "Max. dist: " << giftList.back().getDistance2Pole() << endl;
    cout << "Avg. dist: " << mean_distance(giftList) << endl;
    cout << "Med. dist: " << median(giftList).getDistance2Pole() << endl;

    cout << "Save distance to the north pole to file..." << endl;
    output_file.open(caller_path/"data/output_dist.txt");
    if(output_file.is_open())
    {
        for(auto& gift : giftList)
        {
            output_file << std::setprecision(21) << gift.getDistance2Pole() << "\n";
        }
    }
    output_file.close();

    auto stop = high_resolution_clock::now();
    duration_ms += static_cast<double>(duration_cast<milliseconds>(stop-start).count());
    cout << "Execution took " << duration_ms << " ms" << endl;

    return 0;
}