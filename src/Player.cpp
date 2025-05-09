#include "Player.h"
#include "GoldMine.h"
#include "ElixirCollector.h"
#include "Wall.h"
#include <iostream>

Player::Player(Position position)
    : Entity(position, "assets/Player.png"), resources(400, 400) {}

Player::~Player() {}

Building* Player::Interact(Board& board) {
    for (Building* b : board.getBuildings()) {
        if (b->collidesWith(position)) {
            if (auto* mine = dynamic_cast<GoldMine*>(b)) {
                resources.addGold(mine->Collect().getGold());
            } else if (auto* collector = dynamic_cast<ElixirCollector*>(b)) {
                resources.addElixir(collector->Collect().getElixir());
            }
        }
    }

    if (resources.getGold() >= 10) {
        Wall* newWall = new Wall(position);
        if (board.AddBuilding(newWall)) {
            resources.spendGold(10);
            return newWall;
        }
        delete newWall;
    }

    return nullptr;
}

void Player::Update(const Board& board) {
    for (Building* building : board.getBuildings()) {
        if (building->collidesWith(position)) {
            if (auto* mine = dynamic_cast<GoldMine*>(building)) {
                resources.addGold(mine->Collect().getGold());
            } else if (auto* collector = dynamic_cast<ElixirCollector*>(building)) {
                resources.addElixir(collector->Collect().getElixir());
            }
        }
    }

    if (board.getTownHall() && board.getTownHall()->getHealth() <= 0) {
        std::cout << "Game Over : Town Hall destroyed!\n";
    }
}

Resources& Player::getResources() {
    return resources;
}

void Player::moving(const Board& board, int dx, int dy) {
    Position newPos = position + Position(dx, dy);

    if (newPos.x <= 0 || newPos.y <= 0 ||
    newPos.x >= board.getSizeX() - 1 ||
    newPos.y >= board.getSizeY() - 1) {
    return;
}


    for (Building* b : board.getBuildings()) {
        if (b->collidesWith(newPos) && !b->collidesWith(position)) {
            return;
        }
    }

    position = newPos;
}

