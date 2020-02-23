#include "SerialBasketSolver.h"
#include "UnorderedMapListBasketSolver.h"
#include "MapListBasketSolver.h"
#include <functional>
#include <list>
#include <chrono>
#include <iostream>
#include <fstream>

double timedRun(std::function<int(std::string)> f, std::string p) {
    auto start = std::chrono::high_resolution_clock::now();
    f(p);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    return elapsed.count();
}

std::list<double> timedRuns(std::function<int(std::string)> f, std::string p, int n) {
    std::list<double> results;
    for (int i = 0; i<n; i++) {
        results.push_back(timedRun(f,p));
    }
    return results;
}

using ResultsRow = std::pair<int,std::list<double>>;
int resultListsToCsv(std::string heading, std::list<ResultsRow> results) {
    std::time_t timestamp = std::time(nullptr);
    std::ofstream csvFile;
    csvFile.open ("/home/dan/Desktop/Sync/uni/ASE/ASECoursework1/results/"+ std::to_string(timestamp) + ".csv");
    csvFile << "n, " << heading << "\n";
    for (auto i : results) {
        csvFile << i.first << ", ";
        for (auto j: i.second) {
            csvFile << j << ", ";
        }
        csvFile << "\n";
    }
    csvFile.close();
    return 0;
}

int labelToInt(std::string label) {
    if (label.back()=='K') {
        return std::stoi(label.substr(0, label.size()-1)) * 1000;
    } else if (label.back()=='M') {
        return std::stoi(label.substr(0, label.size()-1)) * 1000000;
    } else {
        return std::stoi(label);
    }
}

int runTimeTrials(std::function<int(std::string)> f, std::string heading, std::list<std::string> sizes) {
    std::list<ResultsRow> results;
    for (auto i : sizes) {
        int size = labelToInt(i);
        std::string fileName =
                "/home/dan/Desktop/Sync/uni/ASE/ASECoursework1/Cswk1-Basket_of_Names-test_data/Basket_of_Names-test_data/"
                + i +"/input-papers-" + i +".txt";
        auto resultRow = timedRuns(f, fileName, 1);
        results.push_front(ResultsRow(size, resultRow));
    }
    resultListsToCsv(heading, results);
    return 0;
}

int main(int argc, const char* argv[]) {
    std::string fileName = "/home/dan/Desktop/Sync/uni/ASE/ASECoursework1/Cswk1-Basket_of_Names-test_data/Basket_of_Names-test_data/20/input-papers-20.txt";
    //std::list<std::string> sizes = { "20","50","100","200", "500", "1K" , "2K", "5K", "10K", "20K"};
    std::list<std::string> sizes = { "20","50","100","200",
                                     "500", "1K" , "2K", "5K",
                                     "10K", "20K", "50K", "100K",
                                     "200K", "500K", "1M","2M","3M"};
    sizes = {"100K"};
    std::function<int(std::string)> fn = serialAlgorithm;
    for(int i = 0; i < argc; ++i) {
        if (std::string(argv[i]) == "-s") {
            sizes = { std::string(argv[++i]) };
        } else if (std::string(argv[i]) == "-a") {
            std::string functionName = std::string(argv[++i]);
            if (functionName == "umap") {
                fn = unorderedMapListBasketSolver;
            } else if (functionName == "map") {
                fn = mapListBasketSolver;
            } else {
                fn = serialAlgorithm;
            }
        } else {
                fileName = argv[i];
        }
    }

    runTimeTrials( serialAlgorithm , "Results for serial algorithm", sizes);
//    std::string fileName = "/home/dan/Desktop/Sync/uni/ASE/ASECoursework1/Cswk1-Basket_of_Names-test_data/Basket_of_Names-test_data/"+ std::to_string(num) +"/input-papers-"+std::to_string(num)+".txt";
//    serialAlgorithm(fileName);
//    mapListBasketSolver(fileName);
//    unorderedMapListBasketSolver(fileName);
    return 0;
}
