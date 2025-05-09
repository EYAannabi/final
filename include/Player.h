#ifndef PLAYER_H
#define PLAYER_H

#include "Resources.h"
#include "Board.h"
#include "Entity.h"
#include "Building.h"

class Player : public Entity {
private:
    Resources resources;
    bool isBuildingMode = false;

public:
    Player(Position position);
    virtual ~Player();

    void ToggleBuildMode() { isBuildingMode = !isBuildingMode; }
    bool IsBuilding() const { return isBuildingMode; }

    Building* Interact(Board& board);
    void moving(const Board& board, int dx, int dy) override;

    Resources& getResources();
    void Update(const Board&) override;
};

#endif // PLAYER_H

