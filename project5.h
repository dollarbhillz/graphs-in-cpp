/* This is the most beautiful header file you will ever see in your entire life.
 *
 * project5.h
 * Benjamin Hills & Bradley Etienne
 */


#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

class Town;
class Road;

class Province
{
  public:
    /* Constructor
     * RT Say what it does.  Describe the input stream and give a simple
     * RT example.
     */
    Province(istream & input);

    // Destructor
    ~Province();

    //RT Good, but need a comment
    Province(const Province &) = delete;
    const Province
      & operator = (const Province &) = delete;

    /* Read and store the input from istream
     * Parameter:
     * * input - the input stream from istream
    */
    //RT Wait, doesn't the constructor do this?  If this is a helper,
    //RT make it private.
    void input(istream & input);

    /* Print the output with appropriate formatting for req 1 */
    //RT Even though I know what this is, you should give it a good
    //RT descriptive comment.  It's good practice.
    //RT (I mean, I have code to do the printing, too, but that practice
    //RT is also good for your learning.)
    void print1();

    /* Accessor for the capital of the province */
    Town * getCapital();

    //RT The mutators should only be called by the constructor,
    //RT so they should be private.

    //RT Good methods!

    /* Mutator for setting the capital of the province
     * Parameter:
     * * capital - the town that is the capital of this province
    */
    void setCapital(Town * capital);

    /* Add a town to the province
     * Parameters:
     * * name - name of Town to add
     * * capital - bool if the town is the capital of the province
    */
    void addTown(string name, bool capital);

    /* Find a town in the province
     * Parameter:
     * * name - the name of the town
    */
    Town * getTown(string name);

    /* Add a road to the province
     * Parameters:
     * * firstTown - the first town the road connects to
     * * secondTown - the second town the road connects to
     * * distance - the distance / weight of the road
     * * bridge - bool if the road is a bridge
    */
    void addRoad(Town * firstTown, Town * secondTown, char bridge, float distance);

  private:
    /* Vectors to store all the towns and roads */
    vector<Town *> _towns;
    vector<Road *> _roads;

    /* The capital of the province */
    Town * _capital;

    /* Name of the Province */
    string _name;
};

class Town
{
  public:
    /* Constructor
     *
     * Parameters:
     * * name - name of the town
     * * capital - bool if this town is the capital
    */
    Town(string name, bool capital);

    /* Add a road connecting to this town
     * Parameters:
     * * road - the pointer to the adjacent road
    */
    void addRoad(Road * road);

    /* Get the vector of adjacent roads */
    vector<Road *> getAdjRoads();

    /* Get the road at a certain index in the adjacent roads vector */
    Road * getRoad(int index);

    /* Accessor for the name of the town */
    string getName();

    /* Check whether this is the capital */
    bool isCapital();

    //RT What is the index for?  Does it really make sense to change the index?
    /* Get index of town */
    int getIndex();

    /* Set index of town */
    void setIndex(int index);

  private:
    /* Is this a capital */
    bool _capital;

    /* Name of the town */
    string _name;

    /* Index of town */
    int _index;
    /* Vector of roads connected to this town */
    vector<Road *> _adjRoads;
};

class Road
{
  public:
    /* Constructor
     *
     * Parameters:
     * * firstTown - the first town this road is connected to
     * * secondTown - the second town this road is connected to
     * * distance - the distance / weight of this road
     * * bridge - bool if this road is a bridge
    */
    Road(Town * firstTown, Town * secondTown, char bridge, float distance);

    /* Access the distance of this road */
    float getDistance();

    /* Check if this road is a bridge */
    bool isBridge();

    /* Get either of the adjacent towns, first town is index 1
       //RT Not index 0 and 1?
     * Parameter:
     * * index - index of town
    */
    Town * getTown(int index);

    /* When getting the town to print for this road, get the alternate town
     * * with a different name than the current town being referenced
     * * Parameter:
     * * * name - the name of the town currently being referenced
    */
    Town * getAltTown(string name);

  private:
    /* Private instance variables */
    char _bridge;
    float _distance;
    vector<Town *> _adjTowns;

};
