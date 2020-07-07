#include <vector>
#include "Tile.h"
#include <iostream>
#ifndef MOSAIC_H
#define MOSAIC_H
#define COLS 5
#define ROWS 10
#include "Boxlid.h"


class Mosaic {
public:
    Mosaic(std::string playerName);
    ~Mosaic();
    void addTiles(std::vector<Tile> tilesAdded);
    void createMosaic(std::string playerName);
    void displayMosaic();
    void setTile(TilePtr tile, int column);
    bool checkRowFull(int row);
    void wallPlacement();
    int countSpots(int column);
    void addToBroken(TilePtr tile);
    void clearBroken();
    std::vector<TilePtr> getBroken();
    int moveTilesToRightSide(std::string** templateBoard, Boxlid* lid);
    void clearRow(int row, Boxlid* lid);
    void calculateScore(int &score);
    int checkForFullRow(int row);
    std::string checkForColour(int row);
    void setMosaicRow(std::string values, int row);
    void setMosaicPileRow(std::string values, int row);
    void addToBrokenLoad(std::string values);
    void displayMosaicRow(int i);
    void displayBroken();
    std::vector<std::string> potentialColours(std::string** templateBoard, int row);
    int getBrokenSize();


    TilePtr getBoard();
    void saveGame(std::ofstream& myfile);

private:
    TilePtr mosaicArray[COLS][ROWS];
    std::vector<TilePtr> brokenTiles;
};
#endif
