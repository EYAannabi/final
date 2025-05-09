#include "GoldMine.h"

GoldMine::GoldMine(Position p)
    : ResourceGenerator(p,
                        3, 3,
                        "assets/GoldMine.png",  // Texture par défaut (non pleine)
                        Resources(0, 100),      // Coût : 100 élixir
                        3,                      // MaxInstances
                        150) {}                 // Santé

Resources GoldMine::Collect() {
    int collected = current;
    current = 0;
    isFull = false;
    return Resources(collected, 0);
}

GoldMine::~GoldMine() {}

