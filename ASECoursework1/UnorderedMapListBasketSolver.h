#ifndef ASECOURSEWORK_UNORDEREDMAPLISTBASKETSOLVER_H
#define ASECOURSEWORK_UNORDEREDMAPLISTBASKETSOLVER_H

#include <unordered_map>
#include <list>
#include <iostream>
#include <utility>
#include <fstream>

using UnOrMapOfNames = std::unordered_map<std::string, std::string>;
using WestEastUnOrMaps = std::pair<UnOrMapOfNames, UnOrMapOfNames>;



int unorderedMapListBasketSolver(std::string);


WestEastUnOrMaps readFileToUWEM(std::string);


#endif //ASECOURSEWORK_UNORDEREDMAPLISTBASKETSOLVER_H
