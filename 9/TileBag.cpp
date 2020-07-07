    #include "TileBag.h"

    //intialises tiles
    TileBag::TileBag()
    {
        TilePtr tile;
        for (int i = 0; i != 100; ++i) {
            tile = new Tile();
            tileBag.push_back(tile);
        }
    }
    TileBag::TileBag(std::string seed){
        std::string b;
        for (int i=0; i< seed.size();i++){
            b = seed[i];
            if (seed[i] != 'E'){
            TilePtr tile = new Tile(b);
            tileBag.push_back(tile);
            }
        }
        
    }
    
    //destructor for tilebag, freeing memory
    TileBag::~TileBag()
    {
        tileBag.clear();
        std::vector<TilePtr>().swap(tileBag);
    }
    
    //gets new tile
    TilePtr TileBag::getNewTile()
    {
        TilePtr tile = tileBag.back();
        return tile;
    }
    
    //removes tile form bag
    void TileBag::removeTile()
    {
        tileBag.pop_back();
    }
    int TileBag::size()
    {
        return tileBag.size();
    }
    
    void TileBag::refill(Boxlid* lid){
        while (tileBag.size() <20){
            TilePtr tile = lid->getFront();
            tileBag.push_back(tile);
            lid->removeFront();
        }
        
    }
    void TileBag::saveGame(std::ofstream& myfile){
        for (int i=0; i < tileBag.size();i++){
            if (tileBag[i] != nullptr){
            myfile << tileBag[i]->getColour();
            }
        }
        if (tileBag.size() == 0){
            myfile << "E";
        }
        myfile << "\n";

    }
