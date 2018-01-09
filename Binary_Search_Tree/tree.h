#ifndef SEARCHTREE_TREE_H
#define SEARCHTREE_TREE_H

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
    template<typename K = KeyType>
    const NodePtrType find(const typename std::enable_if<(has_lt<K>::value && has_neq<K>::value), K>::type &key) const;

    template<typename K = KeyType>
    const NodePtrType find(const typename std::enable_if<(has_lt<K>::value && has_eq<K>::value), K>::type &key) const;

    template<typename K = KeyType>
    const NodePtrType find(const typename std::enable_if<(has_gt<K>::value && has_neq<K>::value), K>::type &key) const;

    template<typename K = KeyType>
    const NodePtrType find(const typename std::enable_if<(has_gt<K>::value && has_eq<K>::value), K>::type &key) const;

    template<typename K = KeyType>
    const NodePtrType find(const typename std::enable_if<(has_lt<K>::value && has_neq<K>::value), K>::type *key) const;

    template<typename K = KeyType>
    const NodePtrType find(const typename std::enable_if<(has_lt<K>::value && has_eq<K>::value), K>::type *key) const;

    template<typename K = KeyType>
    const NodePtrType find(const typename std::enable_if<(has_gt<K>::value && has_neq<K>::value), K>::type *key) const;

    template<typename K = KeyType>
    const NodePtrType find(const typename std::enable_if<(has_gt<K>::value && has_eq<K>::value), K>::type *key) const;

};


namespace btree {

    template<typename KeyType, typename ValueType>
    class SimpleTree : public BinarySearchTree<SimpleTree, SimpleNode, KeyType, ValueType> {
    private:

        using BaseTreeType = BinarySearchTree<btree::SimpleTree, SimpleNode, KeyType, ValueType>;
        using NodeType = SimpleNode<KeyType, ValueType>;
        using NodePtrType = NodeType*;

    public:

        // external users can see 3 iterators for simple tree
        using Inorder = InorderIterator<NodeType>;
        using Preorder = PreorderIterator<NodeType>;
        using Postorder = PostorderIterator<NodeType>;

        SimpleTree() :
                BaseTreeType() {
            ;
        }

        explicit SimpleTree(const KeyType &key, const ValueType &value) :
                BaseTreeType(key, value) {
            ;
        }

        explicit SimpleTree(const KeyType *key, const ValueType &value) :
                BaseTreeType(key, value) {
            ;
        }

        explicit SimpleTree(const KeyType &key, const ValueType *value) :
                BaseTreeType(key, value) {
            ;
        }

        explicit SimpleTree(const KeyType *key, const ValueType *value) :
                BaseTreeType(key, value) {
            ;
        }

        SimpleTree(const SimpleTree &tree) :
                BaseTreeType(tree) {
            ;
        }

        void add(const KeyType &key, const ValueType &value);

        void remove(const KeyType &key);

    };
}

#endif //SEARCHTREE_TREE_H
