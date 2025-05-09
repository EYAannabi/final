#include "Npc.h"

Npc::Npc(Position position, int initialHealth, const std::string& texturePath)
    : Entity(position, texturePath), health(initialHealth) {}

Npc::~Npc() {}

void Npc::loseHealth(int amount) {
    health = (health - amount > 0) ? health - amount : 0;
}

void Npc::moveTowards(const Board& board, Position destination) {
    Position currentPos = getPosition();
    int dx = 0, dy = 0;

    if (currentPos.x < destination.x) dx = 1;
    else if (currentPos.x > destination.x) dx = -1;

    if (currentPos.y < destination.y) dy = 1;
    else if (currentPos.y > destination.y) dy = -1;

    moving(board, dx, dy);
}


