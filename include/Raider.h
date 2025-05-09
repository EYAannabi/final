#ifndef RAIDER_H
#define RAIDER_H

#include "Enemy.h"
#include "Building.h"
#include "Board.h"
#include <vector>

class Raider : public Enemy {
public:
    Raider(Position position);
    virtual ~Raider();

    void Update(const Board& board) override;

private:
    Building* GetNearestBuilding(const std::vector<Building*>& buildings);
    int calculateManhattanDistance(const Position& p1, const Position& p2) const;

    unsigned int lastMoveTime;     // Déclaré en 1er
    unsigned int moveDelay;        // Déclaré en 2e
};

#endif // RAIDER_H

