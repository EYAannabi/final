#include "Enemy.h"
#include "Building.h"
#include "TownHall.h"

Enemy::Enemy(Position position, int attackDamage)
    : Npc(position, 100, "assets/Enemy.png"), Targeted(false), AttackDamage(attackDamage) {}

Enemy::~Enemy() {}

void Enemy::AttackBuilding(const Board& board) {
    for (Building* building : board.getBuildings()) {
        if (building->collidesWith(getPosition())) {
            building->loseHealth(AttackDamage);
        }
    }
}

void Enemy::Update(const Board& board) {
    TownHall* th = board.getTownHall();
    if (th) {
        moveTowards(board, th->getPosition());
        AttackBuilding(board);
    }
}

