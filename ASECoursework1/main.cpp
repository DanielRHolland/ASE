#include <iostream>
#include "dictionary.h"
#include <list>
#include <fstream>
#include <string>
#include <utility>
#include <algorithm>
#include <functional>

using NamePair = std::pair<std::string,std::string>;
using ListOfNamePairs = std::list<NamePair>;
using PosName = std::pair<int, std::string>;
using ListOfPositionedNames = std::list<PosName>;

ListOfNamePairs readFile(std::string fileName) {
    ListOfNamePairs listOfNamePairs;
    std::string name1;
    std::string name2;
    std::ifstream file (fileName);
    std::cout<< fileName;
    while (getline(file, name1)) {
        std::cout<< name1 << std::endl;
    }
    file.close();


    file.open(fileName);
    if (file.is_open()) {
        while ( getline (file, name1, ',') ) {
            std::cout<< name1;
            getline(file, name2);
            std::cout << "::" << name2 << std::endl;
            listOfNamePairs.push_back( NamePair(name1, name2));
            std::cout<< name1 << "::"<< name2 <<  std::endl;
        }
        file.close();
    } else std::cout << "Unable to open file";
    std::cout << "\n-------------\n";
    return listOfNamePairs;
}

int serialAlgorithm() {
//    ListOfNamePairs listOfNamePairs = readFile("./Cswk1-Basket_of_Names-test_data/Basket_of_Names-test_data/20/input-papers-20.txt");
    ListOfNamePairs listOfNamePairs = readFile("/home/dan/Desktop/Sync/uni/ASE/ASECoursework1/in.txt");
    int N = listOfNamePairs.size();
    //Make another copy of the input file;
    ListOfNamePairs secondList (listOfNamePairs);
    // sort one copy on the first components and the other on the second.
//    std::sort(s.begin(), s.end(), [](int a, int b) {
//        return a > b;
//    });
    for (auto i = listOfNamePairs.begin(); i!=listOfNamePairs.end(); i++) {
        std::cout << i->first + ":" + i->second + ",";
    }

    listOfNamePairs.sort([](NamePair np, NamePair np2) { return np.first < np2.first ;});

    secondList.sort([](NamePair np, NamePair np2) { return np.second < np2.second; });


    for (auto i = listOfNamePairs.begin(); i!=listOfNamePairs.end(); i++) {
        std::cout << i->first + ":" + i->second + ",";
    }
    std::cout << "\n";
    for (auto i = secondList.begin(); i!=secondList.end(); i++) {
        std::cout << i->first + ":" + i->second + ",";
    }

    std::cout << "\n";

    NamePair xnminus1xn ("","");
    NamePair x1x2;
    ListOfNamePairs xXPlus2;
    ListOfPositionedNames posNames;
    for (auto i = listOfNamePairs.begin(), j = secondList.begin(); i!=listOfNamePairs.end() && j != secondList.end(); i++, j++) {
        std::cout <<  j->first + ":" + j->second + "," << i->first + ":" + i->second + ","  << std::endl;
        if (j->second == i->first) {
            xXPlus2.push_back(NamePair(j->first, i->second));
        } else if ((++j)->second == i->first) {
            j--;
            std::cout <<  "####################" << j->first + ":" + j->second + "," << i->first + ":" + i->second + ","  << std::endl;
            xnminus1xn = *j;
            posNames.push_back(PosName(N, j->second));
            posNames.push_back(PosName(N-1, j->first));
            i--;
        } else {
            j--;
            std::cout <<  "####################" << j->first + ":" + j->second + "," << i->first + ":" + i->second + ","  << std::endl;
            x1x2 = *i;
            j--;
        }
    }
    std::cout << "xn-1: " << xnminus1xn.first <<  ", xn: " << xnminus1xn.second << "\n";
    std::cout << "x1: " << x1x2.first <<  ", x2: " << x1x2.second << "\n";
    std::cout << "\nend";
    return 0;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    return serialAlgorithm();
}

//

//
//
//
//
//        Passing over these files in sequence now allows us to create a new file containing all pairs
//        (x i , x i+2 ) for 1 ≤ i ≤ N − 2, and to identify (x N −1 , x N ).
//
//        The pairs (N − 1, x N −1 ) and (N, x N ) should be written on still another file.
//
// The process continues inductively. Assume that file F contains all pairs (x i , x i+t ) for
//1 ≤ i ≤ N − t, in random order, and that file G contains all pairs (i, x i ) for N − t < i ≤ N in
//order of the second components. Let H be a copy of file F , and sort H by first components, F by
//        second. Now go through F , G, and H, creating two new files F 0 and G 0 , as follows. If the current
//        records of files F , G, H are, respectively (x, x 0 ), (y, y 0 ), (z, z 0 ), then:
//i) If x 0 = z, output (x, z 0 ) to F 0 and advance files F and H.
//ii) If x 0 = y 0 , output (y − t, x) to G 0 and advance files F and G.
//iii) If x 0 > y 0 , advance file G.
//iv) If x 0 > z, advance file H.
//When file F is exhausted, sort G 0 by second components and merge G with it; then replace t by 2t,
//F by F 0 , G by G 0 .
//Thus t takes the values 2, 4, 8, . . .; and for fixed t we do O(log N ) passes over the data to sort it.
//Hence the total number of passes is O((log N ) 2 ). Eventually t ≥ N , so F is empty; then we simply
//        sort G on its first components.