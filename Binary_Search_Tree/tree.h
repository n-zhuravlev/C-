#ifndef SEARCHTREE_TREE_H
#define SEARCHTREE_TREE_H

#include <type_traits>
#include "metaclasses.h"
#include "iterator.h"
#include "node.h"


template<template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
class BinarySearchTree {
private:

    using NodeType = TreeNodeType<KeyType, ValueType>;
    using NodePtrType = NodeType*;
    using TreeType = DerivedTreeType<KeyType, ValueType>;

protected:

    NodePtrType head;

    BinarySearchTree() :
            head(nullptr) {
        ;
    }

    explicit BinarySearchTree(const KeyType &key, const ValueType &value) {
        head = new NodeType(key, value);
    }

    explicit BinarySearchTree(const KeyType *key, const ValueType &value) {
        head = new NodeType(*key, value);
    }

    explicit BinarySearchTree(const KeyType &key, const ValueType *value) {
        head = new NodeType(key, *value);
    }

    explicit BinarySearchTree(const KeyType *key, const ValueType *value) {
        head = new NodeType(*key, *value);
    }

    BinarySearchTree(const BinarySearchTree &tree);

    ~BinarySearchTree();

public:

    TreeType &operator=(const TreeType &tree);

    // you can get pointer to node with min key, max key, and head key of binary tree
    const NodePtrType head_key() const;
    const NodePtrType min_key() const;
    const NodePtrType max_key() const;

    // KeyType must have overloaded operator< or operator> and overloaded operator== or operator !=
    const NodePtrType find(const typename std::enable_if<(has_lt<KeyType>::value && has_neq<KeyType>::value), KeyType>::type &key) const;
    const NodePtrType find(const typename std::enable_if<(has_lt<KeyType>::value && has_eq<KeyType>::value), KeyType>::type &key) const;
    const NodePtrType find(const typename std::enable_if<(has_gt<KeyType>::value && has_neq<KeyType>::value), KeyType>::type &key) const;
    const NodePtrType find(const typename std::enable_if<(has_gt<KeyType>::value && has_eq<KeyType>::value), KeyType>::type &key) const;

    const NodePtrType find(const typename std::enable_if<(has_lt<KeyType>::value && has_neq<KeyType>::value), KeyType>::type *key) const;
    const NodePtrType find(const typename std::enable_if<(has_lt<KeyType>::value && has_eq<KeyType>::value), KeyType>::type *key) const;
    const NodePtrType find(const typename std::enable_if<(has_gt<KeyType>::value && has_neq<KeyType>::value), KeyType>::type *key) const;
    const NodePtrType find(const typename std::enable_if<(has_gt<KeyType>::value && has_eq<KeyType>::value), KeyType>::type *key) const;

};


namespace btree {


}

#endif //SEARCHTREE_TREE_H
