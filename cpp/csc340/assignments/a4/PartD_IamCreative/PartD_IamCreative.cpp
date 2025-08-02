#include <iostream>
#include <memory>
#include <string>
#include "Include.h"

int main() {
    auto bag1 = std::make_shared<LinkedBag<std::string>>();
    bag1->add("apple");
    bag1->add("banana");

    auto bag2 = std::make_shared<LinkedBag<std::string>>();
    bag2->add("banana");
    bag2->add("cherry");

    auto merged_bag = bag1->merge_remove_duplicates(bag2);

    std::cout << "Merged Bag (no duplicates): ";
    for (const auto& item : merged_bag->toVector()) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    return 0;
}

