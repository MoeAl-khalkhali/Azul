#include "menu.cpp"
// ./test < testCases/testTIleRefill.input > testCases/testTIleRefill.output
// diff testCases/testTIleRefill.output testCases/testTIleRefill.output > testCases/diffTIleRefill.txt
// If doing a test please comment out the error checking for the user input, as the input command was not fully done, it does not work with it
// to run file g++ -Wall -Werror -std=c++14 -g -O -o assign1 Player.cpp TileBag.cpp Tile.cpp main.cpp Mosaic.cpp TileFactory.cpp Boxlid.cpp
// some design choices. unable to add different coloured tile to mosaic is part of user input checking
// unable to add tile to row if the right side of the tile in that row is already filled is part of user input checking
// unable to directly add to broken is a design decision, as there is no reasonable reason to want to do that, alternatively
// if they try to add a tile to an already full row it will go to the broken. we did this as it might be a tactical decision to do so (eg tiles almost full and they do not want ruin a row 
// and be stick with one tile in that row until the next round).
// we did comment out all user input testing as it was invalid and giving us errors that prevented us from running tests throgh termianl
int main(){
    Menu menu;
    return 0;
}

