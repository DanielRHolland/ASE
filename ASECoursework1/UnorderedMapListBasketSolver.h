#ifndef ASECOURSEWORK_UNORDEREDMAPLISTBASKETSOLVER_H
#define ASECOURSEWORK_UNORDEREDMAPLISTBASKETSOLVER_H

#include <unordered_map>
#include <list>
#include <iostream>
#include <utility>
#include <fstream>

using UnOrMapOfNames = std::unordered_map<std::string, std::string>;
using WestEastMaps = std::pair<UnOrMapOfNames, UnOrMapOfNames>;



int unorderedMapListBasketSolver(std::string);


WestEastMaps readFileToWEM(std::string);


#endif //ASECOURSEWORK_UNORDEREDMAPLISTBASKETSOLVER_H
