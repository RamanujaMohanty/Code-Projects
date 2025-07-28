//	Include.h

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>

using namespace std;

class RandomSeeder
{
public:
    RandomSeeder()
    {
        srand(1); // Change to 2 to test for Asmt04_Run2.txt.
    }
};

static RandomSeeder _random_seeder;

#include "LinkedBag.h"
#include "LinkedBag.cpp"
#include "LinkedBag340.cpp"
