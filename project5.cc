/* This is also the most beautiful header comment you will ever encounter in all
 * your experience in the workplace
 *
 * project5.cc
 * Benjamin Hills & Bradley Etienne
 */

#include "project5.h"

Province::Province(istream & input)
{
   int numTowns = 0;
   int numRoads = 0;

   input >> numTowns >> numRoads;

   // _towns->resize(numTowns);
   // _roads->resize(numRoads);
   for (int i = 0; i < numTowns; i++)
   {
     string name = "";
     input >> name;
     if (i == 0)
     {
       addTown(name, true);
       setCapital(getTown(name));
     }
     else
     {
       addTown(name, false);
     }
   }
   for (int j = 0; j < numRoads; j++)
   {
     string firstTown = "";
     string secondTown = "";
     char bridge;
     float distance = 0.0;
     input >> firstTown >> secondTown >> bridge >> distance;
     addRoad(getTown(firstTown), getTown(secondTown), bridge, distance);
   }
}

Province::~Province()
{ }

void Province::print1()
{
  cout << "The input data is: " << endl;
  for (int i = 0; i < _towns.size(); i++)
  {
    if (i == 0)
    {
      cout << "\t" << getCapital()->_name << endl;
      // for()
    }
    else
    {

    }
  }

}

Town * Province::getCapital()
{
  return _capital;
}

void Province::addTown(string name, bool capital)
{
  Town * town = new Town(name, capital);
  _towns.push_back(town);
}

void Province::setCapital(Town * capital)
{
  _capital = capital;
}

Town * Province::getTown(string name)
{
  // Town * town;
  for(vector<Town *>::iterator it = _towns.begin(); it != _towns.end(); ++it)
  {
    Town * town = *it;
    if(town->getName() == name)
    {
      return *it;
    }
  }
}

void Province::addRoad(Town * firstTown, Town * secondTown, char bridge, float distance)
{
  Road * road = new Road(firstTown, secondTown, bridge, distance);
  _roads.push_back(road);
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


Road::Road(Town * firstTown, Town * secondTown, char bridge, float distance)
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
  if (_bridge == 'B')
  {
    return true;
  }
  else
  {
    return false;
  }
}

Town * Road::getTown(int index)
{
  return _adjTowns[index];
}

/* Check the remainder of the file for non-whitespace.
 * Return true if there is whitespace.
 * Return false if non-whitespace is found.
 * Once non-whitespace is found, put non-whitespace character back and return false.
 */
bool eof(istream & input)
{
  while(true)
  {
    char c;
    cin >> c;
    if(cin.eof() || c == '\n' || c == ' ')
    {
      return true;
    }
    else
    {
      cin.unget();
      return false;
    }
  }
}

int main()
{
  while (!eof(cin))
  {
    Province province(cin);
    province.print1();
  }
}
