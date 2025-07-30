// Node.cpp
#include "Node.h"

template<typename ItemType>
Node<ItemType>::Node() : item() {}

template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem) {}

template<typename ItemType>
Node<ItemType>::~Node() {
    // Added for Part C to show when objects are destroyed
    std::cout << "Destroyed Node containing: " << item << std::endl;
}

template<typename ItemType>
void Node<ItemType>::setItem(const ItemType& anItem) {
    item = anItem;
}

template<typename ItemType>
void Node<ItemType>::setNext(std::unique_ptr<Node<ItemType>> nextNodePtr) {
    next = std::move(nextNodePtr); // Use std::move to transfer ownership
}

template<typename ItemType>
ItemType Node<ItemType>::getItem() const {
    return item;
}

template<typename ItemType>
Node<ItemType>* Node<ItemType>::getNext() const {
    return next.get(); // .get() returns a raw pointer for non-owning access
}

template<typename ItemType>
std::unique_ptr<Node<ItemType>> Node<ItemType>::takeNext() {
    return std::move(next); // Transfer ownership away from this node
}
