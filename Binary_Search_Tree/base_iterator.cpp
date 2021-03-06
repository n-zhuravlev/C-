#ifndef SEARCHTREE_BASE_ITERATOR_H
#define SEARCHTREE_BASE_ITERATOR_H

// define base class for all btree iterators
// all iterators are defined in nested namespace btree::iter

// declarations
namespace btree {

	namespace iter {

		template<template<typename> class DerivedIterator, typename Node>
		class Iterator;

		template<typename SpecificIterator, typename NodePtr>
		bool operator==(const NodePtr node_ptr, const SpecificIterator &iter);

		template<typename SpecificIterator, typename NodePtr>
		bool operator!=(const NodePtr node_ptr, const SpecificIterator &iter);

		template<typename SpecificIterator, typename NodePtr>
		bool operator&&(const NodePtr node_ptr, const SpecificIterator &iter);

		template<typename SpecificIterator, typename NodePtr>
		bool operator||(const NodePtr node_ptr, const SpecificIterator &iter);

	}

}


// definitions
namespace btree {

	namespace iter {

		template<template<typename> class DerivedIterator, typename Node>
		class Iterator {
		private:

			using SpecificIterator = DerivedIterator<Node>;
			using NodePtr = Node*;

		protected:

			NodePtr ptr;

			explicit Iterator(const NodePtr ptr = nullptr) : ptr(ptr) {}

		public:

			SpecificIterator &operator=(const SpecificIterator &iter);
			SpecificIterator &operator=(const NodePtr node_ptr);

			operator bool() const;
			bool operator!() const;

			bool operator==(const SpecificIterator &iter) const;
			bool operator!=(const SpecificIterator &iter) const;
			bool operator&&(const SpecificIterator &iter) const;
			bool operator||(const SpecificIterator &iter) const;

			bool operator==(const NodePtr node_ptr) const;
			bool operator!=(const NodePtr node_ptr) const;
			bool operator&&(const NodePtr node_ptr) const;
			bool operator||(const NodePtr node_ptr) const;

			friend bool btree::iter::operator==<SpecificIterator, NodePtr>(const NodePtr node_ptr, const SpecificIterator &iter);
			friend bool btree::iter::operator!=<SpecificIterator, NodePtr>(const NodePtr node_ptr, const SpecificIterator &iter);
			friend bool btree::iter::operator&&<SpecificIterator, NodePtr>(const NodePtr node_ptr, const SpecificIterator &iter);
			friend bool btree::iter::operator||<SpecificIterator, NodePtr>(const NodePtr node_ptr, const SpecificIterator &iter);

			const NodePtr get() const { return ptr; }
		};

	}

}


template<template<typename> class DerivedIterator, typename Node>
inline typename btree::iter::Iterator<DerivedIterator, Node>::SpecificIterator &btree::iter::Iterator<DerivedIterator, Node>::operator=(const SpecificIterator &iter)
{
	ptr = iter.ptr;
	return *this;
};


template<template<typename> class DerivedIterator, typename Node>
inline typename btree::iter::Iterator<DerivedIterator, Node>::SpecificIterator &btree::iter::Iterator<DerivedIterator, Node>::operator=(const NodePtr node_ptr)
{
	ptr = node_ptr;
	return *this;
};


template<template<typename> class DerivedIterator, typename Node>
inline btree::iter::Iterator<DerivedIterator, Node>::operator bool() const
{
	return static_cast<bool>(ptr);
}


template<template<typename> class DerivedIterator, typename Node>
inline bool btree::iter::Iterator<DerivedIterator, Node>::operator!() const
{
	return !(static_cast<bool>(ptr));
}


template<template<typename> class DerivedIterator, typename Node>
inline bool btree::iter::Iterator<DerivedIterator, Node>::operator==(const SpecificIterator &iter) const
{
	return ptr == iter.ptr;
}


template<template<typename> class DerivedIterator, typename Node>
inline bool btree::iter::Iterator<DerivedIterator, Node>::operator!=(const SpecificIterator &iter) const
{
	return ptr != iter.ptr;
}


template<template<typename> class DerivedIterator, typename Node>
inline bool btree::iter::Iterator<DerivedIterator, Node>::operator&&(const SpecificIterator &iter) const
{
	return ptr && iter.ptr;
}


template<template<typename> class DerivedIterator, typename Node>
inline bool btree::iter::Iterator<DerivedIterator, Node>::operator||(const SpecificIterator &iter) const
{
	return ptr || iter.ptr;
}


template<template<typename> class DerivedIterator, typename Node>
inline bool btree::iter::Iterator<DerivedIterator, Node>::operator==(const NodePtr node_ptr) const
{
	return ptr == node_ptr;
}


template<template<typename> class DerivedIterator, typename Node>
inline bool btree::iter::Iterator<DerivedIterator, Node>::operator!=(const NodePtr node_ptr) const
{
	return ptr != node_ptr;
}


template<template<typename> class DerivedIterator, typename Node>
inline bool btree::iter::Iterator<DerivedIterator, Node>::operator&&(const NodePtr node_ptr) const
{
	return ptr && node_ptr;
}


template<template<typename> class DerivedIterator, typename Node>
inline bool btree::iter::Iterator<DerivedIterator, Node>::operator||(const NodePtr node_ptr) const
{
	return ptr || node_ptr;
}


template<typename SpecificIterator, typename NodePtr>
inline bool btree::iter::operator==(const NodePtr node_ptr, const SpecificIterator &iter)
{
	return node_ptr == iter.ptr;
}


template<typename SpecificIterator, typename NodePtr>
inline bool btree::iter::operator!=(const NodePtr node_ptr, const SpecificIterator &iter)
{
	return node_ptr != iter.ptr;
}


template<typename SpecificIterator, typename NodePtr>
inline bool btree::iter::operator&&(const NodePtr node_ptr, const SpecificIterator &iter)
{
	return node_ptr && iter.ptr;
}


template<typename SpecificIterator, typename NodePtr>
inline bool btree::iter::operator||(const NodePtr node_ptr, const SpecificIterator &iter)
{
	return node_ptr || iter.ptr;
}


#endif //SEARCHTREE_BASE_ITERATOR_H