#include "../include/Building.h"
#include <iostream>

Building::Building(Position position, int sX, int sY, const std::string& path, Resources c, int max, int hp)
    : p(position), sizeX(sX), sizeY(sY), texturePath(path), cost(c), maxInstances(max), health(hp) {}

Building::~Building() {}

bool Building::collidesWith(Position position) const {
    int left = p.x - sizeX / 2;
    int right = p.x + sizeX / 2;
    int top = p.y - sizeY / 2;
    int bottom = p.y + sizeY / 2;

    return (position.x >= left && position.x <= right &&
            position.y >= top && position.y <= bottom);
}

bool Building::collidesWith(const Building& other) const {
    int thisLeft = p.x - sizeX / 2;
    int thisRight = p.x + sizeX / 2;
    int thisTop = p.y - sizeY / 2;
    int thisBottom = p.y + sizeY / 2;

    int otherLeft = other.p.x - other.sizeX / 2;
    int otherRight = other.p.x + other.sizeX / 2;
    int otherTop = other.p.y - other.sizeY / 2;
    int otherBottom = other.p.y + other.sizeY / 2;

    return !(thisRight < otherLeft ||
             thisLeft > otherRight ||
             thisBottom < otherTop ||
             thisTop > otherBottom);
}

void Building::update(const Board&) {
    // Comportement par défaut (ne fait rien)
}

void Building::loseHealth(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

SDL_Rect Building::getRect(int tileSize) const {
    return SDL_Rect {
        p.x * tileSize,
        p.y * tileSize,
        sizeX * tileSize,
        sizeY * tileSize
    };
}

void Building::render(SDL_Renderer* renderer, int tileSize) const {
    SDL_Rect dst = getRect(tileSize);

    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &dst);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // rouge si pas de texture
        SDL_RenderFillRect(renderer, &dst);
    }
}

