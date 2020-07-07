#ifndef BOXLID_H
#define BOXLID_H
#include "Tile.h"
#include <istream>
#include <string>
#include <vector>
#include <fstream>

class Node {
public:
   TilePtr value;
   Node* next;
};

class LinkedList {
public:
   Node* head;
   int size();
   int length;
};

class Boxlid {
public:
   Boxlid();
   Boxlid(Boxlid& other);
   ~Boxlid();
   int size();
   TilePtr get(int index);
   void addTile(TilePtr tile);
   void addTile(TilePtr tile, int index);
   void removeTile(int index);
   void clear();
   void loadBoxlid(std::istream& inputStream);
   void addTileLoad(std::string);
   void saveGame(std::ofstream& myfile);
   void removeTileFromBack();
   TilePtr getTileFromBack();
   TilePtr getFront();
    void removeFront();
private:
   LinkedList* boxlid;
};

#endif
