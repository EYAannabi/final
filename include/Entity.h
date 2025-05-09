#ifndef ENTITY_H
#define ENTITY_H

#include "Position.h"
#include <SDL2/SDL.h>
#include <string>

class Board;

class Entity {
protected:
    Position position;
    std::string texturePath;
    SDL_Texture* texture = nullptr;

public:
    Entity(Position pos, const std::string& texturePath);
    virtual ~Entity();

    Position getPosition() const;
    SDL_Texture* getTexture() const { return texture; }
    void setTexture(SDL_Texture* tex) { texture = tex; }
    std::string getTexturePath() const { return texturePath; }

    virtual void moving(const Board& board, int dx, int dy);
    virtual void Update(const Board&) = 0;
    virtual void render(SDL_Renderer* renderer, int tileSize = 32) const;
};

#endif // ENTITY_H

