// Node.h
#pragma once
#include <memory> // Required for std::unique_ptr
#include <iostream> // For destructor message

template<typename ItemType>
class Node {
public:
    Node();
    Node(const ItemType&);
    ~Node(); // Destructor to show deallocation

    void setItem(const ItemType&);
    void setNext(std::unique_ptr<Node<ItemType>> nextNodePtr);
    ItemType getItem() const;
    Node<ItemType>* getNext() const;
    std::unique_ptr<Node<ItemType>> takeNext(); // Method to transfer ownership of the next node

private:
    ItemType item{};
    std::unique_ptr<Node<ItemType>> next{nullptr}; // Use unique_ptr for ownership
};
