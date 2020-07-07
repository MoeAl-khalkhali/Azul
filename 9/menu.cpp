#include <iostream>
#include "Mosaic.h"
#include "Player.h"
#include "Types.h"
#include "TileBag.h"
#include "TileFactory.h"
#include <fstream>

class Menu
{
  public:
    Menu()
    {
      //while loop for the menu.
      while (!std::cin.eof())
      {
        int input;
        std::cout << "Main Menu" << std::endl <<
          "---" << std::endl <<
          "1 - New 1 Player Game" << std::endl <<
          "2 - New 2 Player Game" << std::endl <<
          "3 - Load game" << std::endl <<
          "4 - View credits" << std::endl <<
          "5 - Quit" << std::endl <<
          std::endl;

        //input testing
        std::string errorMsg = "Invalid user input";
        bool checker = true;
        while (checker)
        {
          std::cout << "> ";
          std::cin >> input;
          if (std::cin.fail())
          {
            errorMsg = "Invalid data type";
            std::cin.clear();
            fflush(stdin);
            std::cout << errorMsg << std::endl;
          }
          else if ((int) input < 1 || (int) input > 5)
          {
            errorMsg = "User input \"" + std::to_string(input) + "\" is outside scope (1 to 4)";
            std::cin.clear();
            fflush(stdin);
            std::cout << errorMsg << std::endl;
          }
          else if (input == 1)
          {
            std::cin.clear();
            fflush(stdin);
            newGameOnePlayer();
            playRound();
            checker = false;
          }
          else if (input == 2)
          {
            checker = false;
            std::cin.clear();
            fflush(stdin);
            newGame();
            playRound();
          }
          else if (input == 3)
          {
            std::string filename;
            std::cout << "Enter File Name Please" << std::endl;
            std::cin >> filename;
            std::cin.clear();
            fflush(stdin);
            loadGame(filename);
            checker = false;

          }
          else if (input == 4)
          {
            checker = false;
            std::cin.clear();
            fflush(stdin);
            viewCredits();
          }
          else if (input == 5)
          {
            std::cin.clear();
            fflush(stdin);
            checker = false;
            Quit();
          }
        }
      }
    }

  // initialisation of data structures, players etc
  void newGame()
  {
    tileBag = new TileBag();
    lid = new Boxlid();
    fillTiles();
    std::string playerName = "";
    std::cout << "\nEnter a name for player 1" << std::endl;
    std::cout << "> ";
    std::cin >> playerName;
    std::cout << std::endl;

    //intialises player
    p1 = new Player(playerName, 1);
    p1->setStarter(true);
    std::cout << "\nEnter a name for player 2" << std::endl;
    std::cout << "> ";
    std::cin >> playerName;
    std::cout << std::endl;
    p2 = new Player(playerName, 2);
  }

  // initialisation of data structures, players etc
  void newGameOnePlayer()
  {
    tileBag = new TileBag();
    lid = new Boxlid();
    fillTiles();
    std::string playerName = "";
    std::cout << "\nEnter a name for player 1" << std::endl;
    std::cout << "> ";
    std::cin >> playerName;
    std::cout << std::endl;

    //intialises player
    p1 = new Player(playerName, 1);
    p1->setStarter(true);
    p2 = new Player("CPU", 2);
    p2->setCPU(true);
  }

  //fills the tilefactory values from the tilebag
  void fillTiles()
  {
    tileFactory[0] = new TileFactory();
    if (tileBag->size() < 20)
    {
      tileBag->refill(lid);
    }
    for (int i = 1; i < 6; i++)
    {

      tileFactory[i] = new TileFactory(tileBag);
    }
  }

  //prints credit out
  void viewCredits()
  {
    std::cout << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Name: Nitaf Bar" << std::endl;
    std::cout << "Student ID: s3717378" << std::endl;
    std::cout << "Email: s3717378@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;
    std::cout << "Name: Mouhannad Al Khalkhali" << std::endl;
    std::cout << "Student ID: s3749653" << std::endl;
    std::cout << "Email: s3749653@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;
    std::cout << "Name: Roland Shillam" << std::endl;
    std::cout << "Student ID: s3724076" << std::endl;
    std::cout << "Email: s3724076@student.rmit.edu.au" << std::endl;
    std::cout << "----------------------------------------" << std::endl <<
      std::endl;
  }

  //exits program
  void Quit()
  {
    std::cout << "\nGoodbye" << std::endl <<
      std::endl;
    exit(0);
  }

  //prints out factories
  void displayFactories()
  {
    //outputs factories
    std::cout << "Factories " << std::endl;
    for (int i = 0; i < 6; i++)
    {
      std::cout << i << ". ";
      tileFactory[i]->displayTiles();
    }

    std::cout << std::endl <<
      std::endl;
  }

  //prints out the mosaic
  void displayMosaic(Player *player)
  {
    std::cout << "Mosaic for " << player->getName() << ":" << std::endl;
    player->getBoard()->displayMosaic();
  }
  void displayBothMosaic(Player *currPlayer, Player *otherPlayer)
  {
    std::cout << "Mosaics for:" << std::endl << "(current player): " << std::endl << currPlayer->getName() << ":" << "\t\t\t\tOpponents Mosaic: " << otherPlayer->getName() << ":" << std::endl;
    int rowCounter = 1;
    for (int i = 0; i < 5; i++)
    {
      std::cout<<rowCounter<<". ";
      rowCounter++;
      currPlayer->getBoard()->displayMosaicRow(i);
      std::cout << "\t || \t";
      otherPlayer->getBoard()->displayMosaicRow(i);
      std::cout << std::endl;
    }
    currPlayer->getBoard()->displayBroken();
    std::cout << "\t\t";
    otherPlayer->getBoard()->displayBroken();
    std::cout << std::endl;
  }

  //initialises a round to play
  void playRound()
  {
    std::cout << "=== Start Round ===" << std::endl;

    while (true)
    {
      //checks if tilefactory is empty, if it isnt it play a round, if it is, tiles moved to the other side, broken is cleared to box lid, and left moved to right side of mosaic. If tilebag is not empty, the factory is refilled.

      if (!isEmpty())
      {
       	//check for starter token
        if (p1->isStarter())
        {
          playTurn(p1);
          active = p2->getId();
          turns++;
        }
        else
        {
          if (p2->isCPU())
          {
            playTurnCPU(p2);
          }
          else
          {
            playTurn(p2);
          }
          active = p1->getId();

          turns++;
        }
      }
      else
      {
       	//end of round
        moveTilesToOtherSide(p1);
        moveTilesToOtherSide(p2);
        clearBroken(p1);
        clearBroken(p2);
        printScore(p1);
        printScore(p2);
        fillTiles();
        if (checkForGameOver(p1) || checkForGameOver(p2))
        {
          return;
        }

        if (p1->isStarter())
        {
          playTurn(p1);
          active = p2->getId();

          turns++;
        }
        else
        {
         		//checks if 
          if (p2->isCPU())
          {
            playTurnCPU(p2);
          }
          else
          {
            playTurn(p2);
          }
          active = p1->getId();

          turns++;
        }
      }
      //ensure tile factories arent empty
      if (!isEmpty())
      {
        if (!p1->isStarter())
        {
          playTurn(p1);
          active = p2->getId();
          turns++;
        }
        else
        {
          if (p2->isCPU())
          {
            playTurnCPU(p2);
          }
          else
          {
            playTurn(p2);
          }
          active = p1->getId();
          turns++;
        }
      }
      else
      {

        moveTilesToOtherSide(p1);
        moveTilesToOtherSide(p2);
        clearBroken(p1);
        clearBroken(p2);
        printScore(p1);
        printScore(p2);
        fillTiles();
        if (checkForGameOver(p1) || checkForGameOver(p2))
        {
          return;
        }
        if (!p1->isStarter())
        {
          playTurn(p1);
          active = p2->getId();

          turns++;
        }
        else
        {
          if (p2->isCPU())
          {
            playTurnCPU(p2);
          }
          else
          {
            playTurn(p2);
          }
          active = p1->getId();

          turns++;
        }
      }
    }
  }

  // checks if the tile factories are all empty
  bool isEmpty()
  {
    for (int i = 0; i < 6; i++)
    {
      if (!tileFactory[i]->isEmpty())
      {
        return false;
      }
    }
    return true;
  }

  //moves broken tiles to the box lid
  void clearBroken(Player *player)
  {
    std::vector<TilePtr> broken;
    broken = player->getBoard()->getBroken();
    TilePtr tile;
    int count = 0;
    for (int i = 0; i < (int) broken.size(); i++)
    {
      if (broken[i] != nullptr)
      {
        tile = broken[i];
        lid->addTile(tile);
        count++;
      }
    }
    player->removePoints(count);
    player->getBoard()->clearBroken();
  }

  //initalises the players turn
  void playTurn(Player *player)
  {
    std::cout << "TURN FOR " << player->getName() << std::endl;
    displayFactories();
    if (player->getId() == p1->getId())
    {
      displayBothMosaic(player, p2);
    }
    else
    {
      displayBothMosaic(player, p1);
    }
    //    displayMosaic(player);
    std::string turn = "";
    std::string tempFactoryRow = "";
    int mosaicRow = 10;
    std::string colourChosen = "";
    int factoryRow = -1;

    //Error checking for the three turn inputs (factoryRow, colourChosen and mosaicRow)
    bool isInvalid = false;
    std::string action;
    bool loop = false;
    // If doing a test please comment out the error checking for the user input, as the input command was not fully done, it does not work with it
    while (!isInvalid)
    {
      bool fr = true;
      bool mr = true;
      bool cc = true;
      std::cout << ">";
      std::cin >> action;

      if (action == "-help")
      {
        std::cout << std::endl << "HOW TO PLAY" << std::endl << "_________________" << std::endl << std::endl;
        std::cout << "Type your move in the following format" << std::endl;
        std::cout << "turn factory colour mosaicRow" << std::endl;
        std::cout << "where factory is which factory row you would like to choose from" << std::endl;
        std::cout << "where colour is which colour you would like to choose" << std::endl;
        std::cout << "where mosaicRow is which mosaicRow row you would like to place the tile in" << std::endl;
        std::cout << "eg. turn 1 B 1" << std::endl;
        std::cout << "When picking which mosaic row to pick, the row must only have the same colour or no colour already there. if it is full with the same colour, it will go to the broken bag " << std::endl;
        std::cout << std::endl << "USEFULL COMMANDS" << std::endl << "_________________" << std::endl << std::endl;
        std::cout << "-save to save game" << std::endl;
        std::cout << "-om to print the oppenents mosaic" << std::endl;
        std::cout << "-mm to print your mosaic" << std::endl;
        std::cout << "-tf to print factory tiles" << std::endl;
        std::cout << "-menu to return to the main menu" << std::endl;

        std::cout << std::endl << std::endl << "COLOUR SYMBOLS" << std::endl << "_________________" << std::endl << "R = red";
        std::cout << std::endl << "Y = yellow";
        std::cout << std::endl << "U = black";
        std::cout << std::endl << "b = blue";
        std::cout << std::endl << "l = light blue" << std::endl;
      }
      //exit the game
      else if (action == "-exit")
      {
        std::cout << "Thanks for playing!" << std::endl;
        //destructor for variables
        for (int i = 1; i < 6; i++)
        {
          tileFactory[i]->~TileFactory();
        }
        tileBag->~TileBag();
        p1->~Player();
        p2->~Player();
        lid->~Boxlid();
        exit(0);
        }else if (action == "-menu")
        {
          std::cout << "Thanks for playing!" << std::endl;
          //destructor for variables
          for (int i = 1; i < 6; i++)
          {
            tileFactory[i]->~TileFactory();
          }
          tileBag->~TileBag();
          p1->~Player();
          p2->~Player();
          lid->~Boxlid();
          Menu();
          }
        //print mosaic (opponents)
      else if (action == "-om")
      {
        if (player->getId() == p1->getId())
        {
          displayMosaic(p2);
        }
        else
        {
          displayMosaic(p1);
        }
      }
      //print mosaic (current players)

      else if (action == "-mm")
      {
        if (player->getId() == p1->getId())
        {
          displayMosaic(p1);
        }
        else
        {
          displayMosaic(p2);
        }
      }
      //print tile factories 
      else if (action == "-tf")
      {
        displayFactories();
      }
      else if (action == "-save")
      {
        //saves game then quits
        std::string fileName;
        std::cout << "Enter a name for the save file:" << std::endl;
        std::cin >> fileName;
        saveGame(fileName);
        for (int i = 1; i < 6; i++)
        {
          tileFactory[i]->~TileFactory();
        }
        tileBag->~TileBag();
        p1->~Player();
        p2->~Player();
        lid->~Boxlid();
        exit(0);
      }
      //validation for turn
      else if (action == "turn")
      {
        std::cin >> factoryRow;

        if (!std::cin || factoryRow < 0 || factoryRow > 5)
        {
          fr = false;
          std::cin.clear();
          fflush(stdin);
        }
        else
        {
          if (tileFactory[factoryRow]->isEmpty())
          {
            fr = false;
            std::cin.clear();
            fflush(stdin);
          }
        }

        if (fr)
        {
          //checks if a colour is actually chosen
          std::cin >> colourChosen;
          if (!std::cin || (colourChosen != "Y" && colourChosen != "B" && colourChosen != "R" && colourChosen != "L" && colourChosen != "U"))
          {
            std::cin.clear();
            fflush(stdin);
            cc = false;
          }
          else
          {
            //checks if tileFactory contains the colour
            if (!tileFactory[factoryRow]->contains(colourChosen))
            {
              cc = false;
              std::cin.clear();
              fflush(stdin);
            }
          }
        }

//      validation for mosaic row
        if (cc && fr)
        {
          std::cin >> mosaicRow;

          if (!std::cin || mosaicRow < 1 || mosaicRow > 5)
          {
            mr = false;
            std::cin.clear();
            fflush(stdin);
          }

          if (player->getBoard()->checkForColour(mosaicRow) != "")
          {

            if (player->getBoard()->checkForColour(mosaicRow) != colourChosen)
            {
              mr = false;
              std::cin.clear();
              fflush(stdin);
            }
            if (player->getBoard()->countSpots(mosaicRow) == 0)
            {
              mr = true;
            }
          }
        }
        //if everything is valid exit loop
        if (mr && cc && fr)
        {
          isInvalid = true;
        }
        else
        {
          //invalid turn input
          std::cout << "Invalid Input, Please try again" << std::endl <<
            std::endl;
            loop = true;
          std::cin.clear();
          fflush(stdin);
        }
      }
      else
      {
        //invalid action input
        std::cout << "Invalid Input, Please try again" << std::endl <<
          std::endl;
        std::cin.clear();
        fflush(stdin);
      }
    }
//    }

    // gets tile from factory
    TilePtr tile = tileFactory[factoryRow]->pickTile(colourChosen);
    
    //counts how many tiles in the factory of that color
    int countTiles = tileFactory[factoryRow]->countTile(colourChosen);

    //checks if the the player has enough spots in the row. if not, moves excess to broken
    if (countTiles > player->getBoard()->countSpots(mosaicRow))
    {
      int diff = countTiles - player->getBoard()->countSpots(mosaicRow);
      for (int i = 0; i < diff; i++)
      {
        if (player->getBoard()->getBrokenSize() < 9)
        {
          //if broken is not full add to the broken
          player->getBoard()->addToBroken(tile);
        }
        else
        {
//          if brokens full add to lid
          lid->addTile(tile);
        }
      }
    }

    //sets the tile in the board (logic for excess tiles in the mosaic class)
    for (int i = 0; i < countTiles; i++)
    {
      player->getBoard()->setTile(tile, mosaicRow);
    }

    //moves rest of tiles to default factory
    for (int i = 0; i < tileFactory[factoryRow]->size(); i++)
    {

      // only removes rest of tiles to default factory(after one is picked) if the factory picked from is not 0
      if (factoryRow != 0)
      {
        TilePtr restTile = tileFactory[factoryRow]->restOfTiles(colourChosen);
        tileFactory[0]->addTile(restTile);
        if (restTile != nullptr)
        {
          tileFactory[factoryRow]->removeRestTiles(restTile->getColour());
        }
      }
    }
    //removes tile from the factory
    tileFactory[factoryRow]->removeTile(colourChosen);
  }
  //creates template for mosaic
  std::string **createMosaicTemplate(int height, int width)
  {
    std::string **templateForMosaic = 0;
    templateForMosaic = new std::string *[height];

    for (int h = 0; h < height; h++)
    {
      templateForMosaic[h] = new std::string[width];

      for (int w = 0; w < width; w++)
      {
       	// fill in some initial values
        // (filling in zeros would be more logic, but this is just for the example)
        templateForMosaic[h][w] = '.';
      }
    }
    //creates template mosaic to compare player mosaic to for when moving tiles.
    int i = 0;
    int j = 0;
    int count = 0;
    while (count < 5)
    {
      templateForMosaic[i][j] = 'B';
      count++;
      j++;
      i++;
      if (count == 5)
      {
        count = 1;
        i = 1;
        j = 0;
        while (count < 5)
        {
          templateForMosaic[i][j] = 'L';
          i++;
          j++;
          count++;
        }
        if (count == 5)
        {
          count = 2;
          i = 2;
          j = 0;
          while (count < 5)
          {
            templateForMosaic[i][j] = 'U';
            i++;
            j++;
            count++;
          }
          if (count == 5)
          {
            count = 3;
            i = 3;
            j = 0;
            while (count < 5)
            {
              templateForMosaic[i][j] = 'R';
              i++;
              j++;
              count++;
            }
            if (count == 5)
            {
              count = 4;
              i = 4;
              j = 0;
              while (count < 5)
              {
                templateForMosaic[i][j] = 'Y';
                i++;
                j++;
                count++;
              }
              if (count == 5)
              {
                count = 1;
                i = 0;
                j = 1;
                while (count < 5)
                {

                  templateForMosaic[i][j] = 'Y';
                  i++;
                  j++;
                  count++;
                }
                if (count == 5)
                {
                  count = 2;
                  i = 0;
                  j = 2;
                  while (count < 5)
                  {
                    templateForMosaic[i][j] = 'R';
                    i++;
                    j++;
                    count++;
                  }
                }
                if (count == 5)
                {
                  count = 3;
                  i = 0;
                  j = 3;
                  while (count < 5)
                  {

                    templateForMosaic[i][j] = 'U';
                    i++;
                    j++;
                    count++;
                  }
                  if (count == 5)
                  {
                    count = 4;
                    i = 0;
                    j = 4;
                    while (count < 5)
                    {
                      templateForMosaic[i][j] = 'L';
                      i++;
                      j++;
                      count++;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    return templateForMosaic;
  }

  bool checkForGameOver(Player *player)
  {
    int count = 0;
    for (int i = 0; i < 5; i++)
    {
      count = player->getBoard()->checkForFullRow(i);
      if (count == 5)
      {
        for (int i = 1; i < 6; i++)
        {
          tileFactory[i]->~TileFactory();
        }
        std::cout << "Game Over" << std::endl;
        if (p1->getPoints() > p2->getPoints())
        {

          std::cout << p1->getName() << " is the winner" << std::endl;
        }
        else if (p2->getPoints() > p1->getPoints())
        {
          std::cout << p2->getName() << " is the winner" << std::endl;
        }
        else
        {
          std::cout << "No Winner, it was a draw!" << std::endl;
        }
        tileBag->~TileBag();
        p1->~Player();
        p2->~Player();
        lid->~Boxlid();
        return true;
      }
    }
    return false;
  }

  //moves tiles from left to right and creates template to compare to
  void moveTilesToOtherSide(Player *player)
  {
    int points = 0;
    templateBoard = createMosaicTemplate(5, 5);
    points = player->getBoard()->moveTilesToRightSide(templateBoard, lid);
    player->addPoints(points);
    //deletes memory for the template when done
    for (int i = 0; i != 5; ++i)
    {
      delete[] templateBoard[i];
    }
    delete templateBoard;
  }

  void printScore(Player *player)
  {
    std::cout << player->getName() << "'s Score: " << player->getPoints() << std::endl;
  }

  void loadGame(std::string filename)
  {

    std::string newActive;
    std::ifstream file(filename);
    if (!file.good()){
      std::cout<<std::endl<<"*******File Not found*******"<<std::endl<<std::endl;
      return;
    }
    std::string input;
    bool player1 = true;
    while (!file.eof())
    {
      std::string start;
      std::string type;
      file >> start;

      if (start == "$")
      {
        std::getline(file, input, ':');
        std::getline(file, input, '\n');

        if (input == "player")
        {
          if (player1)
          {
            p1 = new Player("ad", 1);
            p1->loadGame(file);

            player1 = false;
          }
          else
          {
            p2 = new Player("aasdad", 2);
            p2->loadGame(file);
          }
        }
        else if (input == "factory")
        {
          tileFactory[0] = new TileFactory();
          for (int i = 1; i < 6; i++)
          {
            tileFactory[i] = new TileFactory(false);
          }
          int factoryCount = 1;
          while (input != "#")
          {
            std::getline(file, input, ':');
            std::getline(file, input, '\n');
            if (factoryCount == 6)
            {
              tileFactory[0]->fillFactoryLoad(input);
              std::getline(file, input, '\n');
            }
            else
            {
              tileFactory[factoryCount]->fillFactoryLoad(input);
              factoryCount++;
            }
          }
        }
        else if (input == "game")
        {
          std::getline(file, input, ':');

          while (input != "#")
          {
            if (input == "turns")
            {
              std::getline(file, input, '\n');
              turns = std::stoi(input);
              std::getline(file, input, ':');
            }
            else if (input == "active")
            {
              std::getline(file, newActive, '\n');
              active = std::stoi(newActive);
              std::getline(file, input, ':');
            }
            else if (input == "bag")
            {
             				//                        set tilebag
              std::getline(file, input, '\n');
              tileBag = new TileBag(input);
              std::getline(file, input, ':');
            }
            else if (input == "lid")
            {
              std::getline(file, input, '\n');
              lid = new Boxlid();
              lid->addTileLoad(input);
              std::getline(file, input, ':');
            }
          }
        }
      }
    }
    if (p1->getId() == active)
    {
      if (p1->isStarter())
      {
        playRound();
      }
      else
      {
        if (!isEmpty())
        {
          playTurn(p1);
          turns++;
          playRound();
        }
        else
        {
          moveTilesToOtherSide(p1);
          moveTilesToOtherSide(p2);
          clearBroken(p1);
          clearBroken(p2);
          printScore(p1);
          printScore(p2);
          fillTiles();
          if (checkForGameOver(p1) || checkForGameOver(p2))
          {
            return;
          }
        }
      }
    }
    else
    {
      if (p2->isStarter())
      {
        playRound();
      }
      else
      {
        if (!isEmpty())
        {
          if (p2->isCPU())
          {
            playTurnCPU(p2);
          }
          else
          {
            playTurn(p2);
          }

          turns++;
          playRound();
        }
        else
        {
          moveTilesToOtherSide(p1);
          moveTilesToOtherSide(p2);
          clearBroken(p1);
          clearBroken(p2);
          printScore(p1);
          printScore(p2);
          fillTiles();
          if (checkForGameOver(p1) || checkForGameOver(p2))
          {
            return;
          }
        }
      }
    }
  }
  void saveGame(std::string save)
  {
    std::ofstream myfile;
    myfile.open(save);
    p1->saveGame(myfile);
    p2->saveGame(myfile);
    myfile << "$\n";

    myfile << "type:factory\n";

    for (int i = 1; i < 6; i++)
    {
      myfile << "f" << i << ":";
      tileFactory[i]->saveGame(myfile);
    }
    myfile << "mid" << ":";
    tileFactory[0]->saveGame(myfile);
    myfile << "#\n";
    myfile << "\n$\n";
    myfile << "type:game\n";
    myfile << "turns:" << turns << "\n";
    myfile << "active:" << active << "\n";
    myfile << "bag:";
    tileBag->saveGame(myfile);
    myfile << "lid:";
    lid->saveGame(myfile);
    myfile << "#";
    myfile.close();
    Menu();
  }
  
  //  SUEDOCODE FOR AI
  //  1)	Check if pile row is empty or contains space. 
  //  2)	If contains space, or is empty 
  //  a.	Spots = pile empty spots.
  //  b.	Color = color of already tiles in row next to that spot
  //  c.	PotentialColours = colours that aren’t already filled in mosaic
  //  d.	numberOfBrokenToBeAdded
  //  e.	Loop through factory i = 0
  //  i.	factCol = colour
  //  ii.	numOfFactCol = number of that color in factory
  //  iii.	if colour matches with potential colours
  //  1.	if numOfFactCol – spots < numberOfBrokenToBeAdded
  //  a.	color = factCol
  //  b.	factoryRow = i
  //  c.	mosaicRow = J


  void playTurnCPU(Player *player)
  {
    std::string factColour;
    std::vector<std::string > potentialColours;
    templateBoard = createMosaicTemplate(5, 5);
    int factoryRow = 0;
    int mosaicRow = 0;
    std::string colourChosen;
    int brokenTileToBeAdded = 20;
    int diff = 0;
    for (int i = 0; i < 5; i++)
    {
      if (player->getBoard()->countSpots(i + 1) > 0)
      {
        potentialColours = player->getBoard()->potentialColours(templateBoard, i);
        for (int z = 0; z < 6; z++)
        {
          if (!tileFactory[z]->isEmpty())
          {
            for (int j = 0; j < potentialColours.size(); j++)
            {
              if (tileFactory[z]->contains(potentialColours[j]))
              {
                int numberOfTileInFactory = tileFactory[z]->countTile(potentialColours[j]);
                int mosaicSpots = player->getBoard()->countSpots(i + 1);
                diff = numberOfTileInFactory - mosaicSpots;
                if (std::abs(diff)<std::abs(brokenTileToBeAdded))
                {
                  if (player->getBoard()->checkForColour(i + 1) != "")
                  {
                    if (player->getBoard()->checkForColour(i + 1) == potentialColours[j])
                    {
                      brokenTileToBeAdded = diff;
                      factoryRow = z;
                      mosaicRow = i + 1;
                      colourChosen = potentialColours[j];
                    }
                  }
                  else
                  {
                    brokenTileToBeAdded = diff;
                    factoryRow = z;
                    mosaicRow = i + 1;
                    colourChosen = potentialColours[j];
                  }
                }
              }
            }
          }
        }
      }
    }
    potentialColours.clear();
    potentialColours.push_back("R");
    potentialColours.push_back("L");
    potentialColours.push_back("Y");
    potentialColours.push_back("B");
    potentialColours.push_back("U");


    if (brokenTileToBeAdded == 20) {
      for (int i = 1; i < 6; i++) {
        if (player->getBoard()->countSpots(i) == 0) {
          for (int z = 0; z < 6; z++) {
            if (!tileFactory[z]->isEmpty()) {
              for (int j = 0; j < 5; j++) {
                if (tileFactory[z]->contains(potentialColours[j])) {
                  int numberOfTileInFactory = tileFactory[z]->countTile(potentialColours[j]);
                  if (numberOfTileInFactory<brokenTileToBeAdded){
                    brokenTileToBeAdded = numberOfTileInFactory;
                    factoryRow = z;
                    mosaicRow = i + 1;
                    colourChosen = potentialColours[j];
                  }
                }
              }
            }
          }
        }
      }
    }
//   deallocate memory
    potentialColours = std::vector<std::string>();
    //     gets tile from factory
    TilePtr tile = tileFactory[factoryRow]->pickTile(colourChosen);

    //counts how many tiles in the factory of that color
    int countTiles = tileFactory[factoryRow]->countTile(colourChosen);

    //checks if the the player has enough spots in the row. if not, moves excess to broken
    if (countTiles > player->getBoard()->countSpots(mosaicRow))
    {
      int diff = countTiles - player->getBoard()->countSpots(mosaicRow);
      for (int i = 0; i < diff; i++)
      {
        if (player->getBoard()->getBrokenSize() < 9)
        {
          player->getBoard()->addToBroken(tile);
        }
        else
        {
          lid->addTile(tile);
        }
      }
    }

    //sets the tile in the board (logic for excess tiles in the mosaic class)
    for (int i = 0; i < countTiles; i++)
    {
      player->getBoard()->setTile(tile, mosaicRow);
    }

    //moves rest of tiles to default factory
    for (int i = 0; i < tileFactory[factoryRow]->size(); i++)
    {

      // only removes rest of tiles to default factory(after one is picked) if the factory picked from is not 0
      if (factoryRow != 0)
      {
        TilePtr restTile = tileFactory[factoryRow]->restOfTiles(colourChosen);
        tileFactory[0]->addTile(restTile);
        if (restTile != nullptr)
        {
          tileFactory[factoryRow]->removeRestTiles(restTile->getColour());
        }
      }
    }
    //removes tile from the factory
    tileFactory[factoryRow]->removeTile(colourChosen);
  }
};