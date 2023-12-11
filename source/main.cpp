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
#include <ctime>
#include "misc.hpp"
#include "Gift.hpp"
#include "GiftFactory.hpp"
#include "TripManager.hpp"

using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;


int main(int argc, char* argv[])
{
    std::vector<Gift> giftList;
    GiftWeightFactory gwf;
    ofstream output_file;
    fs::path gift_file_path;
    fs::path exe_path = fs::canonical("/proc/self/exe");
    fs::path proj_root = exe_path.parent_path().parent_path();
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
        gift_file_path = proj_root/"data/example_data.csv";
    }

    cout << "Exe path: " << exe_path << endl;
    cout << "Caller path: " << caller_path << endl;
    cout << "Project root: " << proj_root << endl;

    cout << "Read some data from " << gift_file_path << endl;
    readGiftsFromFile(gift_file_path, ',', giftList, gwf);
    
//  Print some statistics about the gifts =================================================
    cout << "Size gift-list: " << giftList.size() << endl;

    sort_weight(giftList);
    cout << "Sort gifts by weight" << endl;
    cout << "Min. weight: " << giftList.front().weight() << endl;
    cout << "Max. weight: " << giftList.back().weight() << endl;
    cout << "Avg. weight: " << mean_weight(giftList) << endl;
    cout << "Med. weight: " << median(giftList).weight() << endl;

    sort_distance(giftList);
    cout << "Sort gifts by distance to the north pole" << endl;
    cout << "Min. dist: " << giftList.front().getDistance2Pole() << endl;
    cout << "Max. dist: " << giftList.back().getDistance2Pole() << endl;
    cout << "Avg. dist: " << mean_distance(giftList) << endl;
    cout << "Med. dist: " << median(giftList).getDistance2Pole() << endl;

    cout << "Optimal number of tours: " << sum_weight(giftList) / 1000.0 << endl;

//  Decide which strategies to use and deliver gifts =====================================
    NaiveLoadingStrategy naiveLoader;
    NearestLoadingStrategy nearestLoader;
    NNLoadingStrategy nnLoader;

    NaiveStrategy naiveDistributer;
    SimulatedAnnealingStrategy saDistributer;

    TripManager tm_Serious(giftList, nnLoader, saDistributer);
    tm_Serious.startDelivery();
    cout << "Delivery by 'Serious Trip-Manager' is " << (tm_Serious.verify_tour() ? "complete" : "not complete") << endl;
    cout << "Number of tours: " << tm_Serious.getNumberOfTours() << endl;
    cout << "Resulted in a WRW of " << setprecision(21) << tm_Serious.getTotalWRW() << endl;

    giftList = tm_Serious.getTotalBestTour();

//  Save results to file =================================================================
    auto now = system_clock::to_time_t(system_clock::now());
    string time_now = "0000-00-00_00-00";
    strftime(time_now.data(), time_now.size()+1, "%F_%H-%M", localtime(&now));

    cout << "Save distance to the north pole to " << proj_root/("data/output_trips_"+time_now+".csv") << endl;
    output_file.open(proj_root/("data/output_trips_"+time_now+".csv"));
    if(output_file.is_open())
    {
        output_file << "GiftId,TripId\n";
        for(auto& gift : giftList)
        {
            output_file << gift.ID() << "," << gift.getTourNumber() << "\n";
        }
    }
    else
    {
        cerr << "Could not open file: "<< proj_root/("data/output_trips_"+time_now+".csv") << endl;
    }
    output_file.close();

    auto stop = high_resolution_clock::now();
    duration_ms += static_cast<double>(duration_cast<milliseconds>(stop-start).count());
    cout << "Execution took " << duration_ms << " ms" << endl;

    return 0;
}