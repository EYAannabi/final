#include "Position.h"
#include <cstdlib>

Position::~Position() {}

SDL_Point Position::toSDLPoint(int scale) const {
    return SDL_Point{ x * scale, y * scale };
}

SDL_Rect Position::toSDLRect(int width, int height) const {
    return SDL_Rect{ x * width, y * height, width, height };
}

int Position::manhattanDistance(const Position& other) const {
    return std::abs(x - other.x) + std::abs(y - other.y);
}

bool operator==(const Position& p1, const Position& p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

bool operator!=(const Position& p1, const Position& p2) {
    return !(p1 == p2);
}

Position operator+(const Position& p1, const Position& p2) {
    return Position(p1.x + p2.x, p1.y + p2.y);
}

