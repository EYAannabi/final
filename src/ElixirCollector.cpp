#include "ElixirCollector.h"

ElixirCollector::ElixirCollector(Position p)
    : ResourceGenerator(p,
                        3, 3,
                        "assets/ElixirCollector.png", // Image par défaut
                        Resources(100, 0),            // Coût : 100 or
                        3,
                        150) {}

Resources ElixirCollector::Collect() {
    int collected = current;
    current = 0;
    isFull = false;
    return Resources(0, collected);
}

ElixirCollector::~ElixirCollector() {}

