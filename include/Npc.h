#ifndef NPC_H
#define NPC_H

#include "Board.h"
#include "Entity.h"
#include "Position.h"

class Npc : public Entity {
protected:
    int health;

public:
    Npc(Position position, int initialHealth = 100, const std::string& texturePath = "assets/Npc.png");
    virtual ~Npc();

    void loseHealth(int amount);
    void moveTowards(const Board& board, Position destination);

    virtual void Update(const Board& board) = 0; // 👈 Abstraction
};

#endif // NPC_H

