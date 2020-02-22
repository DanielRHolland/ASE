#include "SerialBasketSolver.h"

ListOfNamePairs readFile(std::string fileName) {
    ListOfNamePairs listOfNamePairs;
    std::string name1;
    std::string name2;
    std::ifstream file (fileName);
    file.close();
    file.open(fileName);
    if (file.is_open()) {
        while ( getline (file, name1, ',') ) {
            getline(file, name2);
            listOfNamePairs.push_back( NamePair(name1, name2));
        }
        file.close();
    } else std::cout << "Unable to open file";
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
        assert(hi != H.end()); // hi should point to a value
        if (fi->second == hi->first) { // i) If x' = z, output (x, z' ) to F' and advance files F and H.
            fPrime.push_back(NamePair(fi->first, hi->second));
            fi++; hi++;
        } else if (gi!=G.end() && fi->second == gi->second) { // ii) If x' = y' , output (y − t, x) to G' and advance files F and G.
            gPrime.push_back(PosName(gi->first-t, fi->first));
            fi++;gi++;
        } else if (gi!=G.end() && fi->second > gi->second) { // iii) If x' > y' , advance file G.
            gi++;
        } else if (fi->second > hi->first) { // iv) If x' > z, advance file H.
            hi++;
        } else {
            assert(false); // Should never reach this point
        }
    }
    if (!fPrime.empty()) { //
       return onePass(fPrime, gPrime, N,t*2);
    }
    return gPrime;
}


int serialAlgorithm(std::string fileName) {
    ListOfNamePairs H = readFile(fileName);
    int N = H.size()+1;
    ListOfNamePairs F (H);
    H.sort([](NamePair np, NamePair np2) { return np.first < np2.first ;});
    F.sort([](NamePair np, NamePair np2) { return np.second < np2.second; });
    ListOfNamePairs xXPlus2;
    ListOfPositionedNames posNames;
    for (auto hi = H.begin(), fi = F.begin(); hi != H.end() && fi != F.end();) {
        if (fi->second == hi->first) {
            xXPlus2.push_back(NamePair(fi->first, hi->second));
            fi++;hi++;
        } else if (((++fi)--)->second == hi->first) { // get next value by pre-incrementing, then post-decrement to return fi to its state before evaluation of the expression
            posNames.push_back(PosName(N, fi->second));
            posNames.push_back(PosName(N-1, fi->first));
            fi++;
        } else {
            hi++;
        }
    }
    posNames = onePass(xXPlus2, posNames, N);
    posNames.sort([](PosName pn, PosName pn2) { return pn.first < pn2.first; });

    for ( auto i = posNames.begin();  i != posNames.end() ; i++) {
        std::cout << i->second << " ";
    }
    std::cout << std::endl;
    return 0;
}



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