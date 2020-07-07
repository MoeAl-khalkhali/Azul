
#include "Boxlid.h"

#include <iostream>
#include <fstream>

Boxlid::Boxlid()
{
   boxlid = new LinkedList();
   boxlid->head = nullptr;
}


Boxlid::~Boxlid()
{
   Node *next;
   while (boxlid->head != nullptr)
   {
      next = boxlid->head->next;
      delete boxlid->head;
      boxlid->head = next;
   }
}
//gets size of the Boxlid
int Boxlid::size()
{
   Node* current = boxlid->head;
   int counter = 0;
   while (current != nullptr) {
      current = current->next;
      ++counter;
   }
   return counter;
}

//gets tile at specific point
TilePtr Boxlid::get(int index)
{
   Node* current = boxlid->head;
   int counter = 0;
   TilePtr toReturn = nullptr;

   if (index <= 0 && index < size()) {
      while (counter != index) {

         current = current->next;
         ++counter;
      }
      toReturn = current->value;
   }
   return toReturn;
}

//adds tile to linked list
void Boxlid::addTile(TilePtr tile)
{
   Node* toAdd = new Node();
   toAdd->value = tile;
   toAdd->next = nullptr;

   if (boxlid->head == nullptr) {
      boxlid->head = toAdd;
   } else {
      Node* current = boxlid->head;
      while (current->next != nullptr) {
         current = current->next;
      }
      current->next = toAdd;
   }

}

TilePtr Boxlid::getTileFromBack(){
   Node* current = boxlid->head;
   if (boxlid->head == nullptr){
      return nullptr;
   }
   while (current->next != nullptr) {
      current = current->next;
   }
   return current->value;
   }
   
   void Boxlid::removeFront(){
      Node* current = boxlid->head->next;
      delete boxlid->head;
      boxlid->head = current;
   }
   TilePtr Boxlid::getFront(){
      return boxlid->head->value;
   }
   
   void Boxlid::removeTileFromBack(){
      Node* current = boxlid->head;
      Node* prev = boxlid->head;
      if (boxlid->head == nullptr){
         return;
      }else if (current->next == nullptr){
         delete current;
         current = nullptr;
         return;
      }
      current = current-> next;
      
      while (current->next != nullptr) {
         prev = current->next;
         current = current->next;
      }
      prev->next = nullptr;
      current = nullptr;
      }


void Boxlid::removeTile(int index)
{
}

void Boxlid::clear()
{
}
void Boxlid::addTileLoad(std::string values){
   for (int i = 0; i<values.size();i++){
      TilePtr tile = nullptr;
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
      }
      if (tile != nullptr){
         addTile(tile);
      }
   }   
}
void Boxlid::saveGame(std::ofstream& myfile){
   Node* current = boxlid->head;
   while (current != nullptr){
      myfile << current->value->getColour();
      current = current->next;
   }
   myfile << "E";

   myfile << "\n";

}


int LinkedList::size()
{
   return 1;
}

