#include <iostream>
#include "Mosaic.h"
#include <vector>
#include <fstream>

//constructior for mosaic, intilises it to correct dimensions
Mosaic::Mosaic(std::string playerName)
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			mosaicArray[i][j] = nullptr;
		}
	}
}

//adds tile to broken part
void Mosaic::addToBroken(TilePtr tile)
{
	brokenTiles.push_back(tile);
}

//gets the broken tiles
std::vector<TilePtr> Mosaic::getBroken()
{
	return brokenTiles;
}

//displays the mosaic
void Mosaic::displayMosaic()
{
	int rows = 4;
	int counter = 1;
	for (int i = 0;i < 5;i++){
		std::cout<< counter <<".  ";
		counter++;
		for (int x = 0; x < rows; x++){
			std::cout<<"  ";
		}
		rows--;
		for (int j = 0;j < i+5+1;j++){
			if (j == i + 1){
				std::cout << "|| ";
			}
			if (mosaicArray[i][j] != nullptr) {
				std::string col = mosaicArray[i][j]->getColour();
				if (col == "R"){
					std::cout << RED <<"\u25A1"<<RESET;

				}else if (col == "U"){
					std::cout << BLACK <<"\u25A1"<<RESET;

				}else if (col== "L"){
					std::cout << CYAN <<"\u25A1"<<RESET;

				}else if (col == "Y"){
					std::cout << YELLOW <<"\u25A1"<<RESET;

				}else {
				std::cout << BLUE <<"\u25A1"<<RESET;
				}
				std::cout << " ";
			}else{
				std::cout<<"\u25A1 ";

			}
		}
		std::cout<<std::endl;

	}
	displayBroken();
	std::cout << std::endl << std::endl;
}
void Mosaic::displayBroken(){
	std::cout << "broken: ";
	int sizeOfBroken;
	sizeOfBroken = brokenTiles.size();
	for (int i = 0; i < sizeOfBroken; i++) {
		if (brokenTiles[i] != nullptr) {
			std::string col = brokenTiles[i]->getColour();
			if (col == "R"){
				std::cout << RED <<"\u25A1"<<RESET;

			}else if (col == "U"){
				std::cout << BLACK <<"\u25A1"<<RESET;

			}else if (col== "L"){
				std::cout << CYAN <<"\u25A1"<<RESET;

			}else if (col == "Y"){
				std::cout << YELLOW <<"\u25A1"<<RESET;

			}else {
			std::cout << BLUE <<"\u25A1"<<RESET;
			}
		
		}
	}
	for ( int x = 0; x < 9 - brokenTiles.size();x++){
		std::cout << "\u25A1";
	}
}
//displays the mosaic
void Mosaic::displayMosaicRow(int i)
{
	
	int rows = 4-i;
	for (int x = 0; x < rows; x++){
		std::cout<<"  ";
	}
	for (int j= 0; j< i+6; j++){
		if (j == i + 1){
			std::cout << "|| ";
		}
			if (mosaicArray[i][j] != nullptr) {
				std::string col = mosaicArray[i][j]->getColour();
				if (col == "R"){
					std::cout << RED <<"\u25A1"<<RESET;

				}else if (col == "U"){
					std::cout << BLACK <<"\u25A1"<<RESET;

				}else if (col== "L"){
					std::cout << CYAN <<"\u25A1"<<RESET;

				}else if (col == "Y"){
					std::cout << YELLOW <<"\u25A1"<<RESET;

				}else {
				std::cout << BLUE <<"\u25A1"<<RESET;
				}
				std::cout << " ";
			}else{
				std::cout<<"\u25A1 ";
			}
		
	}

}

std::vector<std::string> Mosaic::potentialColours(std::string** templateBoard, int row){
	std::vector<std::string> potentialColours;
	int counter = 0;
	for (int i = row+1; i<row+5+1;i++){
	if (mosaicArray[row][i] == nullptr){
		potentialColours.push_back(templateBoard[row][counter]);
	}
	counter++;
	}
	return potentialColours;
}

//count how many free spots in a row
int Mosaic::countSpots(int row)
{
	int count = 0;

	for (int i=0; i < row;i++){
		if (mosaicArray[row-1][i] == nullptr){
			count++;
		}
	}
//	OLD METHOD
//	int superSpaces = 0;
//	for (int i = 0; i < COLS; i++) {
//		for (int j = 0; j < ROWS - superSpaces; j++) {
//			if (j == i + 1) {
//			}
//			else {
//				if (i == row - 1 && mosaicArray[i][j] == nullptr) {
//					if (j > row - 1) {
//					}
//					else {
//						count++;
//					}
//				}
//			}
//		}
//	}
	return count;
}

//empties the broken tiles
void Mosaic::clearBroken()
{
	brokenTiles.clear();
}

//sets a tile in the array
void Mosaic::setTile(TilePtr tile, int row)
{
		for (int j=row-1;j>=0;j--){
			if (mosaicArray[row-1][j] == nullptr){
				mosaicArray[row-1][j] = tile;
				return;
			}
		}
	
}

//moves the tiles from the left side of the mosaic to the right side if they are full
int Mosaic::moveTilesToRightSide(std::string** templateBoard, Boxlid* lid)
{
	int points = 0;
	bool vertical = false;
	bool horozontal = false;
	int temp=0;
	//template board is the board used to compare the right side with, to ensure correct placement of tiles
	//check to make sure only one tile is added on the right side.
	int check = 0;
	for (int i = 0; i < 5; i++) {
		check = 0;
		if (countSpots(i + 1) == 0) {
			std::string toBePlaced = mosaicArray[i][i]->getColour();
			TilePtr tile = mosaicArray[i][i];
			for (int j = 0; j < 5; j++) {
				if (templateBoard[i][j] == toBePlaced) {
					int a = j + i + 1;
					
//					1 point for new tile
					if (mosaicArray[i][a] == nullptr && check == 0) {
						mosaicArray[i][a] = tile;
						points++;
						temp = i+1;
						int x = a + 1;
						
//						iterate to the up, each tile add one point
						while (mosaicArray[temp][x] != nullptr && temp < 5){
							temp++;
							points++;
							x++;
							horozontal = true;
						}
						 x = a - 1;
						temp = i-1;
//						iterate to the down, each tile add one point
						while (mosaicArray[temp][x] != nullptr && temp >= 0){
							temp--;
							points++;
							x--;
							horozontal = true;
						}
						temp = a+1;
//						iterate to the left, each tile add one point
						while (mosaicArray[i][temp] != nullptr && temp < i+6){
							temp++;
							points++;
							vertical = true;
						}
						temp = a-1;
//						iterate to the right, each tile add one point
						while (mosaicArray[i][temp] != nullptr && temp > i+1){
							temp--;
							points++;
							vertical = true;
						}
//						if there is a tile vertically or horoztally adjacent, add an extra point as the tile itself gets counted twice
						if (vertical && horozontal){
							points++;
						}
						check++;
					}
				}
			}
//			clears pile
			clearRow(i + 1, lid);
		}
	}
	return points;
}

//clears the row on the left side, for when they are moved to the right side
void Mosaic::clearRow(int column, Boxlid* lid)
{
	int superSpaces = 0;
	for (int i = 0; i < COLS; i++) {
		for (int j = 0; j < ROWS - superSpaces; j++) {
			if (j == i + 1) {
			}
			else {
				if (i == column - 1) {
					if (j > column - 1) {
					}
					else {
						lid->addTile(mosaicArray[i][j]);
						mosaicArray[i][j] = nullptr;
					}
				}
			}
		}
	}
}

//Passes in a score by reference and allows for it to be printed out
void Mosaic::calculateScore(int &score)
{
	std::cout << std::endl << "SCORE: " << score << std::endl << std::endl;
}

//Checks to see if a row is full. Meant for scoring
int Mosaic::checkForFullRow(int row)
{
	int count = 0;
	for (int i = 0; i<5;i++){
			if (mosaicArray[row][i+1+row] != nullptr){
				count++;
			}
		
	}
	return count;
}

std::string Mosaic::checkForColour(int row)
{
	if (mosaicArray[row-1][row-1] != nullptr){
		return mosaicArray[row-1][row-1]->getColour();
	}
	return "";
}

void Mosaic::setMosaicRow(std::string values, int row){
	for (int i=0;i<5;i++){
		TilePtr tile;
		if (values[i] == 'R'){
			 tile = new Tile(R);
		}else if (values[i] == 'Y'){
			 tile = new Tile(Y);
		}else if (values[i] == 'L'){
			 tile = new Tile(L);
		}else if (values[i] == 'B'){
			 tile = new Tile(B);
		}else if (values[i] == 'U'){
			 tile = new Tile(U);
		}else{
			 tile = nullptr;
		}
		mosaicArray[row][row+1+i] = tile;
	}
}
void Mosaic::setMosaicPileRow(std::string values, int row){
	for (int i=0;i<row+1;i++){
		TilePtr tile;
		if (values[i] == 'R'){
			 tile = new Tile(R);
		}else if (values[i] == 'Y'){
			 tile = new Tile(Y);
		}else if (values[i] == 'L'){
			 tile = new Tile(L);
		}else if (values[i] == 'B'){
			 tile = new Tile(B);
		}else if (values[i] == 'U'){
			 tile = new Tile(U);
		}else{
			 tile = nullptr;
		}
		if (tile != nullptr){
		mosaicArray[row][i] = tile;
		}
	}
}
void Mosaic::addToBrokenLoad(std::string values){
	for (int i=0;i<9;i++){
		TilePtr tile;
		if (values[i] == 'R'){
			 tile = new Tile(R);
		}else if (values[i] == 'Y'){
			 tile = new Tile(Y);
		}else if (values[i] == 'L'){
			 tile = new Tile(L);
		}else if (values[i] == 'B'){
			 tile = new Tile(B);
		}else if (values[i] == 'U'){
			 tile = new Tile(U);
		}else{
			 tile = nullptr;
		}
		if (tile != nullptr){
		brokenTiles.push_back(tile);
		}
	}
	
}
void Mosaic::saveGame(std::ofstream& myfile){
			myfile << "mosaic:";
			for (int i =0; i<5;i++){
				for (int j=i+1;j<i+5+1;j++){
					if (mosaicArray[i][j] != nullptr){
					myfile << mosaicArray[i][j]->getColour();
					}else{
						myfile << "E";

					}
				}
				if (i==4){
					
				}else{
				myfile << ",";}
			}
			
			myfile << "\npile:";
			for (int i =0; i<5;i++){
				for (int j=0;j<i+1;j++){
					if (mosaicArray[i][j] != nullptr){
					myfile << mosaicArray[i][j]->getColour();
					}else{
						myfile << "E";

					}
				}
				if (i==4){
					
				}else{
				myfile << ",";}
			}
			myfile << "\nbroken:";
			for (int i =0; i<brokenTiles.size();i++){
				myfile << brokenTiles[i]->getColour();
			}
			myfile << "\n";

}
int Mosaic::getBrokenSize(){
	return brokenTiles.size();
}
//$
//type:player
//id:1
//name:SomeName
//points:123
//mosaic:EREEE,EEEEE,EEEEE,EEEEE,RUYLE
//pile:R,EY,ERR,EEEE,BBBBB
//broken:EREEYERR
//starter:1
//#