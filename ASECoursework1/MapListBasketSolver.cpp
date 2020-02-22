#include "MapListBasketSolver.h"



WestEastMaps readFileToWEM(std::string fileName) {
    WestEastMaps westEastMaps;
    std::string name1;
    std::string name2;
    std::ifstream file (fileName);
    file.close();
    file.open(fileName);
    if (file.is_open()) {
        while ( getline (file, name1, ',') ) {
            getline(file, name2);
            westEastMaps.first[name1] = name2;
            westEastMaps.second[name2] = name1;
        }
        file.close();
    } else std::cout << "Unable to open file";
    return westEastMaps;
}

int mapListBasketSolver(std::string fileName) {
    WestEastMaps westEastMaps = readFileToWEM(fileName);
    std::list<std::string> namesList;
    auto i = westEastMaps.first.begin();
    namesList.push_front(i->first);
    while (i != westEastMaps.first.end()) {
        namesList.push_back(i->second);
        i = westEastMaps.first.find(i->second);
    }
    i = westEastMaps.second.find(*namesList.begin());
    while (i != westEastMaps.second.end()) {
        namesList.push_front(i->second);
        i = westEastMaps.second.find(i->second);
    }

    for (auto i = namesList.begin(); i!= namesList.end(); i++) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    return 0;
}

//1.Insert the contents of the pieces of paper into a data structure suitable for searching.
//2. Create an empty container suitable for storing the resulting sequence of names.
//3. Arbitrarily choose one of the names as a starting point.
//4. Insert the name at the back of the result sequence, and then perform a search to identify his
//westerly neighbour (if any). Repeat this step until the most westerly name has been added to
//the sequence.
//5. Now return to the starting name.
//6. Perform a search to identify his easterly neighbour (if any), and then insert that name at the
//front of the result sequence. Repeat this step until the most easterly name has been added to
//the sequence.