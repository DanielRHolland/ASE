#include "SerialBasketSolver.h"
#include "UnorderedMapListBasketSolver.h"


int main() {
    //std::string num = "20";
    //std::string fileName = "/home/dan/Desktop/Sync/uni/ASE/ASECoursework1/Cswk1-Basket_of_Names-test_data/Basket_of_Names-test_data/"+num+"/input-papers-"+num+".txt");
    std::string fileName = "/home/dan/Desktop/Sync/uni/ASE/ASECoursework1/in.txt";
    serialAlgorithm(fileName);
    return unorderedMapListBasketSolver(fileName);
}

