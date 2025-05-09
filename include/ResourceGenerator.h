#ifndef RESOURCEGENERATOR_H
#define RESOURCEGENERATOR_H

#include "Building.h"
#include "Board.h"

class ResourceGenerator : public Building {
protected:
    int current;
    int capacity;
    bool isFull;

public:
    ResourceGenerator(Position p, int sX, int sY, const std::string& texturePath, Resources cost, int maxInst, int hp);
    virtual ~ResourceGenerator();

    virtual void update(const Board& board) override;

    bool full() const { return isFull; }
    int getCurrent() const { return current; }
    int getCapacity() const { return capacity; }

    // Optionnel : pour remplacer texture si isFull devient vrai
    virtual void setFullTexture(SDL_Texture* fullTex) { /* optionnel à surcharger */ }
};

#endif // RESOURCEGENERATOR_H

