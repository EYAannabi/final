#include "Board.h"
#include "Position.h"
#include "Player.h"
#include "TownHall.h"
#include <algorithm>
#include <typeinfo> // nécessaire pour typeid
#include <iostream>

Board::Board(int sizeX, int sizeY)
    : SizeX(sizeX), SizeY(sizeY), townHall(nullptr), player(nullptr) {}

Board::~Board() {
    for (auto& b : buildings) delete b;
    for (auto& e : entities) delete e;
}

bool Board::IsOutOfBounds(Position pos) const {
    return pos.x < 0 || pos.x >= SizeX || pos.y < 0 || pos.y >= SizeY;
}

int Board::CountBuildingType(const Building& targetBuilding) const {
    int count = 0;
    for (const Building* b : buildings) {
        if (typeid(*b) == typeid(targetBuilding)) {
            count++;
        }
    }
    return count;
}

bool Board::CollidesWith(const Building& newBuilding) const {
    int newLeft = newBuilding.getPosition().x - newBuilding.getSizeX() / 2;
    int newRight = newBuilding.getPosition().x + newBuilding.getSizeX() / 2;
    int newTop = newBuilding.getPosition().y - newBuilding.getSizeY() / 2;
    int newBottom = newBuilding.getPosition().y + newBuilding.getSizeY() / 2;

    for (const Building* b : buildings) {
        int bLeft = b->getPosition().x - b->getSizeX() / 2;
        int bRight = b->getPosition().x + b->getSizeX() / 2;
        int bTop = b->getPosition().y - b->getSizeY() / 2;
        int bBottom = b->getPosition().y + b->getSizeY() / 2;

        if (!(newRight < bLeft || newLeft > bRight ||
              newBottom < bTop || newTop > bBottom)) {
            return true;
        }
    }
    return false;
}

bool Board::AddBuilding(Building* newBuilding) {
    if (IsOutOfBounds(newBuilding->getPosition())) return false;
    if (CollidesWith(*newBuilding)) return false;
    if (player && !player->getResources().canAfford(newBuilding->getCost())) return false;

    if (newBuilding->getMaxInstances() <= CountBuildingType(*newBuilding)) {
        delete newBuilding;
        return false;
    }

    if (player) {
        player->getResources().consume(newBuilding->getCost());
    }

    buildings.push_back(newBuilding);

    if (auto* th = dynamic_cast<TownHall*>(newBuilding)) {
        townHall = th;
    }

    return true;
}

bool Board::isPositionValid(const Position& pos) const {
    bool inBounds = (pos.x >= 0 && pos.x < SizeX &&
                     pos.y >= 0 && pos.y < SizeY);

    for (const Building* b : buildings) {
        if (b->collidesWith(pos)) {
            return false;
        }
    }

    return inBounds;
}

// ⛔️ Fonction console : désactivée pour SDL
/*
void Board::Draw() const {
    std::cout << "+";
    for (int x = 0; x < SizeX; x++) std::cout << "--";
    std::cout << "+\n";

    for (int y = 0; y < SizeY; y++) {
        std::cout << "|";
        for (int x = 0; x < SizeX; x++) {
            bool hasBuilding = false;
            for (const auto& b : buildings) {
                if (b->collidesWith({x, y})) {
                    std::wcout << b->getRepr() << " ";
                    hasBuilding = true;
                    break;
                }
            }
            if (!hasBuilding) std::cout << "  ";
        }
        std::cout << "|\n";
    }

    std::cout << "+";
    for (int x = 0; x < SizeX; x++) std::cout << "--";
    std::cout << "+\n";
}
*/

void Board::render(SDL_Renderer* renderer, int tileSize) const {
    for (const Building* b : buildings) {
        if (b) b->render(renderer, tileSize);
    }

    // Dessin de la grille (optionnel)
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // gris clair
    for (int i = 0; i <= SizeX; ++i) {
        SDL_RenderDrawLine(renderer, i * tileSize, 0, i * tileSize, SizeY * tileSize);
    }
    for (int j = 0; j <= SizeY; ++j) {
        SDL_RenderDrawLine(renderer, 0, j * tileSize, SizeX * tileSize, j * tileSize);
    }
}

