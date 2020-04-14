#include <algorithm>
#include "gameObject.h"

// init static variable
int GameObject::_idCnt = 0;

bool _game_over = false;

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

void GameObject::stop()
{
    _game_over = true;
}

