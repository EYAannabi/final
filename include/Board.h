#pragma once
#ifndef BOARD_H
#define BOARD_H

#include "Position.h"
#include "Building.h"
#include "TownHall.h"
#include "Entity.h"
#include <vector>
#include <SDL2/SDL.h>

class Player;

class Board {
private:
    int SizeX;
    int SizeY;
    std::vector<Building*> buildings;
    std::vector<Entity*> entities;
    TownHall* townHall;
    Player* player;

public:
    Board(int sizeX, int sizeY);
    virtual ~Board();

    bool IsOutOfBounds(Position pos) const;
    int CountBuildingType(const Building& targetBuilding) const;
    bool CollidesWith(const Building& newBuilding) const;
    bool AddBuilding(Building* newBuilding);
    bool isPositionValid(const Position& pos) const;

    void PlaceTownHall();
    void render(SDL_Renderer* renderer, int tileSize = 32) const; // nouvelle méthode SDL

    // Getters
    int getSizeX() const { return SizeX; }
    int getSizeY() const { return SizeY; }
    const std::vector<Building*>& getBuildings() const { return buildings; }
    Player* getPlayer() const { return player; }
    TownHall* getTownHall() const { return townHall; }

    // Setters
    void setPlayer(Player* p) { player = p; }
    void setTownHall(TownHall* th) { townHall = th; }
};

#endif // BOARD_H

