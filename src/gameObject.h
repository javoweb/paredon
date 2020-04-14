#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <thread>
#include <mutex>

enum ObjectType
{
    noObject,
    objectBall,
    objectWall,
    objectPlayer,
};

class GameObject
{
public:

    enum class Direction { kLeft, kRight, kUp, kDown };
    // constructor / destructor
    GameObject(int grid_width, int grid_height);
    ~GameObject();

    // getter and setter
    int getID() { return _id; }
    ObjectType getType() { return _type; }
    bool running();
    // typical behaviour methods
    virtual void play(){};
    void stop();

protected:

    ObjectType _type;                 // identifies the class type
    int _id;                          // every game object has its own unique id
    std::vector<std::thread> threads; // holds all threads that have been launched within this object
    std::mutex _mtx;                  // mutex for prevent data race 
    int _grid_width;                  // size of grid
    int _grid_height;                 // size of grid
    static bool _game_over;           // flag for end running processes
    
private:
    static int _idCnt; // global variable for counting object ids
};

#endif