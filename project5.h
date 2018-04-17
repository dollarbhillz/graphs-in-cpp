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
     *
     */
    Province();

    // Destructor
    ~Province();

    Province(const Province &) = delete;
    const Province
      & operator = (const Province &) = delete;

    /* Read and store the input from istream
     * Parameter:
     * * input - the input stream from istream
    */
    void input(istream & input);

    /* Print the output with appropriate formatting */
    void print();

    /* Accessor for the capital of the province */
    Town * getCapital();

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

    /* Add a road to the province
     * Parameters:
     * * firstTown - the first town the road connects to
     * * secondTown - the second town the road connects to
     * * distance - the distance / weight of the road
     * * bridge - bool if the road is a bridge
    */
    void addRoad(Town * firstTown, Town * secondTown, float distance, bool bridge);

  private:
    /* Vectors to store all the towns and roads */
    vector<Town *> _towns [];
    vector<Road *> _roads [];

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

    /* Accessor for the name of the town */
    string getName();

    /* Set whether or not this is the capital of the province */
    void setCapital();

    /* Check whether this is the capital */
    bool isCapital();

  private:
    /* Vector of roads connected to this town */
    vector<Road *> _adjRoads [];

    /* Is this a capital */
    bool _capital;

    /* Name of the town */
    string _name;
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
    Road(Town * firstTown, Town * secondTown, float distance, bool bridge);

    /* Access the distance of this road */
    float getDistance();

    /* Set the bridge boolean if this road is a bridge */
    void makeBridge();

    /* Check if this road is a bridge */
    bool isBridge();

    /* Add an adjacent town to this road
     * Parameters:
     * * town - The pointer to the Town to add
     * * name - the name of the Town to add
     * * index - where to add it in the adjacent Town vector (either 0 or 1)
    */
    void addTown(Town * town, string name, int index);
  private:
    /* Private instance variables */
    bool _bridge;
    float _distance;
    vector<Town *> adjTowns [];

};
