// Include.h

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>

using namespace std;

// Seeding logic to control randomness (used in removeRandom340)
class RandomSeeder {
public:
    RandomSeeder() {
        srand(1); // <- Change to 2 for Asmt04_Run2.txt
    }
};

static RandomSeeder _random_seeder;

// Include template headers and their implementations
#include "LinkedBag.h"
#include "LinkedBag.cpp"
#include "LinkedBag340.cpp"
