#pragma once
#include <memory>

template<typename ItemType>
class Node {
public:
    Node();
    Node(const ItemType&);
    Node(const ItemType&, std::shared_ptr<Node<ItemType>>);

    void setItem(const ItemType&);
    void setNext(std::shared_ptr<Node<ItemType>>);

    ItemType getItem() const;
    std::shared_ptr<Node<ItemType>> getNext() const;

private:
    ItemType item{};
    std::shared_ptr<Node<ItemType>> next{ nullptr };
};

