#ifndef POSITION_H
#define POSITION_H

#include <SDL2/SDL.h>

class Position {
public:
    int x;
    int y;

     Position(int x = 0, int y = 0) : x(x), y(y) {}
    virtual ~Position();

    SDL_Point toSDLPoint(int scale = 32) const;
    SDL_Rect toSDLRect(int width = 32, int height = 32) const;

    int manhattanDistance(const Position& other) const;

    friend bool operator==(const Position& p1, const Position& p2);
    friend bool operator!=(const Position& p1, const Position& p2);
    friend Position operator+(const Position& p1, const Position& p2);
};

#endif // POSITION_H

