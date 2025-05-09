#ifndef ENEMY_H
#define ENEMY_H

#include "Board.h"
#include "Npc.h"

class Enemy : public Npc {
private:
    bool Targeted;
    int AttackDamage;

public:
    Enemy(Position position, int attackDamage = 10);
    virtual ~Enemy();

    void AttackBuilding(const Board& board);
    void Update(const Board& board) override;
};

#endif // ENEMY_H

