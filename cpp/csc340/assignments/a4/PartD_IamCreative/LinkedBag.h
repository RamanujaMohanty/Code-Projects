#pragma once
#include "Node.cpp"
#include "BagInterface.h"
#include <memory>

template<typename ItemType>
class LinkedBag : public BagInterface<ItemType> {
public:
    // CSC340 Add-ons
    bool removeSecondNode340();
    bool addEnd340(const ItemType&);
    int getCurrentSize340Iterative() const;
    int getCurrentSize340Recursive() const;
    int getCurrentSize340RecursiveNoHelper() const;
    int getFrequencyOf340Recursive(const ItemType&) const;
    int getFrequencyOf340RecursiveNoHelper(const ItemType&) const;
    ItemType removeRandom340();

private:
    int getCurrentSize340RecursiveHelper(std::shared_ptr<Node<ItemType>>) const;
    int getFrequencyOf340RecursiveHelper(std::shared_ptr<Node<ItemType>>, const ItemType&) const;

public:
    LinkedBag();
    LinkedBag(const LinkedBag<ItemType>&);
    virtual ~LinkedBag();

    int getCurrentSize() const;
    bool isEmpty() const;
    bool add(const ItemType&);
    bool remove(const ItemType&);
    void clear();
    bool contains(const ItemType&) const;
    int getFrequencyOf(const ItemType&) const;
    std::vector<ItemType> toVector() const;
    std::shared_ptr<LinkedBag<ItemType>> merge_remove_duplicates(
        const std::shared_ptr<LinkedBag<ItemType>>& other_bag) const;

private:
    std::shared_ptr<Node<ItemType>> headPtr{ nullptr };
    int itemCount{ 0 };

    std::shared_ptr<Node<ItemType>> getPointerTo(const ItemType&) const;
};
