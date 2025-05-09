#include "Entity.h"
#include "../include/Board.h"

Entity::Entity(Position pos, const std::string& path)
    : position(pos), texturePath(path) {}

Entity::~Entity() {}

Position Entity::getPosition() const {
    return position;
}

void Entity::moving(const Board& board, int dx, int dy) {
    Position newPos = position + Position(dx, dy);
    if (board.isPositionValid(newPos)) {
        position = newPos;
    }
}

void Entity::render(SDL_Renderer* renderer, int tileSize) const {
    if (texture) {
        SDL_Rect dst = {
            position.x * tileSize,
            position.y * tileSize,
            tileSize,
            tileSize
        };
        SDL_RenderCopy(renderer, texture, nullptr, &dst);
    } else {
        SDL_Rect dst = {
            position.x * tileSize,
            position.y * tileSize,
            tileSize,
            tileSize
        };
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // Magenta par défaut
        SDL_RenderFillRect(renderer, &dst);
    }
}

