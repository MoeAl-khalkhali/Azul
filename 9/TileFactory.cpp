
#include "TileFactory.h"

//non default tilefactory
TileFactory::TileFactory(TileBag *a)
{
	length = 0;
	tileFactory = new TilePtr[4];
	for (int i = 0; i < 4; i++)
	{
		tileFactory[i] = nullptr;
	}
	for (int i = 0; i < 4; i++)
	{
		tileFactory[i] = a->getNewTile();
		a->removeTile();
		length++;
	}
}
TileFactory::~TileFactory()
{
	for (int i = 0; i < length; i++)
	{
		delete tileFactory[i];
	}
	delete tileFactory;
}

//default tilefactory constructor
TileFactory::TileFactory()
{
	length = 0;
	tileFactory = new TilePtr[17];
	for (int i = 0; i < 17; i++)
	{
		tileFactory[i] = nullptr;
		length++;
	}
}
TileFactory::TileFactory(bool dummy)
{
	length = 0;
	tileFactory = new TilePtr[4];
	for (int i = 0; i < 4; i++)
	{
		tileFactory[i] = nullptr;
		length++;
	}
}
//get tile of corresponding color
TilePtr TileFactory::pickTile(std::string colour)
{
	TilePtr returnVal = nullptr;
	for (int i = 0; i < length; i++)
	{
		if (tileFactory[i] != nullptr)
		{
			if (tileFactory[i]->getColour() == colour)
			{
				returnVal = tileFactory[i];
			}
		}
	}
	return returnVal;
}

//removes tile from factory
void TileFactory::removeTile(std::string colour)
{
	for (int i = 0; i < length; i++)
	{
		if (tileFactory[i] != nullptr)
		{
			if (tileFactory[i]->getColour() == colour)
			{
				tileFactory[i] = nullptr;
			}
		}
	}
}
bool TileFactory::contains(std::string colour)
{
	for (int i = 0; i < length; i++)
	{
		if (tileFactory[i] != nullptr)
		{
			if (tileFactory[i]->getColour() == colour)
			{
				return true;
			}
		}
	}
	return false;
}

//removes rest of the tiles after one is selected
void TileFactory::removeRestTiles(std::string colour)
{
	for (int i = 0; i < length; i++)
	{
		if (tileFactory[i] != nullptr)
		{
			if (tileFactory[i]->getColour() == colour)
			{
				tileFactory[i] = nullptr;
				return;
			}
		}
	}
}

//counts how many tiles of a certain color there is
int TileFactory::countTile(std::string colour)
{
	int count = 0;
	for (int i = 0; i < length; i++)
	{
		if (tileFactory[i] != nullptr)
		{
			if (!tileFactory[i]->getColour().compare(colour))
			{
				count++;
			}
		}
	}
	return count;
}

//gets the color of the rest of the tiles after one is selected
TilePtr TileFactory::restOfTiles(std::string colour)
{
	for (int i = 0; i < length; i++)
	{
		if (tileFactory[i] == nullptr) {}
		else
		{
			if (tileFactory[i]->getColour().compare(colour))
			{
				return tileFactory[i];
			}
		}
	}
	return nullptr;
}
//size of factory
int TileFactory::size()
{
	return this->length;
}

//display factory tiles
void TileFactory::displayTiles()
{
	for (int z = 0; z < length; z++)
	{
		if (tileFactory[z] == nullptr) {}
		else
		{
			std::string col = tileFactory[z]->getColour();
			if (col == "R")
			{
				std::cout << RED << "\u25A1" << RESET;
				std::cout << " ";
			}
		}
	}
	for (int z = 0; z < length; z++)
	{
		if (tileFactory[z] == nullptr) {}
		else
		{
			std::string col = tileFactory[z]->getColour();
			if (col == "U")
			{
				std::cout << BLACK << "\u25A1" << RESET;
				std::cout << " ";
			}
		}
	}
	for (int z = 0; z < length; z++)
	{
		if (tileFactory[z] == nullptr) {}
		else
		{
			std::string col = tileFactory[z]->getColour();
			if (col == "L")
			{
				std::cout << CYAN << "\u25A1" << RESET;
				std::cout << " ";
			}
		}
	}

	for (int z = 0; z < length; z++)
	{
		if (tileFactory[z] == nullptr) {}
		else
		{
			std::string col = tileFactory[z]->getColour();
			if (col == "B")
			{
				std::cout << BLUE << "\u25A1" << RESET;
				std::cout << " ";
			}
		}
	}
	for (int z = 0; z < length; z++)
	{
		if (tileFactory[z] == nullptr) {}
		else
		{
			std::string col = tileFactory[z]->getColour();
			if (col == "Y")
			{
				std::cout << YELLOW << "\u25A1" << RESET;
				std::cout << " ";
			}
		}
	}

	std::cout << std::endl;
}

//adds tile, mainly for default factory
void TileFactory::addTile(TilePtr tile)
{
	for (int z = 0; z < size(); z++)
	{
		if (tileFactory[z] == nullptr)
		{
			tileFactory[z] = tile;
			return;
		}
	}
}

//check if factory is empty
bool TileFactory::isEmpty()
{
	for (int i = 0; i < size(); i++)
	{
		if (tileFactory[i] != nullptr)
		{
			return false;
		}
	}
	return true;
}
void TileFactory::fillFactoryLoad(std::string values)
{

	for (int i = 0; i < length; i++)
	{
		TilePtr tile = nullptr;
		if (values[i] == 'R')
		{
			tile = new Tile(R);
		}
		else if (values[i] == 'Y')
		{
			tile = new Tile(Y);
		}
		else if (values[i] == 'L')
		{
			tile = new Tile(L);
		}
		else if (values[i] == 'B')
		{
			tile = new Tile(B);
		}
		else if (values[i] == 'U')
		{
			tile = new Tile(U);
		}
		if (tile != nullptr)
		{
			tileFactory[i] = tile;
		}
	}
}
void TileFactory::saveGame(std::ofstream& myfile){
	for (int i=0; i<length;i++){
		if (tileFactory[i] != nullptr){
		myfile << tileFactory[i]->getColour();
		}else{
			if (length >10){
				
			}else{
			myfile <<"E";
			}
		}
	}
	myfile <<"\n";
}
