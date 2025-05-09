#include "Wall.h"

Wall::Wall(Position position)
    : Building(position,
               1, 1,                     // Taille : 1x1
               "assets/Wall.png",        // Chemin vers l’image
               Resources(10, 0),         // Coût : 10 or, 0 élixir
               200,                      // MaxInstances
               200)                      // Santé initiale
{}

Wall::~Wall() {}

