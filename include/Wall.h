#ifndef WALL_H
#define WALL_H

#include "Building.h"
#include "Resources.h"

class Wall : public Building {
public:
    Wall(Position position);
    virtual ~Wall();
};

#endif // WALL_H

