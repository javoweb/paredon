#include <algorithm>
#include "gameObject.h"

// init static variable
int GameObject::_idCnt = 0;

bool GameObject::_game_over = false;

GameObject::GameObject(int grid_width, int grid_height) : _grid_width(grid_width), _grid_height(grid_height)
{
    _type = ObjectType::noObject;
    _id = _idCnt++;
}

GameObject::~GameObject()
{
    // set up thread barrier before this object is destroyed
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });
}

bool GameObject::running()
{
    return !_game_over;
}

void GameObject::stop()
{
    _game_over = true;
}

GameObject::GameObject(GameObject &other)
{
    _type = ObjectType::noObject;
    _id = _idCnt++;
    threads = other.threads;
    _grid_height = other._grid_height;
    _grid_width = other._grid_width;
}

GameObject::GameObject(GameObject &&other){
    _type = ObjectType::noObject;
    _id = _idCnt++;
    threads = std::move(other.threads);
    _grid_height = other._grid_height;
    _grid_width = other._grid_width;
}

GameObject& GameObject::operator=(GameObject &other){
    if (this == &other){
        return other;
    }
    threads = other.threads;
    _grid_height = other._grid_height;
    _grid_width = other._grid_width;
    return *this;
}

GameObject& GameObject::operator=(GameObject &&other){
    if (this == &other){
        return other;
    }
    threads = std::move(other.threads);
    _grid_height = other._grid_height;
    _grid_width = other._grid_width;
    return *this;
}