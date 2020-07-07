#include <iostream>
#include "Player.h"
#include <fstream>

//constructor for player and initialises board
Player::Player(std::string name, int id)
{
	this->name = name;
	board = new Mosaic(name);
	starter = false;
	this->id = id;
	cpu = false;
}

//constructor for player and initialises board
Player::Player(std::string name, int id, int points)
{
	this->name = name;
	this->id = id;
	this->points = points;
	board = new Mosaic(name);
	starter = false;
	cpu = false;
}

Player::~Player() {}
int Player::getId()
{
	return id;
}

//gets points
int Player::getPoints()
{
	return points;
}
void Player::setStarter(bool yesOrNo)
{
	starter = yesOrNo;
}
bool Player::isStarter()
{
	return starter;
}

//resets points to zero
void Player::resetPoints()
{
	points = 0;
}

//returns name
std::string Player::getName()
{
	return name;
}
void Player::addPoints(int newPoints)
{
	points = points + newPoints;
	if (points < 0)
	{
		points = 0;
	}
}
void Player::removePoints(int newPoints)
{
	points = points - newPoints;
	if (points < 0)
	{
		points = 0;
	}
}

//returns board
Mosaic *Player::getBoard()
{
	return board;
}
bool Player::isCPU(){
	return cpu;
}
void Player::setCPU(bool cpu){
	this->cpu = cpu;
}
void Player::loadGame(std::istream &file)
{
	std::string input;
	int countRows = 0;
	std::getline(file, input, ':');
	std::string endOfType = " ";

	while (endOfType != "#")
	{
		if (input == "id")
		{
			std::getline(file, input, '\n');
			this->id = std::stoi(input);
			std::getline(file, input, ':');
		}
		else if (input == "name")
		{
			std::getline(file, this->name, '\n');
			std::getline(file, input, ':');
		}
		else if (input == "points")
		{
			std::getline(file, input, '\n');
			this->points = std::stoi(input);
			std::getline(file, input, ':');
		}
		else if (input == "mosaic")
		{
			while (countRows != 5)
			{
				if (countRows == 4)
				{
					std::getline(file, input, '\n');
				}
				else
				{
					std::getline(file, input, ',');
				}
				
					board->setMosaicRow(input, countRows);
				countRows++;
			}
			countRows = 0;
			std::getline(file, input, ':');
		}
		else if (input == "broken")
		{
			std::getline(file, input, '\n');
			
				board->addToBrokenLoad(input);

			std::getline(file, input, ':');
		}
		else if (input == "pile")
		{
			while (countRows != 5)
			{
				if (countRows == 4)
				{
					std::getline(file, input, '\n');
				}
				else
				{
					std::getline(file, input, ',');
				}
		
					board->setMosaicPileRow(input, countRows);
				

				countRows++;
			}
			countRows = 0;
			std::getline(file, input, ':');
		}
		else if (input == "starter")
		{
			std::getline(file, input, '\n');
			if (input == "1")
			{

				setStarter(true);

			}
			else
			{
	setStarter(false);

			}
			std::getline(file, input, ':');

		}
		else if (input == "CPU")
		{
			std::getline(file, input, '\n');
			if (input == "true")
			{
				cpu = true;

			}
			else
			{
				cpu = false;

			}
		}
		else
		{

			std::getline(file, endOfType, '\n');
		}
	}


}
void Player::saveGame(std::ofstream& myfile){
	myfile << "$\n";
		myfile << "type:player\n";
		myfile << "id:"<<id<<"\n";
		myfile << "name:"<<name<<"\n";
		myfile << "points:"<<points<<"\n";
		board->saveGame(myfile);
		if (starter){
			myfile << "starter:"<<"1"<<"\n";

		}else{
			myfile << "starter:"<<"0"<<"\n";
		}
		if (cpu){
			myfile << "CPU:true"<<"\n";

		}else{
			myfile << "CPU:false"<<"\n";

		}
		myfile << "#\n\n";

		//        type:player
		//        id:2
		//        name:OtherName
		//        points:123
		//        mosaic:EEEEE,EEEEE,EEEEE,EEEEE,EEEEE
		//        pile:E,EE,EEE,EEEE,EEEEE
		//        broken:EEEEEEEE
		//        starter:0

}