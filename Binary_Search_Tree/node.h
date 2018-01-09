#ifndef SEARCHTREE_NODE_H
#define SEARCHTREE_NODE_H

#include "tree.h"
#include "iterator.h"

// btree classes definitions
template<template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
class BinarySearchTree;

namespace btree {
    template<typename KeyType, typename ValueType>
    class SimpleTree;
}


template<template<typename, typename> class DerivedNodeType, typename KeyType, typename ValueType>
class BaseNode {
private:

    using NodePtrType = DerivedNodeType<KeyType, ValueType>*;

    BaseNode() = default;

protected:

    NodePtrType parent;
    NodePtrType right;
    NodePtrType left;

    explicit BaseNode(const KeyType &key, const ValueType &value, const NodePtrType parent) :
            parent(parent),
            right(nullptr),
            left(nullptr),
            key(key),
            value(value) {
        ;
    }

    BaseNode(const BaseNode &node, const NodePtrType parent) :
            parent(parent),
            right(nullptr),
            left(nullptr),
            key(node.key),
            value(node.value) {
        ;
    }

public:

    KeyType key;
    ValueType value;

};


template<typename KeyType, typename ValueType>
class SimpleNode : public BaseNode<SimpleNode, KeyType, ValueType> {
private:

    using BaseNodeType = BaseNode<::SimpleNode, KeyType, ValueType>;
    using NodeType = SimpleNode<KeyType, ValueType>;
    using NodePtrType = NodeType*;

    // Iterators and simple tree can access to parent, left and right pointers of simple node
    friend class BinarySearchTree<btree::SimpleTree, ::SimpleNode, KeyType, ValueType>;
    friend class btree::SimpleTree<KeyType, ValueType>;
    friend class InorderIterator<NodeType>;
    friend class PreorderIterator<NodeType>;
    friend class PostorderIterator<NodeType>;

    SimpleNode() = default;

    explicit SimpleNode(const KeyType &key, const ValueType &value, const NodePtrType parent = nullptr) :
            BaseNodeType(key, value, parent) {
        ;
    }

    SimpleNode(const SimpleNode &node, const NodePtrType parent = nullptr) :
            BaseNodeType(node, parent) {
        ;
    }
};

#endif //SEARCHTREE_NODE_H