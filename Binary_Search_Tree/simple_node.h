#ifndef SEARCHTREE_SIMPLE_NODE_H
#define SEARCHTREE_SIMPLE_NODE_H

// define simple node class
// all nodes are defined in nested namespace btree::node

// declarations
namespace btree {

	namespace iter {

		template<typename Node>
		class InorderIterator;

		template<typename Node>
		class PreorderIterator;

		template<typename Node>
		class PostorderIterator;

	}

	namespace node {

		template<template<typename, typename> class DerivedNode, typename Key, typename Value>
		class Node;

		template<typename Key, typename Value>
		class SimpleNode;

	}

}


// definitions
namespace btree {

	namespace node {

		template<typename Key, typename Value>
		class SimpleNode : public Node<SimpleNode, Key, Value> {
		private:

			using BaseNode = Node<btree::node::SimpleNode, Key, Value>;
			using NodePtr = SimpleNode*;

			// Iterators and simple tree own a simple node
			friend class btree::iter::InorderIterator<SimpleNode>;
			friend class btree::iter::PreorderIterator<SimpleNode>;
			friend class btree::iter::PostorderIterator<SimpleNode>;

			SimpleNode() = default;
			explicit SimpleNode(const Key &key, const Value &value, const NodePtr parent_ptr = nullptr) : BaseNode(key, value, parent_ptr) {}
			SimpleNode(const SimpleNode &node, const NodePtr parent_ptr = nullptr) : BaseNode(node, parent_ptr) {}
		};

	}

}


#endif //SEARCHTREE_SIMPLE_NODE_H