#pragma once

#include "Position.h"
#include "Resources.h"
#include <SDL2/SDL.h>
#include <string>

class Board;

class Building {
protected:
    Position p;
    int sizeX;
    int sizeY;
    std::string texturePath; // Chemin vers l'image (ex: "assets/TownHall.png")
    Resources cost;
    int maxInstances;
    int health;
    SDL_Texture* texture = nullptr; // Texture SDL du bâtiment

public:
    Building(Position position, int sX, int sY, const std::string& path, Resources c, int max, int hp);
    virtual ~Building();

    bool collidesWith(Position position) const;
    bool collidesWith(const Building& other) const;
    virtual void update(const Board& board);
    virtual void render(SDL_Renderer* renderer, int tileSize = 32) const;

    Position getPosition() const { return p; }
    int getSizeX() const { return sizeX; }
    int getSizeY() const { return sizeY; }
    int getHealth() const { return health; }
    void loseHealth(int amount);
    Resources getCost() const { return cost; }
    int getMaxInstances() const { return maxInstances; }

    void setTexture(SDL_Texture* tex) { texture = tex; }
    const std::string& getTexturePath() const { return texturePath; }

protected:
    SDL_Rect getRect(int tileSize = 32) const;
};

