#ifndef SEARCHTREE_POSTORDER_ITERATOR_H
#define SEARCHTREE_POSTORDER_ITERATOR_H

// define postorder iterator class
// all iterators are defined in nested namespace btree::iter

// declarations
namespace btree {

	namespace iter {

		template<template<typename> class DerivedIterator, typename Node>
		class Iterator;

		template<typename Node>
		class PostorderIterator;

	}

}


// definitions
namespace btree {

	namespace iter {

		template<typename Node>
		class PostorderIterator : public Iterator<PostorderIterator, Node> {
		private:

			using BaseIterator = Iterator<btree::iter::PostorderIterator, Node>;
			using NodePtr = Node*;

		public:

			explicit PostorderIterator(const NodePtr node_ptr = nullptr) : BaseIterator(node_ptr) {}

			PostorderIterator  &operator++();
			PostorderIterator  operator++(int);
			PostorderIterator  &operator--();
			PostorderIterator  operator--(int);
		};

	}

}


template<typename Node>
typename btree::iter::PostorderIterator<Node> &btree::iter::PostorderIterator<Node>::operator++()
{
	if (this->ptr) {

		if ((this->ptr->parent == nullptr) || (this->ptr->parent->right == this->ptr) || (this->ptr->parent->right == nullptr)) {
			this->ptr = this->ptr->parent;
		}
		else {

			this->ptr = this->ptr->parent->right;

			while (true) {

				if (this->ptr->left) {
					this->ptr = this->ptr->left;
				}
				else if (this->ptr->right) {
					this->ptr = this->ptr->right;
				}
				else break;
			}
		}
	}

	return *this;
}


template<typename Node>
typename btree::iter::PostorderIterator<Node> btree::iter::PostorderIterator<Node>::operator++(int)
{
	NodePtr previous_ptr = this->ptr;

	if (this->ptr) {

		if ((this->ptr->parent == nullptr) || (this->ptr->parent->right == this->ptr) || (this->ptr->parent->right == nullptr)) {
			this->ptr = this->ptr->parent;
		}
		else {

			this->ptr = this->ptr->parent->right;

			while (true) {

				if (this->ptr->left) {
					this->ptr = this->ptr->left;
				}
				else if (this->ptr->right) {
					this->ptr = this->ptr->right;
				}
				else break;
			}
		}
	}

	return btree::iter::PostorderIterator<Node>(previous_ptr);
}


template<typename Node>
typename btree::iter::PostorderIterator<Node> &btree::iter::PostorderIterator<Node>::operator--()
{

	if (this->ptr) {

		if (this->ptr->right) {
			this->ptr = this->ptr->right;
		}
		else if (this->ptr->left) {
			this->ptr = this->ptr->left;
		}
		else {

			while (true) {

				if (this->ptr->parent == nullptr) {
					this->ptr = nullptr;
					break;
				}
				else if ((this->ptr->parent->left == this->ptr) || (this->ptr->parent->left == nullptr)) {
					this->ptr = this->ptr->parent;
				}
				else {
					this->ptr = this->ptr->parent->left;
					break;
				}
			}
		}
	}

	return *this;
}


template<typename Node>
typename btree::iter::PostorderIterator<Node> btree::iter::PostorderIterator<Node>::operator--(int)
{
	NodePtr previous_ptr = this->ptr;

	if (this->ptr) {

		if (this->ptr->right) {
			this->ptr = this->ptr->right;
		}
		else if (this->ptr->left) {
			this->ptr = this->ptr->left;
		}
		else {

			while (true) {

				if (this->ptr->parent == nullptr) {
					this->ptr = nullptr;
					break;
				}
				else if ((this->ptr->parent->left == this->ptr) || (this->ptr->parent->left == nullptr)) {
					this->ptr = this->ptr->parent;
				}
				else {
					this->ptr = this->ptr->parent->left;
					break;
				}
			}
		}
	}

	return btree::iter::PostorderIterator<Node>(previous_ptr);
}

#endif //SEARCHTREE_POSTORDER_ITERATOR_H