//	LinkedBag340.cpp
//	Created by: CSC340

#include "LinkedBag.h" // This include is necessary to define LinkedBag and Node.
#include <cstdlib>     // For rand()

template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340()
{
    if (itemCount < 2)
    {
        return false;
    }
    Node<ItemType>* nodeToDeletePtr = headPtr->getNext();
    headPtr->setNext(nodeToDeletePtr->getNext());
    delete nodeToDeletePtr;
    nodeToDeletePtr = nullptr;
    itemCount--;
    return true;
}

template<typename ItemType>
bool LinkedBag<ItemType>::addEnd340(const ItemType& newEntry)
{
    Node<ItemType>* newNodePtr = new Node<ItemType>();
    newNodePtr->setItem(newEntry);
    newNodePtr->setNext(nullptr);
    if (isEmpty())
    {
        headPtr = newNodePtr;
    } else {
        Node<ItemType>* lastNodePtr = headPtr;
        while (lastNodePtr->getNext() != nullptr)
        {
            lastNodePtr = lastNodePtr->getNext();
        }
        lastNodePtr->setNext(newNodePtr);
    }
    itemCount++;
    return true;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Iterative() const
{
    int size = 0;
    Node<ItemType>* curPtr = headPtr;
    while (curPtr != nullptr)
    {
        size++;
        curPtr = curPtr->getNext();
    }
    return size;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const
{
    return getCurrentSize340RecursiveHelper(headPtr);
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(Node<ItemType>* curPtr) const
{
    if (curPtr == nullptr)
    {
        return 0;
    }
    return 1 + getCurrentSize340RecursiveHelper(curPtr->getNext());
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveNoHelper() const
{
    if (isEmpty())
    {
        return 0;
    }
    LinkedBag<ItemType> restOfBag;
    restOfBag.headPtr = headPtr->getNext();
    int size = 1 + restOfBag.getCurrentSize340RecursiveNoHelper();
    restOfBag.headPtr = nullptr;
    return size;
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType& anEntry) const
{
    return getFrequencyOf340RecursiveHelper(headPtr, anEntry);
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveHelper(Node<ItemType>* curPtr, const ItemType& anEntry) const
{
    if (curPtr == nullptr)
    {
        return 0;
    }
    int frequency = getFrequencyOf340RecursiveHelper(curPtr->getNext(), anEntry);
    if (curPtr->getItem() == anEntry)
    {
        return 1 + frequency;
    }
    return frequency;
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveNoHelper(const ItemType& anEntry) const
{
    if (isEmpty())
    {
        return 0;
    }
    LinkedBag<ItemType> restOfBag;
    restOfBag.headPtr = headPtr->getNext();
    int freqInRest = restOfBag.getFrequencyOf340RecursiveNoHelper(anEntry);
    restOfBag.headPtr = nullptr;
    if (headPtr->getItem() == anEntry)
    {
        return 1 + freqInRest;
    }
    return freqInRest;
}

template<typename ItemType>
ItemType LinkedBag<ItemType>::removeRandom340()
{
    if (isEmpty())
    {
        return ItemType{};
    }
    int randomIndex = rand() % itemCount;
    Node<ItemType>* nodeToRemovePtr = nullptr;
    ItemType itemToReturn;
    if (randomIndex == 0) {
        nodeToRemovePtr = headPtr;
        headPtr = headPtr->getNext();
    } else {
        Node<ItemType>* prevPtr = headPtr;
        for (int i = 0; i < randomIndex - 1; i++) {
            prevPtr = prevPtr->getNext();
        }
        nodeToRemovePtr = prevPtr->getNext();
        prevPtr->setNext(nodeToRemovePtr->getNext());
    }
    itemToReturn = nodeToRemovePtr->getItem();
    delete nodeToRemovePtr;
    nodeToRemovePtr = nullptr;
    itemCount--;
    return itemToReturn;
}
