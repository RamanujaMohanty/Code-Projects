// LinkedBag.h
#pragma once
#include "Node.cpp"
#include "BagInterface.h"
#include <memory> // Required for std::unique_ptr

template<typename ItemType>
class LinkedBag : public BagInterface<ItemType> {

// ... (CSC340 interface is unchanged) ...
public:
	bool removeSecondNode340();
	bool addEnd340(const ItemType&);
	int getCurrentSize340Iterative() const;
	int getCurrentSize340Recursive() const;
	int getCurrentSize340RecursiveNoHelper() const;
	int getFrequencyOf340Recursive(const ItemType&) const;
	int getFrequencyOf340RecursiveNoHelper(const ItemType&) const;
	ItemType removeRandom340();
private:
	int getCurrentSize340RecursiveHelper(Node<ItemType>*) const;
	int getFrequencyOf340RecursiveHelper(Node<ItemType>*, const ItemType&) const;

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

private:
    std::unique_ptr<Node<ItemType>> headPtr{nullptr}; // headPtr now owns the list
    int itemCount{0};

    Node<ItemType>* getPointerTo(const ItemType&) const;
};
