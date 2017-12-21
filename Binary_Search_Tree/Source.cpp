#include <windows.h>
#include "Header.h"
#include <iostream>    
#include <new>          


template< template<typename, typename> class DerivedNodeType, typename KeyType, typename ValueType>
class BaseNode {
private:
	
	using NodeType = DerivedNodeType<KeyType, ValueType>;
	using NodePtrType = NodeType*;

	BaseNode() = default;

protected:

	NodePtrType parent;
	NodePtrType right;
	NodePtrType left;

	explicit BaseNode(const KeyType &key, const ValueType &value) :
		parent(nullptr),
		right(nullptr),
		left(nullptr),
		key(key),
		value(value) {
		;
	}

	explicit BaseNode(const NodeType &node, const NodePtrType parent = nullptr) :
		parent(parent),
		right(nullptr),
		left(nullptr),
		key(node.key),
		value(node.value) {
		;
	}

	explicit BaseNode(const NodePtrType node, const NodePtrType parent = nullptr) :
		parent(parent),
		right(nullptr),
		left(nullptr),
		key(node->key),
		value(node->value) {
		;
	}

public:
	
	KeyType key;
	ValueType value;

};


template<typename NodeType>
class InorderIterator {
private:

	using IteratorType = InorderIterator<NodeType>;
	using NodePtrType = NodeType*;

	NodePtrType ptr;

public:

	explicit InorderIterator(const NodePtrType ptr = nullptr) : ptr(ptr) { ; }

	InorderIterator(const IteratorType &iter) : ptr(iter.ptr), { ; }

	const IteratorType &operator=(const IteratorType &iter) {
		ptr = iter.ptr;
		return *this;
	}

	const IteratorType &operator=(const NodePtrType node_ptr) {
		ptr = node_ptr;
		return *this;
	}

	IteratorType &operator++();

	IteratorType operator++(int);

	IteratorType &operator--();

	IteratorType operator--(int);

};

template<typename NodeType>
typename InorderIterator<NodeType>::IteratorType &InorderIterator<NodeType>::operator++()
{
	if (!ptr) return *this;

	else if (ptr->right) {
		
		ptr = ptr->right;
		
		while (ptr->left) 
			ptr = ptr->left;
	}
	else {
		
		while (ptr->parent && (ptr == ptr->parent->right)) 
			ptr = ptr->parent;
		
		if (!(ptr->parent))
			ptr = nullptr;
	}

	return *this;
}

template<typename NodeType>
typename InorderIterator<NodeType>::IteratorType InorderIterator<NodeType>::operator++(int)
{
	NodePtrType previous_ptr = ptr;

	if (!ptr) return *this;

	else if (ptr->right) {

		ptr = ptr->right;

		while (ptr->left)
			ptr = ptr->left;
	}
	else {

		while (ptr->parent && (ptr == ptr->parent->right))
			ptr = ptr->parent;

		if (!(ptr->parent))
			ptr = nullptr;
	}

	return IteratorType(previous_ptr);
}


template< template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
class BinarySearchTree {
private:

	using NodeType = TreeNodeType<KeyType, ValueType>;
	using NodePtrType = NodeType*;
	using TreeType = BinarySearchTree<TreeNodeType, KeyType, ValueType>;

protected:

	NodePtrType head;

	BinarySearchTree() : head(nullptr) { ; }

	explicit BinarySearchTree(const KeyType &key, const ValueType &value) { head = new NodeType(key, value); }

	explicit BinarySearchTree(const TreeType &tree);

	~BinarySearchTree();

public:

	const NodePtrType find(const KeyType &key) const;

	const NodePtrType find(const KeyType *key) const;

};


template< template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
BinarySearchTree<TreeNodeType, KeyType, ValueType>::BinarySearchTree(const TreeType &tree)
{
	if (!tree.head) {
		head = nullptr;
		return;
	}

	enum {
		RIGHT_SUB_TREE,
		LEFT_SUB_TREE,
		PARENT
	} from = PARENT;

	const NodePtrType ptr = tree.head;
	head = new NodeType(ptr);

	while (ptr->parent || from) {

		switch (from) {

		case RIGHT_SUB_TREE:

			from = (ptr == ptr->parent->left) ? LEFT_SUB_TREE : RIGHT_SUB_TREE;
			ptr = ptr->parent;
			head = head->parent;
			break;

		case LEFT_SUB_TREE:

			if (ptr->right) {
				from = PARENT;
				ptr = ptr->right;
				head = head->right = new NodeType(ptr, head);
			}
			else from = RIGHT_SUB_TREE;
			break;

		case PARENT:

			if (ptr->left) {
				from = PARENT;
				ptr = ptr->left;
				head = head->left = new NodeType(ptr, head);
			}
			else from = LEFT_SUB_TREE;
			break;
		}
	}
}


template< template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
BinarySearchTree<TreeNodeType, KeyType, ValueType>::~BinarySearchTree()
{
	while (head->parent || head->left || head->right) {

		if (head->left) head = head->left;

		else if (head->right) head = head->right;

		else {

			head = head->parent;

			if (head->left) {
				delete head->left;
				head->left = nullptr;
			}
			else {
				delete head->right;
				head->right = nullptr;
			}
		}
	}

	delete head;
}


template< template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
const typename BinarySearchTree<TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<TreeNodeType, KeyType, ValueType>::find(const KeyType &key) const
{
	const NodePtrType ptr = head;
	
	while (ptr && (key != ptr->key) ) 
		ptr = (key < ptr->key) ? ptr->left : ptr->right;
	

	return ptr;
}


template< template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
const typename BinarySearchTree<TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<TreeNodeType, KeyType, ValueType>::find(const KeyType *key) const
{
	const NodePtrType ptr = head;

	while (ptr && (*key != ptr->key)) 
		ptr = (*key < ptr->key) ? ptr->left : ptr->right;

	return ptr;
}


template<typename KeyType, typename ValueType>
class SimpleNode : public BaseNode<SimpleNode, KeyType, ValueType> {
private:

	friend class BinarySearchTree<::SimpleNode, KeyType, ValueType>;

	using BaseNodeType = BaseNode<::SimpleNode, KeyType, ValueType>;
	using NodeType = SimpleNode<KeyType, ValueType>;
	using NodePtrType = NodeType*;

	SimpleNode() = default;

protected:

	explicit SimpleNode(const KeyType &key, const ValueType &value) : BaseNodeType(key, value) { ; }

	explicit SimpleNode(const NodeType &node, const NodePtrType parent = nullptr) : BaseNodeType(node, parent) { ; }

	explicit SimpleNode(const NodePtrType node, const NodePtrType parent = nullptr) : BaseNodeType(node, parent) { ; }

};


class Point2D {
public:

	int x;
	int y;

	Point2D() : x(0), y(0) {
		std::cout << "New point2d default constructor" << std::endl;
	}

	Point2D(int x, int y) : x(x), y(y) {
		std::cout << "New point2d constructor" << std::endl;
	}

	Point2D(const Point2D &obj) : x(obj.x), y(obj.y) {
		std::cout << "Copy point2d constructor" << std::endl;
	}

	~Point2D() {
		std::cout << "Destructor point2d " << std::endl;
	}
};

Point2D foo()
{
	int a = 32;
	std::cout << a << std::endl;
	Point2D c(10, 10);
	return c;
}

int main() {

	std::cout << foo().x << std::endl;

	Sleep(5000);
	return 0;
}

