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

// #define EVAL_MAGIC_NUMBERS

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

    cout << endl;
    sort_weight(giftList);
    cout << "Some weight stats:" << endl;
    cout << "Min. weight: " << giftList.front().weight() << endl;
    cout << "Max. weight: " << giftList.back().weight() << endl;
    cout << "Avg. weight: " << mean_weight(giftList) << endl;
    cout << "Med. weight: " << median(giftList).weight() << endl;

    cout << endl;
    sort_distance(giftList);
    cout << "Some distance to the north pole stats:" << endl;
    cout << "Min. dist: " << giftList.front().getDistance2Pole() << endl;
    cout << "Max. dist: " << giftList.back().getDistance2Pole() << endl;
    cout << "Avg. dist: " << mean_distance(giftList) << endl;
    cout << "Med. dist: " << median(giftList).getDistance2Pole() << endl;

    cout << "Optimal number of tours: " << sum_weight(giftList) / 1000.0 << endl << endl;

#ifdef EVAL_MAGIC_NUMBERS
    cout << "## Starting evaluation of magic numbers ##" << endl;
#else
    cout << "## Starting calculation ##" << endl;
#endif

//  Decide which strategies to use and deliver gifts =====================================
    NNLoadingStrategy nnLoader;

    #ifdef EVAL_MAGIC_NUMBERS
    unsigned int eval_progress = 0;
    vector<vector<double>> eval_numbers = {{1,  5,  8,  32, 100000.0, 0.001},
                                           {1, 10,  8,  32, 100000.0, 0.001},
                                           {1, 15,  8,  32, 100000.0, 0.001},
                                           {1, 20,  8,  32, 100000.0, 0.001},
                                           {1, 25,  8,  32, 100000.0, 0.001},
                                           {1,  5, 16,  64, 100000.0, 0.001},
                                           {1, 10, 16,  64, 100000.0, 0.001},
                                           {1, 15, 16,  64, 100000.0, 0.001},
                                           {1, 25, 16,  64, 100000.0, 0.001},
                                           {1,  5, 32, 128, 100000.0, 0.001},
                                           {1, 10, 32, 128, 100000.0, 0.001},
                                           {1, 15, 32, 128, 100000.0, 0.001},
                                           {1, 20, 32, 128, 100000.0, 0.001},
                                           {1, 25, 32, 128, 100000.0, 0.001},
                                           {1,  5,  8,  32, 100000.0, 0.001},
                                           {1,  5,  8,  64, 100000.0, 0.001},
                                           {1,  5,  8, 128, 100000.0, 0.001},
                                           {1, 10,  8,  32, 100000.0, 0.001},
                                           {1, 10,  8,  64, 100000.0, 0.001},
                                           {1, 10,  8, 128, 100000.0, 0.001},
                                           {1, 15,  8,  32, 100000.0, 0.001},
                                           {1, 15,  8,  64, 100000.0, 0.001},
                                           {1, 15,  8, 128, 100000.0, 0.001},
                                           {1, 20,  8,  32, 100000.0, 0.001},
                                           {1, 20,  8,  64, 100000.0, 0.001},
                                           {1, 20,  8, 128, 100000.0, 0.001},
                                           {1, 25,  8,  32, 100000.0, 0.001},
                                           {1, 25,  8,  64, 100000.0, 0.001},
                                           {1, 25,  8, 128, 100000.0, 0.001},
                                           {1,  5, 16,  48, 100000.0, 0.001},
                                           {1,  5, 16,  64, 100000.0, 0.001},
                                           {1,  5, 16, 128, 100000.0, 0.001},
                                           {1, 10, 16,  48, 100000.0, 0.001},
                                           {1, 10, 16,  64, 100000.0, 0.001},
                                           {1, 10, 16, 128, 100000.0, 0.001},
                                           {1, 15, 16,  48, 100000.0, 0.001},
                                           {1, 15, 16,  64, 100000.0, 0.001},
                                           {1, 15, 16, 128, 100000.0, 0.001},
                                           {1, 20, 16,  48, 100000.0, 0.001},
                                           {1, 20, 16,  64, 100000.0, 0.001},
                                           {1, 20, 16, 128, 100000.0, 0.001},
                                           {1, 25, 16,  48, 100000.0, 0.001},
                                           {1, 25, 16,  64, 100000.0, 0.001},
                                           {1, 25, 16, 128, 100000.0, 0.001},
                                           {1,  5, 32,  96, 100000.0, 0.001},
                                           {1,  5, 32, 128, 100000.0, 0.001},
                                           {1, 10, 32,  96, 100000.0, 0.001},
                                           {1, 10, 32, 128, 100000.0, 0.001},
                                           {1, 15, 32,  96, 100000.0, 0.001},
                                           {1, 15, 32, 128, 100000.0, 0.001},
                                           {1, 20, 32,  96, 100000.0, 0.001},
                                           {1, 20, 32, 128, 100000.0, 0.001},
                                           {1, 25, 32,  96, 100000.0, 0.001},
                                           {1, 25, 32, 128, 100000.0, 0.001}};

    for(auto& parameterList : eval_numbers)
    {
        double min_swap_offset = parameterList.at(0);
        double max_swap_offset = parameterList.at(1);
        double cool_intervall = parameterList.at(2);
        double reheat_intervall = parameterList.at(3);
        double T_initial = parameterList.at(4);
        double T_final = parameterList.at(5);
        auto local_giftlist(giftList);

        SimulatedAnnealingStrategy saDistributer({min_swap_offset, max_swap_offset, cool_intervall, reheat_intervall, T_initial, T_final});
        TripManager tm_Serious(local_giftlist, nnLoader, saDistributer);
    #else
        SimulatedAnnealingStrategy saDistributer({1, 25, 32, 128, 100000.0, 0.001});
        TripManager tm_Serious(giftList, nnLoader, saDistributer);
    #endif

        // TripManager tm_Serious(giftList, nnLoader, saDistributer);
        tm_Serious.startDelivery();

    #ifndef EVAL_MAGIC_NUMBERS
        cout << endl;
        cout << "Delivery by 'Serious Trip-Manager' is " << (tm_Serious.verify_tour() ? "complete" : "not complete") << endl;
        cout << "Number of tours: " << tm_Serious.getNumberOfTours() << endl;
        cout << "Resulted in a WRW of " << setprecision(21) << tm_Serious.getTotalWRW() << endl;
    
        giftList = tm_Serious.getTotalBestTour();

//  Simulation time
        auto stop = high_resolution_clock::now();
        duration_ms = static_cast<double>(duration_cast<milliseconds>(stop-start).count());
        cout << "Execution took " << duration_ms << " ms" << endl;
    #endif

    #ifdef EVAL_MAGIC_NUMBERS
        ++eval_progress;
        cout << "Evaluated magic numbers " << eval_progress << " / " << eval_numbers.size() << ": " << setprecision(4);
        printVector(parameterList);
        cout << "Resulted in a WRW of " << setprecision(21) << tm_Serious.getTotalWRW() << endl;
    }
    #endif

//  Save results to file =================================================================
#ifndef EVAL_MAGIC_NUMBERS
    char saveFile;
    cout << "Save tour to file? [y,n]:";
    cin >> saveFile;

    if(saveFile == 'y')
    {
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
    }
#endif

    return 0;
}