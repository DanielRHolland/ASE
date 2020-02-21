#include <iostream>
#include "dictionary.h"
#include <list>
#include <fstream>
#include <string>
#include <utility>
#include <algorithm>
#include <functional>
#include <assert.h>

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



ListOfPositionedNames onePass(ListOfNamePairs F, ListOfPositionedNames G, int N, int t = 2) {
    ListOfNamePairs H (F);
    F.sort([](NamePair np, NamePair np2) { return np.second < np2.second ;});
    H.sort([](NamePair np, NamePair np2) { return np.first < np2.first; });
    G.sort([](PosName pn, PosName pn2) { return pn.second < pn2.second; });
    ListOfNamePairs fPrime;
    ListOfPositionedNames gPrime (G);
    auto gi = G.begin();
    for (auto fi = F.begin(),hi = H.begin(); fi!=F.end();) {

        assert(hi != H.end());
        assert(fi != F.end());
        std::cout << " f: " << fi->first << " " << fi->second;
        if (gi != G.end()) std::cout << "\t| g: " << gi->first << " " << gi->second;
        else std::cout << " |\t\t  ";
        std::cout << "\t| h: " << hi->first << " " << hi->second << " \t|";
//        i) If x 0 = z, output (x, z 0 ) to F 0 and advance files F and H.
        if (fi->second == hi->first) {
            fPrime.push_back(NamePair(fi->first, hi->second));
            fi++; hi++;
            std::cout << " result : i" << std::endl;
        } //       ii) If x 0 = y 0 , output (y − t, x) to G 0 and advance files F and G.
        else if (gi!=G.end() && fi->second == gi->second) {
            gPrime.push_back(PosName(N-t, gi->second));
            fi++;gi++;
            std::cout << " result : ii" << std::endl;
        } //      iii) If x 0 > y 0 , advance file G.
        else if (gi!=G.end() && fi->second > gi->second) {
            gi++;
            std::cout << " result : iii" << std::endl;
        }
//       iv) If x 0 > z, advance file H.
        else if (fi->second > hi->first) {
            hi++;
            std::cout << " result : iv" << std::endl;
        } else {
            assert(false);
        }
    }
    for (auto i = fPrime.begin(); i != fPrime.end(); i++) {
        std::cout << i->first + ":" + i->second + ",";
    }
    std::cout << std::endl;
    for (auto i = gPrime.begin(); i != gPrime.end(); i++) {
        std::cout << i->first << ":" << i->second + ",";
    }
    std::cout << std::endl;
    std::cout << "t:" << t << std::endl;
    if (!fPrime.empty()) {
        assert(t<40);
        std::cout << " recursing...." << std::endl;
        return onePass(fPrime, gPrime, t*2);
    }
    return gPrime;
}


int serialAlgorithm() {
//    ListOfNamePairs H = readFile("./Cswk1-Basket_of_Names-test_data/Basket_of_Names-test_data/20/input-papers-20.txt");
    ListOfNamePairs H = readFile("/home/dan/Desktop/Sync/uni/ASE/ASECoursework1/in.txt");
    int N = H.size()+1;
    ListOfNamePairs F (H);
    for (auto i = H.begin(); i != H.end(); i++) {
        std::cout << i->first + ":" + i->second + ",";
    }

    H.sort([](NamePair np, NamePair np2) { return np.first < np2.first ;});

    F.sort([](NamePair np, NamePair np2) { return np.second < np2.second; });


    for (auto i = H.begin(); i != H.end(); i++) {
        std::cout << i->first + ":" + i->second + ",";
    }
    std::cout << "\n";
    for (auto i = F.begin(); i != F.end(); i++) {
        std::cout << i->first + ":" + i->second + ",";
    }

    std::cout << "\n";

    ListOfNamePairs xXPlus2;
    ListOfPositionedNames posNames;
    for (auto hi = H.begin(), fi = F.begin(); hi != H.end() && fi != F.end();) {
        std::cout << fi->first + ":" + fi->second + "," << hi->first + ":" + hi->second + "," << std::endl;
        if (fi->second == hi->first) {
            xXPlus2.push_back(NamePair(fi->first, hi->second));
            fi++;hi++;
        } else if ((++fi)->second == hi->first) {
            fi--;
            std::cout << "####################" << fi->first + ":" + fi->second + "," << hi->first + ":" + hi->second + "," << std::endl;
            std::cout << "xn-1: " << fi->first <<  ", xn: " << fi->second << "\n";
            posNames.push_back(PosName(N, fi->second));
            posNames.push_back(PosName(N-1, fi->first));
            fi++;
        } else {
            fi--;
            std::cout << "####################" << fi->first + ":" + fi->second + "," << hi->first + ":" + hi->second + "," << std::endl;
            std::cout << "x1: " << hi->first <<  ", x2: " << hi->second << "\n";
            hi++;
        }
    }
    std::cout << "\nstart onePass:";

    for (auto i = xXPlus2.begin(); i != xXPlus2.end(); i++) {
        std::cout << i->first + ":" + i->second + ",";
    }
    std::cout << std::endl;

    posNames = onePass(xXPlus2, posNames, N);


    posNames.sort([](PosName pn, PosName pn2) { return pn.first < pn2.first; });

    for ( auto i = posNames.begin();  i != posNames.end() ; i++) {
        std::cout << "  " << i->second;
    }

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