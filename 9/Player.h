#include <iostream>
#include "Mosaic.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player(std::string name, int id);
    Player(std::string name, int id, int points);
    ~Player();
    int getPoints();
    void resetPoints();
    std::string getName();
    Mosaic* getBoard();
    void addPoints(int points);
    void removePoints(int points);
    void loadGame(std::istream& inputStream);
    void setStarter(bool yesOrNo);
    bool isStarter();
    int getId();
    void saveGame(std::ofstream& myfile);
    void setCPU(bool cpu);
    bool isCPU();



private:
    int points;
    std::string name;
    Mosaic* board;
    int id;
    bool starter;
    bool cpu;
    
};
#endif