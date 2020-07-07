#include <string>
#include <iostream>
#ifndef TILE_H
#define TILE_H
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
enum Colour {
    R,
    Y,
    B,
    L,
    U
};

class Tile {
public:
    Tile();
    Tile(Colour col);
    Tile(std::string col);

    ~Tile();
    std::string getColour();
    std::string getColourAsString();

private:
    Colour colour;
};
typedef Tile* TilePtr;

#endif
