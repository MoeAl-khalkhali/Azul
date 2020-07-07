#include <iostream>
#include "TileFactory.h"
#include "Boxlid.h"
#ifndef TYPES_H
#define TYPES_H
Player* p1;
Player* p2;
TileFactory *tileFactory[8];
TileBag* tileBag;
Boxlid* lid;
std::string** templateBoard;
typedef std::string* TemplateMosaic;
int turns= 0;
int active =0;
#endif
