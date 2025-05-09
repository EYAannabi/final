#include "../include/TownHall.h"

TownHall::TownHall(Position p)
    : Building(p, 5, 5, "assets/Townhall.png", Resources(0, 0), 1, 1000) {}

TownHall::~TownHall() {}

