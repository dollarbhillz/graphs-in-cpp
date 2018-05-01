/* This is also the most beautiful header comment you will ever encounter in all
 * your experience in the workplace
 *
 * project5.cc
 * Benjamin Hills & Bradley Etienne
 */


#include <stack>
#include "project5.h"

Province::Province(istream & input)
{
   int numTowns = 0;
   int numRoads = 0;

   input >> numTowns >> numRoads;

   for (int i = 0; i < numTowns; i++)
   {
     string name = "";
     input >> name;
     if (i == 0)
     {
       addTown(name, true);
       setCapital(getTown(name));
       getTown(name)->setIndex(0);
     }
     else
     {
       addTown(name, false);
       getTown(name)->setIndex(i);
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

// Destructor to be implemented
Province::~Province()
{ }

void Province::print1()
{
  bool * scheduled = new bool[_towns.size()];
  for (int n = 0; n < _towns.size(); n++)
  {
    scheduled[n] = false;
  }

  queue<Town *> toVisit;

  toVisit.push(getCapital());

  scheduled[0] = true;

  cout << "The input data is: " << endl;

  while(!toVisit.empty())
  {
    Town * current = toVisit.front();
    toVisit.pop();
    cout << "\t" << current->getName() << endl;

    vector<Town *> adj;
    for (int j = 0; j < current->getAdjRoads().size(); j++)
    {
      adj.push_back(current->getRoad(j)->getAltTown(current->getName()));
      string bridge = "";
      if (current->getRoad(j)->isBridge())
      {
        bridge = "via bridge";
      }
      cout << "\t\t" << current->getRoad(j)->getAltTown(current->getName())->getName() << " "
             << current->getRoad(j)->getDistance() << " mi "
               << bridge << endl;
    }

    // Inspired by Graph Algorithms handout
    for (vector<Town *>::iterator iter = adj.begin();
          iter != adj.end(); iter++)
    {
      Town * adjacent = *iter;
      int head = adjacent->getIndex();
      if (!scheduled[head])
      {
        toVisit.push(*iter);
        scheduled[head] = true;
      }
    }
  }
}

void Province::print2()
{
  // List of distances from capital, indices are parallel to _towns list
  vector<float> dist;
  vector<Town *> path;
  Town * curTown = getCapital();
  Town * prevTown;
  // stack<Town *> visited;
  priority_queue<MinHeapItem> toVisit;
  // First distance in list is capital, so 0
  dist.push_back(0);
  // Add all the towns except the capital to the toVisit priority_queue
  // // and set the distance in the dist vector to inf initially
  for(int i = 1; i < _towns.size(); i++)
  {
    // curTown = _towns[i];
    // vector<Road *> curAdjRoads = curTown->getAdjRoads();
    // vector<Town *> curAdjTowns;
    // for(int j = 0; j < curAdjRoads.size(); j++)
    // {
    //   Road * temp = curAdjRoads[j];
    //   curAdjTowns.push_back(temp->getAltTown(curTown->getName()));
    // }
    // for(int k = 0; k < curAdjTowns.size(); k++)
    // {
    //   if(curAdjTowns[k]->isCapital())
    //   {
    //     dist.push_back(curAdjRoads[k]->getDistance()); // Has direct path to capital
    //     toVisit.push({ curAdjRoads[k]->getDistance(), curAdjTowns[k]->getName() });
    //     // visited.push(_towns[i]);
    //   }
    //   else
    //   {
    //     dist.push_back(FLT_MAX); // No direct path to capital
    //     toVisit.push({ FLT_MAX, curAdjTowns[k]->getName() });
    //   }
    // }
    dist.push_back(FLT_MAX);
  }
  // Declare and initialize the list of adjacent roads and towns to the capital
  vector<Road *> capAdjRoads = curTown->getAdjRoads();
  vector<Town *> capAdjTowns;
  for(int j = 0; j < capAdjRoads.size(); j++)
  {
    capAdjTowns.push_back(capAdjRoads[j]->getAltTown(getCapital()->getName()));
  }
  // Update dist with distance to adjacent towns and push them to toVisit
  for(int k = 0; k < capAdjTowns.size(); k++)
  {
    dist[capAdjTowns[k]->getIndex()] = capAdjRoads[k]->getDistance();
    toVisit.push({ capAdjRoads[k]->getDistance(), capAdjTowns[k]->getName() });
  }

for(int i = 0; i < _towns.size(); i++)
{
  if(dist[i] == FLT_MAX)
  {
    toVisit.push({ FLT_MAX, _towns[i]->getName() });
  }
}


  // Traverse the towns not yet visited, starting with the closest ones
  while (!toVisit.empty())
  {
    curTown = getTown(toVisit.top()._name);
    toVisit.pop();


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
  firstTown->addRoad(road);
  secondTown->addRoad(road);
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

vector<Road *> Town::getAdjRoads()
{
  return _adjRoads;
}

Road * Town::getRoad(int index)
{
  return _adjRoads[index];
}

string Town::getName()
{
  return _name;
}

bool Town::isCapital()
{
  return _capital;
}

int Town::getIndex()
{
  return _index;
}

void Town::setIndex(int index)
{
  _index = index;
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

Town * Road::getAltTown(string name)
{
  for(vector<Town *>::iterator it = _adjTowns.begin(); it != _adjTowns.end(); ++it)
  {
    Town * town = *it;
    if(town->getName() != name)
    {
      return *it;
    }
  }
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
