#include "ResourceGenerator.h"

ResourceGenerator::ResourceGenerator(Position p, int sX, int sY,
                                     const std::string& texturePath,
                                     Resources cost, int maxInst, int hp)
    : Building(p, sX, sY, texturePath, cost, maxInst, hp),
      current(0), capacity(100), isFull(false) {}

ResourceGenerator::~ResourceGenerator() {}

void ResourceGenerator::update(const Board& /* board */) {
    if (!isFull) {
        current++;
        if (current >= capacity) {
            current = capacity;
            isFull = true;

            // Tu peux ici déclencher un changement de texture, exemple :
            // if (fullTexture) setTexture(fullTexture);
        }
    }
}

