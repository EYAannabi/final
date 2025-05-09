#ifndef TOWNHALL_H
#define TOWNHALL_H

#include "Building.h"
#include "Resources.h"

class TownHall : public Building {
public:
    TownHall(Position p);
    virtual ~TownHall();

    // Redondant avec Building::getPosition(), mais si vous le redéclarez :
    //Position getPosition() override;
};

#endif // TOWNHALL_H

