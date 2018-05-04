/* This the most beautiful implementation comment you will ever encounter in all
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


Province::~Province()
{
   vector<Town*>::iterator i;
   for (i = _towns.begin(); i != _towns.end(); i++)
   {
     delete *i;
   }

   vector<Road*>::iterator j;
   for (j = _roads.begin(); j != _roads.end(); j++)
   {
     delete *j;
   }
}

/* Implementation of requirement 1 */
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

/* Implementation of requirement 2 */
void Province::print2()
{

  cout << "The shortest routes from " << getCapital()->getName() << " are:" << endl;
  map<Town*, float> dist;
  set<Town*> townSet;
  map<Town*, Town*> prevTown;

  vector<Town*> path = getTowns();
  vector<Town*>::iterator i = path.begin();

  dist[*i] = 0;
  i++;


  for( ; i != path.end(); i++)
  {
    dist[*i] = FLT_MAX;
  }

  for (i = path.begin(); i != path.end(); i++)
  {
    prevTown[*i] = 0;
  }

  while (townSet.size() != path.size())
  {
    map<Town*, float>::iterator j = dist.begin();
    float minDist = FLT_MAX;
    Town* k;

    for (j = dist.begin(); j != dist.end(); j++)
      if (townSet.count(j->first) == 0 && j->second < minDist)
      {
        k = j->first;
        minDist = j->second;
      }

    townSet.insert(k);

    vector<Road*> adjacentRoads = k->getAdjRoads();
    vector<Road*>::iterator m;

      for (m = adjacentRoads.begin(); m != adjacentRoads.end(); m++)
        if (townSet.count((*m)-> getAltTown(k->getName())) == 0)
        {
          Road* n = *m;
          Town* o = n->getAltTown(k->getName());
          if (dist[k] + n->getDistance() < dist[o])
          {
            dist[o] = dist[k] + n->getDistance();
            prevTown[o] = k;
          }
        }
   }

   i = ++path.begin();
   for (; i != path.end(); i++)
   {
     Town* curTown = *i;
     cout << "\t" << "The shortest route from " << path.front()->getName()
             << " to " << curTown->getName() << " is "
             << dist[curTown] << " mi:" << endl << endl;

     stack<Town*> towns;
     Town* temp = curTown;

     while (temp != 0)
     {
       towns.push(temp);
       temp = prevTown[temp];
     }

     while (!towns.empty())
     {
       cout << "\t\t" << towns.top()->getName() << endl;
       towns.pop();
     }

     cout << endl;
   }
 }


 // Helper function for print3()
 template <typename Town>
 void unionFind(map<Town, Town>& mainMap, Town a, Town b)
 {
   Town aRoot = a;
   Town bRoot = b;

   while (aRoot != mainMap[aRoot])
   {
     aRoot = mainMap[aRoot];
   }

   while (bRoot != mainMap[bRoot])
   {
     bRoot = mainMap[bRoot];
   }

   if (aRoot != bRoot)
   {
     mainMap[bRoot] = aRoot;
   }
 }

 void Province::print3()
 {
   // need to construct a proper priority queue     priority_queue<   > toVisit;
   map<Town*, Town*> map;
   vector<Road*> tree;

   vector<Town*> towns = getTowns();
   vector<Town*>::iterator i;

   for (i = towns.begin(); i != towns.end(); i++)
   {
     map[*i] = *i;
   }

   vector<Road*> roads = getRoads();
   vector<Road*>::iterator j;

   for (j = roads.begin(); j != roads.end(); j++)
   {
     // toVisit.push(*j);
   }

   while (tree.size() < towns.size()-1)
   {
     // Road* road = toVisit.top();
     // toVisit.pop()

     /* Stuck */
   }
 }

 vector<Town*> Province::BreadthFirstSearch(Town* start, bool bridges)
 {
   set<Town*> foundTowns;
   queue<Town*> BFSq;
   vector<Town*> BFSv;

   foundTowns.insert(start);
   BFSq.push(start);

   while (!BFSq.empty())
   {
     Town* curTown = BFSq.front();
     BFSq.pop();

     BFSv.push_back(curTown);

     vector<Road*> roads = curTown->getAdjRoads();
     vector<Road*>::iterator i;

     for (i = roads.begin(); i != roads.end(); i++)
     {
       Road* road = *i;

       if (!(bridges && road->isBridge()))
       {
         Town* altTown = road->getAltTown(curTown->getName());

         if (foundTowns.count(altTown) == 0)
         {
           BFSq.push(altTown);
           foundTowns.insert(altTown);
         }
       }
     }
   }
   return BFSv;
 }


 void Province::print4()
 {
   set<Town*> done;
   vector<Town*> towns = getTowns();

   while (done.size() != towns.size())
   {
     vector<Town*>::iterator i;
     Town* curTown = NULL;

     for (i = towns.begin(); i != towns.end(); i++)
     {
       if (done.count(*i) == 0)
       {
         curTown = *i;
       }

     if (curTown != NULL)
     {
       vector<Town*> BFSv = BreadthFirstSearch(curTown, true);

       cout << "\t" << "If all bridges fail, the following towns would form"
                       " an isolated group:" << endl << endl;

       for (i = BFSv.begin(); i != BFSv.end(); i++)
       {
         cout << "\t\t" << (*i)->getName() << endl;
         done.insert(*i);
       }
       cout << endl;
     }
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

vector<Town*> Province::getTowns()
{
  return _towns;
}

vector<Road*> Province::getRoads()
{
  return _roads;
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
    cout << endl << endl;
    province.print2();
    cout << endl << endl;
    province.print4();
  }
}
