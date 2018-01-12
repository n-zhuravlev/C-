#ifndef SEARCHTREE_BASE_NODE_H
#define SEARCHTREE_BASE_NODE_H

// define base class for all btree nodes
// all nodes are defined in nested namespace btree::node

namespace btree {

	namespace node {

		template<template<typename, typename> class DerivedNode, typename Key, typename Value>
		class BaseNode {
		private:

			using NodePtr = DerivedNode<Key, Value>*;

			BaseNode() = default;

		protected:

			NodePtr parent;
			NodePtr right;
			NodePtr left;

			explicit BaseNode(const Key &key, const Value &value, const NodePtr parent_ptr);
			BaseNode(const BaseNode &node, const NodePtr parent_ptr);

		public:

			Key key;
			Value value;
		};

	}

}


template<template<typename, typename> class DerivedNode, typename Key, typename Value>
inline explicit btree::node::BaseNode<DerivedNode, Key, Value>::BaseNode(const Key &key, const Value &value, const NodePtr parent_ptr) :
	key(key), value(value), parent(parent_ptr), right(nullptr), left(nullptr) {}

template<template<typename, typename> class DerivedNode, typename Key, typename Value>
inline explicit btree::node::BaseNode<DerivedNode, Key, Value>::BaseNode(const BaseNode &node, const NodePtr parent_ptr) :
	key(node.key), value(node.value), parent(parent_ptr), right(nullptr), left(nullptr) {}


#endif //SEARCHTREE_BASE_NODE_H