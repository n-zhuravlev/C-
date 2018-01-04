#include "iterator.h"

// Iterator friend functions

template<template<typename> class DerivedIteratorType, typename NodeType>
inline bool operator==(const typename Iterator<DerivedIteratorType, NodeType>::NodePtrType ptr_, const typename Iterator<DerivedIteratorType, NodeType>::IteratorType &iter)
{
    return ptr_ == iter.ptr;
}


template<template<typename> class DerivedIteratorType, typename NodeType>
inline bool operator!=(const typename Iterator<DerivedIteratorType, NodeType>::NodePtrType ptr_, const typename Iterator<DerivedIteratorType, NodeType>::IteratorType &iter)
{
    return ptr_ != iter.ptr;
}


template<template<typename> class DerivedIteratorType, typename NodeType>
inline bool operator&&(const typename Iterator<DerivedIteratorType, NodeType>::NodePtrType ptr_, const typename Iterator<DerivedIteratorType, NodeType>::IteratorType &iter)
{
    return ptr_ && iter.ptr;
}


template<template<typename> class DerivedIteratorType, typename NodeType>
inline bool operator||(const typename Iterator<DerivedIteratorType, NodeType>::NodePtrType ptr_, const typename Iterator<DerivedIteratorType, NodeType>::IteratorType &iter)
{
    return ptr_ || iter.ptr;
}


template<typename NodeType>
typename InorderIterator<NodeType>::IteratorType &InorderIterator<NodeType>::operator++()
{
    if (this->ptr) {

        if (this->ptr->right) {

            this->ptr = this->ptr->right;

            while (this->ptr->left)
                this->ptr = this->ptr->left;
        }
        else {

            while (this->ptr->parent && (this->ptr == this->ptr->parent->right))
                this->ptr = this->ptr->parent;

            this->ptr = this->ptr->parent;
        }
    }

    return *this;
}


template<typename NodeType>
typename InorderIterator<NodeType>::IteratorType InorderIterator<NodeType>::operator++(int)
{
    NodePtrType previous_ptr = this->ptr;

    if (this->ptr) {

        if (this->ptr->right) {

            this->ptr = this->ptr->right;

            while (this->ptr->left)
                this->ptr = this->ptr->left;
        }
        else {

            while (this->ptr->parent && (this->ptr == this->ptr->parent->right))
                this->ptr = this->ptr->parent;

            this->ptr = this->ptr->parent;
        }
    }

    return IteratorType(previous_ptr);
}


template<typename NodeType>
typename InorderIterator<NodeType>::IteratorType &InorderIterator<NodeType>::operator--()
{

    if (this->ptr) {

        if (this->ptr->left) {

            this->ptr = this->ptr->left;

            while (this->ptr->right)
                this->ptr = this->ptr->right;
        }
        else {

            while (this->ptr->parent && (this->ptr == this->ptr->parent->left))
                this->ptr = this->ptr->parent;

            this->ptr = this->ptr->parent;
        }
    }

    return *this;
}


template<typename NodeType>
typename InorderIterator<NodeType>::IteratorType InorderIterator<NodeType>::operator--(int)
{
    NodePtrType previous_ptr = this->ptr;

    if (this->ptr) {

        if (this->ptr->left) {

            this->ptr = this->ptr->left;

            while (this->ptr->right)
                this->ptr = this->ptr->right;
        }
        else {

            while (this->ptr->parent && (this->ptr == this->ptr->parent->left))
                this->ptr = this->ptr->parent;

            this->ptr = this->ptr->parent;
        }
    }

    return IteratorType(previous_ptr);
}


template<typename NodeType>
typename PreorderIterator<NodeType>::IteratorType &PreorderIterator<NodeType>::operator++()
{
    if (this->ptr) {

        if (this->ptr->left)
            this->ptr = this->ptr->left;

        else if (this->ptr->right)
            this->ptr = this->ptr->right;

        else {

            while (true) {

                if (this->ptr->parent == nullptr) {
                    this->ptr = nullptr;
                    break;
                }

                else if ( (this->ptr->parent->right == this->ptr) || (this->ptr->parent->right == nullptr) )
                    this->ptr = this->ptr->parent;

                else {
                    this->ptr = this->ptr->parent->right;
                    break;
                }
            }
        }
    }

    return *this;
}


template<typename NodeType>
typename PreorderIterator<NodeType>::IteratorType PreorderIterator<NodeType>::operator++(int)
{
    NodePtrType previous_ptr = this->ptr;

    if (this->ptr) {

        if (this->ptr->left)
            this->ptr = this->ptr->left;

        else if (this->ptr->right)
            this->ptr = this->ptr->right;

        else {

            while (true) {

                if (this->ptr->parent == nullptr) {
                    this->ptr = nullptr;
                    break;
                }

                else if ((this->ptr->parent->right == this->ptr) || (this->ptr->parent->right == nullptr))
                    this->ptr = this->ptr->parent;

                else {
                    this->ptr = this->ptr->parent->right;
                    break;
                }
            }
        }
    }

    return IteratorType(previous_ptr);
}


template<typename NodeType>
typename PreorderIterator<NodeType>::IteratorType &PreorderIterator<NodeType>::operator--()
{
    if (this->ptr) {

        if (this->ptr->parent && (this->ptr->parent->right == this->ptr) && this->ptr->parent->left) {

            this->ptr = this->ptr->parent->left;

            while (true) {

                if (this->ptr->right)
                    this->ptr = this->ptr->right;

                else if (this->ptr->left)
                    this->ptr = this->ptr->left;

                else break;
            }
        }
        else this->ptr = this->ptr->parent;
    }

    return *this;
}


template<typename NodeType>
typename PreorderIterator<NodeType>::IteratorType PreorderIterator<NodeType>::operator--(int)
{
    NodePtrType previous_ptr = this->ptr;

    if (this->ptr) {

        if (this->ptr->parent && (this->ptr->parent->right == this->ptr) && this->ptr->parent->left) {

            this->ptr = this->ptr->parent->left;

            while (true) {

                if (this->ptr->right)
                    this->ptr = this->ptr->right;

                else if (this->ptr->left)
                    this->ptr = this->ptr->left;

                else break;
            }
        }
        else this->ptr = this->ptr->parent;
    }

    return IteratorType(previous_ptr);
}


template<typename NodeType>
typename PostorderIterator<NodeType>::IteratorType &PostorderIterator<NodeType>::operator++()
{
    if (this->ptr) {

        if ((this->ptr->parent == nullptr) || (this->ptr->parent->right == this->ptr) || (this->ptr->parent->right == nullptr))
            this->ptr = this->ptr->parent;

        else {

            this->ptr = this->ptr->parent->right;

            while (true) {

                if (this->ptr->left)
                    this->ptr = this->ptr->left;

                else if (this->ptr->right)
                    this->ptr = this->ptr->right;

                else break;
            }
        }
    }

    return *this;
}


template<typename NodeType>
typename PostorderIterator<NodeType>::IteratorType PostorderIterator<NodeType>::operator++(int)
{
    NodePtrType previous_ptr = this->ptr;

    if (this->ptr) {

        if ((this->ptr->parent == nullptr) || (this->ptr->parent->right == this->ptr) || (this->ptr->parent->right == nullptr))
            this->ptr = this->ptr->parent;

        else {

            this->ptr = this->ptr->parent->right;

            while (true) {

                if (this->ptr->left)
                    this->ptr = this->ptr->left;

                else if (this->ptr->right)
                    this->ptr = this->ptr->right;

                else break;
            }
        }
    }

    return IteratorType(previous_ptr);
}


template<typename NodeType>
typename PostorderIterator<NodeType>::IteratorType &PostorderIterator<NodeType>::operator--()
{
    if (this->ptr) {

        if (this->ptr->right)
            this->ptr = this->ptr->right;

        else if (this->ptr->left)
            this->ptr = this->ptr->left;

        else {

            while (true) {

                if (this->ptr->parent == nullptr) {
                    this->ptr = nullptr;
                    break;
                }
                else if ((this->ptr->parent->left == this->ptr) || (this->ptr->parent->left == nullptr))
                    this->ptr = this->ptr->parent;

                else {
                    this->ptr = this->ptr->parent->left;
                    break;
                }
            }
        }
    }

    return *this;
}


template<typename NodeType>
typename PostorderIterator<NodeType>::IteratorType PostorderIterator<NodeType>::operator--(int)
{
    NodePtrType previous_ptr = this->ptr;

    if (this->ptr) {

        if (this->ptr->right)
            this->ptr = this->ptr->right;

        else if (this->ptr->left)
            this->ptr = this->ptr->left;

        else {

            while (true) {

                if (this->ptr->parent == nullptr) {
                    this->ptr = nullptr;
                    break;
                }
                else if ((this->ptr->parent->left == this->ptr) || (this->ptr->parent->left == nullptr))
                    this->ptr = this->ptr->parent;

                else {
                    this->ptr = this->ptr->parent->left;
                    break;
                }
            }
        }
    }

    return IteratorType(previous_ptr);
}