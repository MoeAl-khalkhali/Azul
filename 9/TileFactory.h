#ifndef TILEFACTORY_H
#define TILEFACTORY_H
#include "TileBag.h"
#include "Tile.h"
#include <fstream>

class TileFactory {
public:
	TileFactory(TileBag* a);
	TileFactory();
	~TileFactory();
	TilePtr pickTile(std::string colour);
	void removeTile(std::string colour);
	int countTile(std::string colour);
	TilePtr restOfTiles(std::string colour);
	void removeRestTiles(std::string colour);
	void addTile(TilePtr tile);
	void displayTiles();
	bool contains(std::string colour);
	int size();
	bool isEmpty();
	void fillFactoryLoad(std::string values);
	TileFactory(bool dummy);
	void saveGame(std::ofstream& myfile);


private:
	TilePtr* tileFactory;
	int length;
};
#endif
