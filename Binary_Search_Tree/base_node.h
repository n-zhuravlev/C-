#ifndef SEARCHTREE_BASE_NODE_H
#define SEARCHTREE_BASE_NODE_H

// define base class for all btree nodes
// all nodes are defined in nested namespace btree::node

namespace btree {

	namespace node {

		template<template<typename, typename> class DerivedNode, typename Key, typename Value>
		class Node {
		private:

			using NodePtr = DerivedNode<Key, Value>*;

			Node() = default;

		protected:

			NodePtr parent;
			NodePtr right;
			NodePtr left;

			explicit Node(const Key &key, const Value &value, const NodePtr parent_ptr);
			Node(const Node &node, const NodePtr parent_ptr);

		public:

			Key key;
			Value value;
		};

	}

}


template<template<typename, typename> class DerivedNode, typename Key, typename Value>
inline btree::node::Node<DerivedNode, Key, Value>::Node(const Key &key, const Value &value, const NodePtr parent_ptr) :
	key(key), value(value), parent(parent_ptr), right(nullptr), left(nullptr) {}

template<template<typename, typename> class DerivedNode, typename Key, typename Value>
inline btree::node::Node<DerivedNode, Key, Value>::Node(const Node &node, const NodePtr parent_ptr) :
	key(node.key), value(node.value), parent(parent_ptr), right(nullptr), left(nullptr) {}


#endif //SEARCHTREE_BASE_NODE_H