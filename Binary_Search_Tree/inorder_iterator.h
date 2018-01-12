#ifndef SEARCHTREE_INORDER_ITERATOR_H
#define SEARCHTREE_INORDER_ITERATOR_H

// define inorder iterator class
// all iterators are defined in nested namespace btree::iter

// declarations
namespace btree {

	namespace iter {

		template<template<typename> class DerivedIterator, typename Node>
		class Iterator;

		template<typename Node>
		class InorderIterator;

	}

}


// definitions
namespace btree {

	namespace iter {

		template<typename Node>
		class InorderIterator : public Iterator<InorderIterator, Node> {
		private:

			using BaseIterator = Iterator<btree::iter::InorderIterator, Node>;
			using NodePtr = Node*;

		public:

			explicit InorderIterator(const NodePtr node_ptr = nullptr) : BaseIterator(node_ptr) {}

			InorderIterator &operator++();
			InorderIterator operator++(int);
			InorderIterator &operator--();
			InorderIterator operator--(int);
		};

	}

}


template<typename Node>
typename btree::iter::InorderIterator<Node> &btree::iter::InorderIterator<Node>::operator++()
{
	if (this->ptr) {

		if (this->ptr->right) {

			this->ptr = this->ptr->right;

			while (this->ptr->left) {
				this->ptr = this->ptr->left;
			}
		}
		else {

			while (this->ptr->parent && (this->ptr == this->ptr->parent->right)) {
				this->ptr = this->ptr->parent;
			}

			this->ptr = this->ptr->parent;
		}
	}

	return *this;
}


template<typename Node>
typename btree::iter::InorderIterator<Node> btree::iter::InorderIterator<Node>::operator++(int)
{
	NodePtr previous_ptr = this->ptr;

	if (this->ptr) {

		if (this->ptr->right) {

			this->ptr = this->ptr->right;

			while (this->ptr->left) {
				this->ptr = this->ptr->left;
			}
		}
		else {

			while (this->ptr->parent && (this->ptr == this->ptr->parent->right)) {
				this->ptr = this->ptr->parent;
			}

			this->ptr = this->ptr->parent;
		}
	}

	return btree::iter::InorderIterator<Node>(previous_ptr);
}


template<typename Node>
typename btree::iter::InorderIterator<Node> &btree::iter::InorderIterator<Node>::operator--()
{

	if (this->ptr) {

		if (this->ptr->left) {

			this->ptr = this->ptr->left;

			while (this->ptr->right) {
				this->ptr = this->ptr->right;
			}	
		}
		else {

			while (this->ptr->parent && (this->ptr == this->ptr->parent->left)) {
				this->ptr = this->ptr->parent;
			}

			this->ptr = this->ptr->parent;
		}
	}

	return *this;
}


template<typename Node>
typename btree::iter::InorderIterator<Node> btree::iter::InorderIterator<Node>::operator--(int)
{
	NodePtr previous_ptr = this->ptr;

	if (this->ptr) {

		if (this->ptr->left) {

			this->ptr = this->ptr->left;

			while (this->ptr->right) {
				this->ptr = this->ptr->right;
			}
		}
		else {

			while (this->ptr->parent && (this->ptr == this->ptr->parent->left)) {
				this->ptr = this->ptr->parent;
			}

			this->ptr = this->ptr->parent;
		}
	}

	return btree::iter::InorderIterator<Node>(previous_ptr);
}

#endif //SEARCHTREE_INORDER_ITERATOR_H