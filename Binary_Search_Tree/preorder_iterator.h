#ifndef SEARCHTREE_PREORDER_ITERATOR_H
#define SEARCHTREE_PREORDER_ITERATOR_H

// define preorder iterator class
// all iterators are defined in nested namespace btree::iter

// declarations
namespace btree {

	namespace iter {

		template<template<typename> class DerivedIterator, typename Node>
		class Iterator;

		template<typename Node>
		class PreorderIterator;

	}

}


// definitions
namespace btree {

	namespace iter {

		template<typename Node>
		class PreorderIterator : public Iterator<PreorderIterator, Node> {
		private:

			using BaseIterator = Iterator<btree::iter::PreorderIterator, Node>;
			using NodePtr = Node*;

		public:

			explicit PreorderIterator(const NodePtr node_ptr = nullptr) : BaseIterator(node_ptr) {}

			PreorderIterator  &operator++();
			PreorderIterator  operator++(int);
			PreorderIterator  &operator--();
			PreorderIterator  operator--(int);
		};

	}

}


template<typename Node>
typename btree::iter::PreorderIterator<Node> &btree::iter::PreorderIterator<Node>::operator++()
{
	if (this->ptr) {

		if (this->ptr->left) {
			this->ptr = this->ptr->left;
		}
		else if (this->ptr->right) {
			this->ptr = this->ptr->right;
		}
		else {

			while (true) {

				if (this->ptr->parent == nullptr) {
					this->ptr = nullptr;
					break;
				}
				else if ((this->ptr->parent->right == this->ptr) || (this->ptr->parent->right == nullptr)) {
					this->ptr = this->ptr->parent;
				}
				else {
					this->ptr = this->ptr->parent->right;
					break;
				}
			}
		}
	}

	return *this;
}


template<typename Node>
typename btree::iter::PreorderIterator<Node> btree::iter::PreorderIterator<Node>::operator++(int)
{
	NodePtr previous_ptr = this->ptr;

	if (this->ptr) {

		if (this->ptr->left) {
			this->ptr = this->ptr->left;
		}
		else if (this->ptr->right) {
			this->ptr = this->ptr->right;
		}
		else {

			while (true) {

				if (this->ptr->parent == nullptr) {
					this->ptr = nullptr;
					break;
				}
				else if ((this->ptr->parent->right == this->ptr) || (this->ptr->parent->right == nullptr)) {
					this->ptr = this->ptr->parent;
				}
				else {
					this->ptr = this->ptr->parent->right;
					break;
				}
			}
		}
	}

	return btree::iter::PreorderIterator<Node>(previous_ptr);
}


template<typename Node>
typename btree::iter::PreorderIterator<Node> &btree::iter::PreorderIterator<Node>::operator--()
{

	if (this->ptr) {

		if (this->ptr->parent && (this->ptr->parent->right == this->ptr) && this->ptr->parent->left) {

			this->ptr = this->ptr->parent->left;

			while (true) {

				if (this->ptr->right) {
					this->ptr = this->ptr->right;
				}
				else if (this->ptr->left) {
					this->ptr = this->ptr->left;
				}
				else break;
			}
		}
		else {
			this->ptr = this->ptr->parent;
		}
	}

	return *this;
}


template<typename Node>
typename btree::iter::PreorderIterator<Node> btree::iter::PreorderIterator<Node>::operator--(int)
{
	NodePtr previous_ptr = this->ptr;

	if (this->ptr) {

		if (this->ptr->parent && (this->ptr->parent->right == this->ptr) && this->ptr->parent->left) {

			this->ptr = this->ptr->parent->left;

			while (true) {

				if (this->ptr->right) {
					this->ptr = this->ptr->right;
				}
				else if (this->ptr->left) {
					this->ptr = this->ptr->left;
				}
				else break;
			}
		}
		else {
			this->ptr = this->ptr->parent;
		}
	}

	return btree::iter::PreorderIterator<Node>(previous_ptr);
}

#endif //SEARCHTREE_PREORDER_ITERATOR_H