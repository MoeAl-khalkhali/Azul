#include "Tile.h"
#ifndef TILEBAG_H
#define TILEBAG_H
#include <vector>
#include <fstream>
#include "Boxlid.h"

class TileBag {
public:
    TileBag();
    TileBag(std::string seed);
    ~TileBag();
    TilePtr get(int index);
    void removeTile();
    TilePtr getNewTile();
    int size();
    void saveGame(std::ofstream& myfile);
    void refill(Boxlid* lid);


private:
    std::vector<TilePtr> tileBag;
};
#endif