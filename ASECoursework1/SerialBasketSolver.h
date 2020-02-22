#ifndef ASECOURSEWORK_SERIALBASKETSOLVER_H
#define ASECOURSEWORK_SERIALBASKETSOLVER_H

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

int serialAlgorithm(std::string fileName);
ListOfNamePairs readFile(std::string);
ListOfPositionedNames onePass(ListOfNamePairs, ListOfPositionedNames, int, int);

#endif //ASECOURSEWORK_SERIALBASKETSOLVER_H
