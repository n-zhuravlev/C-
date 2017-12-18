#include <windows.h>
#include "Header.h"
#include <iostream>    
#include <new>          


template< template<typename, typename> class DerivedNodeType, typename KeyType, typename ValueType>
class BaseNode {
private:

	BaseNode() = default;

protected:

	using BaseNodeType = BaseNode<DerivedNodeType, KeyType, ValueType>;
	using NodeType = DerivedNodeType<KeyType, ValueType>;
	using NodePtrType = NodeType*;

	BaseNode(const KeyType &key, const ValueType &value) : key(key), value(value) {
		right = nullptr;
		left = nullptr;
	}

	BaseNode(const BaseNodeType &node) :
		right(node.right),
		left(node.left),
		key(node.key),
		value(node.value) {
		;
	}

	BaseNode(const BaseNodeType &node, NodePtrType right, NodePtrType left) :
		right(right),
		left(left),
		key(node.key),
		value(node.value) {
		;
	}

public:

	NodePtrType parent;
	NodePtrType right;
	NodePtrType left;
	KeyType key;
	ValueType value;

};


template<typename KeyType, typename ValueType>
class SimpleNode : public BaseNode<SimpleNode, KeyType, ValueType> {
private:
	
	using BaseNodeType = BaseNode<::SimpleNode, KeyType, ValueType>;
	using NodeType = SimpleNode<KeyType, ValueType>;
	using NodePtrType = NodeType*;

	SimpleNode() = default;

public:

	NodePtrType parent;

	SimpleNode(const KeyType &key, const ValueType &value) : BaseNodeType(key, value) {
		parent = nullptr;
	}

	SimpleNode(const NodeType &node) : BaseNodeType(node), parent(node.parent) { ; }

	SimpleNode(const NodeType &node, NodePtrType parent) : BaseNodeType(node), parent(parent) { ; }

};


template< template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
class BinarySearchTree {
private:

	using NodeType = TreeNodeType<KeyType, ValueType>;
	using NodePtrType = NodeType*;
	using TreeType = BinarySearchTree<TreeNodeType, KeyType, ValueType>;

protected:

	BinarySearchTree() : head(nullptr) { ; }

	BinarySearchTree(const KeyType &key, const ValueType &value) {
		head = new NodeType(key, value);
	}

	BinarySearchTree(const TreeType &tree);

	~BinarySearchTree();

public:

	NodePtrType head;

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




class Point2D {
	int x;
	int y;

public:

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



int main() {

	Point2D simple_point(10, 20);
	SimpleNode<Point2D, Point2D> node(simple_point, simple_point);
	SimpleNode<Point2D, Point2D> node1(node, node.left);
	//    ptr = (ptr->left)?(ptr->left):(ptr->right?ptr->right:ptr->parent);
	auto a = 3;

	std::cout << (bool)nullptr << std::endl;

	return 0;
}
