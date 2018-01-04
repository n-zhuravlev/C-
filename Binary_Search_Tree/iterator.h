#ifndef SEARCHTREE_ITERATOR_H
#define SEARCHTREE_ITERATOR_H


template<template<typename> class DerivedIteratorType, typename NodeType>
class Iterator {
private:

    using IteratorType = DerivedIteratorType<NodeType>;
    using NodePtrType = NodeType*;

protected:

    NodePtrType ptr;

    explicit Iterator(const NodePtrType ptr_ = nullptr) :
            ptr(ptr_) {
        ;
    }

    Iterator(const Iterator &iter) :
            ptr(iter.ptr) {
        ;
    }

public:

    IteratorType &operator=(const IteratorType &iter) {
        ptr = iter.ptr;
        return *this;
    }

    IteratorType &operator=(const NodePtrType ptr_) {
        ptr = ptr_;
        return *this;
    }

    explicit operator bool() const {
        return static_cast<bool>(ptr);
    }

    bool operator!() const {
        return !(static_cast<bool>(ptr));
    }

    bool operator==(const IteratorType &iter) const {
        return ptr == iter.ptr;
    }

    bool operator==(const NodePtrType ptr_) const {
        return ptr == ptr_;
    }

    template<template<typename> class, typename>
    friend bool operator==(const NodePtrType ptr_, const IteratorType &iter);

    bool operator!=(const IteratorType &iter) const {
        return ptr != iter.ptr;
    }

    bool operator!=(const NodePtrType ptr_) const {
        return ptr != ptr_;
    }

    template<template<typename> class, typename>
    friend bool operator!=(const NodePtrType ptr_, const IteratorType &iter);

    bool operator&&(const IteratorType &iter) const {
        return ptr && iter.ptr;
    }

    bool operator&&(const NodePtrType ptr_) const {
        return ptr && ptr_;
    }

    template<template<typename> class, typename>
    friend bool operator&&(const NodePtrType ptr_, const IteratorType &iter);

    bool operator||(const IteratorType &iter) const {
        return ptr || iter.ptr;
    }

    bool operator||(const NodePtrType ptr_) const {
        return ptr || ptr_;
    }

    template<template<typename> class, typename>
    friend bool operator||(const NodePtrType ptr_, const IteratorType &iter);

    const NodePtrType get() const {
        return ptr;
    }
};


template<typename NodeType>
class InorderIterator : public Iterator<InorderIterator, NodeType> {
private:

    using BaseIteratorType = Iterator<InorderIterator, NodeType>;
    using IteratorType = InorderIterator<NodeType>;
    using NodePtrType = NodeType*;

public:

    explicit InorderIterator(const NodePtrType ptr_ = nullptr) :
            BaseIteratorType(ptr_) {
        ;
    }

    InorderIterator(const InorderIterator &iter) :
            BaseIteratorType(iter) {
        ;
    }

    IteratorType &operator++();
    IteratorType operator++(int);
    IteratorType &operator--();
    IteratorType operator--(int);

};


template<typename NodeType>
class PreorderIterator : public Iterator<PreorderIterator, NodeType> {
private:

    using BaseIteratorType = Iterator<PreorderIterator, NodeType>;
    using IteratorType = PreorderIterator<NodeType>;
    using NodePtrType = NodeType*;

public:

    explicit PreorderIterator(const NodePtrType ptr_ = nullptr) :
            BaseIteratorType(ptr_) {
        ;
    }

    PreorderIterator(const PreorderIterator &iter) :
            BaseIteratorType(iter) {
        ;
    }

    IteratorType &operator++();
    IteratorType operator++(int);
    IteratorType &operator--();
    IteratorType operator--(int);

};


template<typename NodeType>
class PostorderIterator : public Iterator<PostorderIterator, NodeType> {
private:

    using BaseIteratorType = Iterator<PostorderIterator, NodeType>;
    using IteratorType = PostorderIterator<NodeType>;
    using NodePtrType = NodeType*;

public:

    explicit PostorderIterator(const NodePtrType ptr_ = nullptr) :
            BaseIteratorType(ptr_) {
        ;
    }

    PostorderIterator(const PostorderIterator &iter) :
            BaseIteratorType(iter) {
        ;
    }

    IteratorType &operator++();
    IteratorType operator++(int);
    IteratorType &operator--();
    IteratorType operator--(int);

};

#endif //SEARCHTREE_ITERATOR_H