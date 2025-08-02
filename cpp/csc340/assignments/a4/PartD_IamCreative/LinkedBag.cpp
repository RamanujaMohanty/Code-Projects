#include "LinkedBag.h"
#include <iostream>

template<typename ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0) {}

template<typename ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag) {
    itemCount = aBag.itemCount;
    std::shared_ptr<Node<ItemType>> origChainPtr = aBag.headPtr;

    if (!origChainPtr) {
        headPtr = nullptr;
    } else {
        headPtr = std::make_shared<Node<ItemType>>(origChainPtr->getItem());
        std::shared_ptr<Node<ItemType>> newChainPtr = headPtr;
        origChainPtr = origChainPtr->getNext();

        while (origChainPtr != nullptr) {
            auto newNode = std::make_shared<Node<ItemType>>(origChainPtr->getItem());
            newChainPtr->setNext(newNode);
            newChainPtr = newChainPtr->getNext();
            origChainPtr = origChainPtr->getNext();
        }
    }
}

template<typename ItemType>
LinkedBag<ItemType>::~LinkedBag() {
    std::cout << "[Destructor] LinkedBag object is being destroyed...\n";
    clear();
}

template<typename ItemType>
bool LinkedBag<ItemType>::isEmpty() const {
    return itemCount == 0;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize() const {
    return itemCount;
}

template<typename ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry) {
    auto newNodePtr = std::make_shared<Node<ItemType>>(newEntry);
    newNodePtr->setNext(headPtr);
    headPtr = newNodePtr;
    itemCount++;
    return true;
}

template<typename ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry) {
    auto entryNodePtr = getPointerTo(anEntry);
    bool canRemove = !isEmpty() && (entryNodePtr != nullptr);

    if (canRemove) {
        entryNodePtr->setItem(headPtr->getItem());
        headPtr = headPtr->getNext();
        itemCount--;
    }

    return canRemove;
}

template<typename ItemType>
void LinkedBag<ItemType>::clear() {
    headPtr = nullptr;
    itemCount = 0;
}

template<typename ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const {
    return (getPointerTo(anEntry) != nullptr);
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const {
    int frequency = 0;
    auto curPtr = headPtr;
    while (curPtr != nullptr) {
        if (curPtr->getItem() == anEntry) {
            frequency++;
        }
        curPtr = curPtr->getNext();
    }
    return frequency;
}

template<typename ItemType>
std::vector<ItemType> LinkedBag<ItemType>::toVector() const {
    std::vector<ItemType> bagContents;
    auto curPtr = headPtr;
    while (curPtr != nullptr) {
        bagContents.push_back(curPtr->getItem());
        curPtr = curPtr->getNext();
    }
    return bagContents;
}

template<typename ItemType>
std::shared_ptr<Node<ItemType>> LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const {
    auto curPtr = headPtr;
    while (curPtr != nullptr) {
        if (curPtr->getItem() == anEntry) {
            return curPtr;
        }
        curPtr = curPtr->getNext();
    }
    return nullptr;
}

template<class ItemType>
std::shared_ptr<LinkedBag<ItemType>> LinkedBag<ItemType>::merge_remove_duplicates(
    const std::shared_ptr<LinkedBag<ItemType>>& other_bag) const
{
    auto result = std::make_shared<LinkedBag<ItemType>>();

    for (const auto& item : toVector()) {
        if (!result->contains(item)) {
            result->add(item);
        }
    }

    for (const auto& item : other_bag->toVector()) {
        if (!result->contains(item)) {
            result->add(item);
        }
    }

    return result;
}

// Explicit instantiations (optional if used in separate cpp)
template std::shared_ptr<LinkedBag<std::string>> LinkedBag<std::string>::merge_remove_duplicates(
    const std::shared_ptr<LinkedBag<std::string>>& other_bag) const;

