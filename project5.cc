/* This is also the most beautiful header comment you will ever encounter in all
 * your experience in the workplace
 *
 * project5.cc
 * Benjamin Hills & Bradley Etienne
 */

 #include "project5.h"

 Province::Province(Town * capital)
 {
   _capital = capital;
 }

 Province::~Province()
 { }

 void Province::input(istream & input)
 {

 }

 void Province::print()
 {
   cout << "The input data is: " << endl;

   
 }

 Town * Province::getCapital()
 {
   return _capital;
 }

 void Province::addTown(string name, bool capital)
 {

 }

 void Province::addRoad(Town * firstTown, Town * secondTown, float distance, bool bridge)
 {

 }









 Town::Town(string name, bool capital)
 {
   _name = name;
   _capital = capital;
 }

 void Town::addRoad(Road * road)
 {
   _adjRoads.push_back(road);
 }

 string Town::getName()
 {
   return _name;
 }


 bool Town::isCapital()
 {
   return _capital;
 }










 Road::Road(Town * firstTown, Town * secondTown, float distance, bool bridge)
 {
   _distance = distance;
   _bridge = bridge;
   _adjTowns.push_back(firstTown);
   _adjTowns.push_back(secondTown);
 }

 float Road::getDistance()
 {
   return _distance;
 }

 bool Road::isBridge()
 {
   return _bridge;
 }
