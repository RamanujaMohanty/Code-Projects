#include "LinkedBag.h"
#include <cstdlib>

template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340() {
    if (itemCount < 2) return false;

    auto nodeToDelete = headPtr->getNext();
    headPtr->setNext(nodeToDelete->getNext());
    itemCount--;
    return true;
}

template<typename ItemType>
bool LinkedBag<ItemType>::addEnd340(const ItemType& newEntry) {
    auto newNode = std::make_shared<Node<ItemType>>(newEntry);
    newNode->setNext(nullptr);

    if (isEmpty()) {
        headPtr = newNode;
    } else {
        auto lastPtr = headPtr;
        while (lastPtr->getNext() != nullptr) {
            lastPtr = lastPtr->getNext();
        }
        lastPtr->setNext(newNode);
    }

    itemCount++;
    return true;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Iterative() const {
    int count = 0;
    auto cur = headPtr;
    while (cur != nullptr) {
        count++;
        cur = cur->getNext();
    }
    return count;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const {
    return getCurrentSize340RecursiveHelper(headPtr);
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(std::shared_ptr<Node<ItemType>> cur) const {
    if (!cur) return 0;
    return 1 + getCurrentSize340RecursiveHelper(cur->getNext());
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveNoHelper() const {
    if (isEmpty()) return 0;

    LinkedBag<ItemType> rest;
    rest.headPtr = headPtr->getNext();
    int size = 1 + rest.getCurrentSize340RecursiveNoHelper();
    rest.headPtr = nullptr;
    return size;
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType& entry) const {
    return getFrequencyOf340RecursiveHelper(headPtr, entry);
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveHelper(std::shared_ptr<Node<ItemType>> cur, const ItemType& entry) const {
    if (!cur) return 0;

    int freq = getFrequencyOf340RecursiveHelper(cur->getNext(), entry);
    if (cur->getItem() == entry)
        return 1 + freq;
    return freq;
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveNoHelper(const ItemType& entry) const {
    if (isEmpty()) return 0;

    LinkedBag<ItemType> rest;
    rest.headPtr = headPtr->getNext();
    int freq = rest.getFrequencyOf340RecursiveNoHelper(entry);
    rest.headPtr = nullptr;

    if (headPtr->getItem() == entry)
        return 1 + freq;
    return freq;
}

template<typename ItemType>
ItemType LinkedBag<ItemType>::removeRandom340() {
    if (isEmpty()) return ItemType{};

    int index = rand() % itemCount;
    ItemType result;

    if (index == 0) {
        result = headPtr->getItem();
        headPtr = headPtr->getNext();
    } else {
        auto prev = headPtr;
        for (int i = 0; i < index - 1; i++) {
            prev = prev->getNext();
        }
        auto nodeToRemove = prev->getNext();
        result = nodeToRemove->getItem();
        prev->setNext(nodeToRemove->getNext());
    }

    itemCount--;
    return result;
}
