#include <stdlib.h> /* srand, rand */
#include "Tile.h"

//intialises tile
Tile::Tile()
{
    colour = Colour(rand() % 5);
}
Tile::Tile(Colour col){
    colour = col;
}
Tile::Tile(std::string col){
    if (col == "R"){
        colour = Colour(R);
    }else if(col == "Y"){
        colour = Colour(Y);
    }else if(col == "B"){
        colour = Colour(B);
    }else if(col == "U"){
        colour = Colour(U);
    }else if (col == "L"){
        colour = Colour(L);
    }else{
        
    }
}
Tile::~Tile()
{
}

//gets color of tile
std::string Tile::getColour()
{
    std::string returnVal;

    if (colour == R) {
        returnVal = "R";
    }
    else if (colour == Y) {
        returnVal = "Y";
    }
    else if (colour == B) {
        returnVal = "B";
    }
    else if (colour == L) {
        returnVal = "L";
    }
    else if (colour == U) {
        returnVal = "U";
    }
    else {
        returnVal = "ssss";
    }
    return returnVal;
}

//gets full name of color
std::string Tile::getColourAsString()
{
    std::string returnVal;
    if (this->colour == R) {
        returnVal = "Red";
    }
    else if (this->colour == Y) {
        returnVal = "Yellow";
    }
    else if (this->colour == B) {
        returnVal = "Dark Blue";
    }
    else if (this->colour == L) {
        returnVal = "Light Blue";
    }
    else if (this->colour == U) {
        returnVal = "Black";
    }
    return returnVal;
}