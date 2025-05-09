#include "Raider.h"
#include <limits>
#include <SDL2/SDL.h>

Raider::Raider(Position position)
    : Enemy(position, 1), lastMoveTime(0), moveDelay(1000)  // <-- ordre corrigé
{
    texturePath = "assets/Raider.png"; // Optionnel selon ton implémentation
}


Raider::~Raider() {}

void Raider::Update(const Board& board) {
    unsigned int currentTime = SDL_GetTicks();
    if (currentTime - lastMoveTime < moveDelay) {
        return; // trop tôt pour se déplacer
    }

    Building* target = GetNearestBuilding(board.getBuildings());
    if (!target) return;

    if (target->collidesWith(getPosition())) {
        AttackBuilding(board);
    } else {
        moveTowards(board, target->getPosition());
    }

    lastMoveTime = currentTime;
}

Building* Raider::GetNearestBuilding(const std::vector<Building*>& buildings) {
    Building* nearest = nullptr;
    int minDistance = std::numeric_limits<int>::max();

    for (Building* building : buildings) {
        int dist = calculateManhattanDistance(getPosition(), building->getPosition());
        if (dist < minDistance) {
            minDistance = dist;
            nearest = building;
        }
    }
    return nearest;
}

int Raider::calculateManhattanDistance(const Position& p1, const Position& p2) const {
    return std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y);
}

