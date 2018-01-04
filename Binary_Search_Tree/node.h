#ifndef SEARCHTREE_NODE_H
#define SEARCHTREE_NODE_H


template<template<typename, typename> class DerivedNodeType, typename KeyType, typename ValueType>
class BaseNode {
private:

    using NodePtrType = DerivedNodeType<KeyType, ValueType>*;

    BaseNode() = default;

protected:

    NodePtrType parent;
    NodePtrType right;
    NodePtrType left;

    explicit BaseNode(const KeyType &key, const ValueType &value) :
            parent(nullptr),
            right(nullptr),
            left(nullptr),
            key(key),
            value(value) {
        ;
    }

    BaseNode(const BaseNode &node, const NodePtrType parent = nullptr) :
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
    using NodePtrType = SimpleNode<KeyType, ValueType>*;

    //friend class BinarySearchTree<::SimpleNode, KeyType, ValueType>;
    //friend class InorderIterator<::SimpleNode>;

    SimpleNode() = default;

protected:

    explicit SimpleNode(const KeyType &key, const ValueType &value) :
            BaseNodeType(key, value) {
        ;
    }

    SimpleNode(const SimpleNode &node, const NodePtrType parent = nullptr) :
            BaseNodeType(node, parent) {
        ;
    }
};

#endif //SEARCHTREE_NODE_H