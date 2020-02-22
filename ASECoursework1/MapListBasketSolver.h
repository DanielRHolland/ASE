//
// Created by dan on 22/02/2020.
//

#ifndef ASECOURSEWORK_MAPLISTBASKETSOLVER_H
#define ASECOURSEWORK_MAPLISTBASKETSOLVER_H

#include <map>
#include <list>
#include <iostream>
#include <utility>
#include <fstream>

using MapOfNames = std::map<std::string, std::string>;
using WestEastMaps = std::pair<MapOfNames, MapOfNames>;



int mapListBasketSolver(std::string);


WestEastMaps readFileToWEM(std::string);


#endif //ASECOURSEWORK_MAPLISTBASKETSOLVER_H
