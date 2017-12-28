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


template< template<typename> class DerivedIteratorType, typename NodeType>
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

	operator bool() const {
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

	friend bool operator==(const NodePtrType ptr_, const IteratorType &iter);

	bool operator!=(const IteratorType &iter) const {
		return ptr != iter.ptr;
	}

	bool operator!=(const NodePtrType ptr_) const {
		return ptr != ptr_;
	}

	friend bool operator!=(const NodePtrType ptr_, const IteratorType &iter);

	bool operator&&(const IteratorType &iter) const {
		return ptr && iter.ptr;
	}

	bool operator&&(const NodePtrType ptr_) const {
		return ptr && ptr_;
	}

	friend bool operator&&(const NodePtrType ptr_, const IteratorType &iter);

	bool operator||(const IteratorType &iter) const {
		return ptr || iter.ptr;
	}

	bool operator||(const NodePtrType ptr_) const {
		return ptr || ptr_;
	}

	friend bool operator||(const NodePtrType ptr_, const IteratorType &iter);

	const NodePtrType get() const {
		return ptr;
	}
};


template< template<typename> class DerivedIteratorType, typename NodeType>
inline bool operator==(const typename Iterator<DerivedIteratorType, NodeType>::NodePtrType ptr_, const typename Iterator<DerivedIteratorType, NodeType>::IteratorType &iter)
{
	return ptr_ == iter.ptr;
}


template< template<typename> class DerivedIteratorType, typename NodeType>
inline bool operator!=(const typename Iterator<DerivedIteratorType, NodeType>::NodePtrType ptr_, const typename Iterator<DerivedIteratorType, NodeType>::IteratorType &iter)
{
	return ptr_ != iter.ptr;
}


template< template<typename> class DerivedIteratorType, typename NodeType>
inline bool operator&&(const typename Iterator<DerivedIteratorType, NodeType>::NodePtrType ptr_, const typename Iterator<DerivedIteratorType, NodeType>::IteratorType &iter)
{
	return ptr_ && iter.ptr;
}


template< template<typename> class DerivedIteratorType, typename NodeType>
inline bool operator||(const typename Iterator<DerivedIteratorType, NodeType>::NodePtrType ptr_, const typename Iterator<DerivedIteratorType, NodeType>::IteratorType &iter)
{
	return ptr_ || iter.ptr;
}


template<typename NodeType>
class InorderIterator : public Iterator<InorderIterator, NodeType> {
private:

	using BaseIteratorType = Iterator<::InorderIterator, NodeType>;
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
typename InorderIterator<NodeType>::IteratorType &InorderIterator<NodeType>::operator++()
{
	if (ptr) {

		if (ptr->right) {

			ptr = ptr->right;

			while (ptr->left)
				ptr = ptr->left;
		}
		else {

			while (ptr->parent && (ptr == ptr->parent->right))
				ptr = ptr->parent;

			ptr = ptr->parent;
		}
	}

	return *this;
}

template<typename NodeType>
typename InorderIterator<NodeType>::IteratorType InorderIterator<NodeType>::operator++(int)
{
	NodePtrType previous_ptr = ptr;

	if (ptr) {

		if (ptr->right) {

			ptr = ptr->right;

			while (ptr->left)
				ptr = ptr->left;
		}
		else {

			while (ptr->parent && (ptr == ptr->parent->right))
				ptr = ptr->parent;

			ptr = ptr->parent;
		}
	}

	return IteratorType(previous_ptr);
}


template<typename NodeType>
typename InorderIterator<NodeType>::IteratorType &InorderIterator<NodeType>::operator--()
{

	if (ptr) {

		if (ptr->left) {

			ptr = ptr->left;

			while (ptr->right)
				ptr = ptr->right;
		}
		else {

			while (ptr->parent && (ptr == ptr->parent->left))
				ptr = ptr->parent;

			ptr = ptr->parent;
		}
	}

	return *this;
}


template<typename NodeType>
typename InorderIterator<NodeType>::IteratorType InorderIterator<NodeType>::operator--(int)
{
	NodePtrType previous_ptr = ptr;

	if (ptr) {

		if (ptr->left) {

			ptr = ptr->left;

			while (ptr->right)
				ptr = ptr->right;
		}
		else {

			while (ptr->parent && (ptr == ptr->parent->left))
				ptr = ptr->parent;

			ptr = ptr->parent;
		}
	}

	return IteratorType(previous_ptr);
}


template<typename NodeType>
class PreorderIterator : public Iterator<PreorderIterator, NodeType> {
private:

	using BaseIteratorType = Iterator<::PreorderIterator, NodeType>;
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
typename PreorderIterator<NodeType>::IteratorType &PreorderIterator<NodeType>::operator++()
{
	if (ptr) {

		if (ptr->left)
			ptr = ptr->left;

		else if (ptr->right)
			ptr = ptr->right;

		else {

			while (true) {

				if (ptr->parent == nullptr) {
					ptr = nullptr;
					break;
				}

				else if ( (ptr->parent->right == ptr) || (ptr->parent->right == nullptr) )
					ptr = ptr->parent;

				else {
					ptr = ptr->parent->right;
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
	NodePtrType previous_ptr = ptr;

	if (ptr) {

		if (ptr->left)
			ptr = ptr->left;

		else if (ptr->right)
			ptr = ptr->right;

		else {

			while (true) {

				if (ptr->parent == nullptr) {
					ptr = nullptr;
					break;
				}

				else if ((ptr->parent->right == ptr) || (ptr->parent->right == nullptr))
					ptr = ptr->parent;

				else {
					ptr = ptr->parent->right;
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
	if (ptr) {

		if (ptr->parent && (ptr->parent->right == ptr) && ptr->parent->left) {

			ptr = ptr->parent->left;

			while (true) {

				if (ptr->right)
					ptr = ptr->right;

				else if (ptr->left)
					ptr = ptr->left;

				else break;
			}
		}
		else ptr = ptr->parent;
	}

	return *this;
}


template<typename NodeType>
typename PreorderIterator<NodeType>::IteratorType PreorderIterator<NodeType>::operator--(int)
{
	NodePtrType previous_ptr = ptr;

	if (ptr) {

		if (ptr->parent && (ptr->parent->right == ptr) && ptr->parent->left) {

			ptr = ptr->parent->left;

			while (true) {

				if (ptr->right)
					ptr = ptr->right;

				else if (ptr->left)
					ptr = ptr->left;

				else break;
			}
		}
		else ptr = ptr->parent;
	}

	return IteratorType(previous_ptr);
}


template<typename NodeType>
class PostorderIterator : public Iterator<PostorderIterator, NodeType> {
private:

	using BaseIteratorType = Iterator<::PostorderIterator, NodeType>;
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


template<typename NodeType>
typename PostorderIterator<NodeType>::IteratorType &PostorderIterator<NodeType>::operator++()
{
	if (ptr) {

		if ((ptr->parent == nullptr) || (ptr->parent->right == ptr) || (ptr->parent->right == nullptr))
			ptr = ptr->parent;
		
		else {

			ptr = ptr->parent->right;

			while (true) {

				if (ptr->left)
					ptr = ptr->left;

				else if (ptr->right)
					ptr = ptr->right;

				else break;
			}
		}
	}

	return *this;
}

template<typename NodeType>
typename PostorderIterator<NodeType>::IteratorType PostorderIterator<NodeType>::operator++(int)
{
	NodePtrType previous_ptr = ptr;

	if (ptr) {

		if ((ptr->parent == nullptr) || (ptr->parent->right == ptr) || (ptr->parent->right == nullptr))
			ptr = ptr->parent;

		else {

			ptr = ptr->parent->right;

			while (true) {

				if (ptr->left)
					ptr = ptr->left;

				else if (ptr->right)
					ptr = ptr->right;

				else break;
			}
		}
	}

	return IteratorType(previous_ptr);
}


template<typename NodeType>
typename PostorderIterator<NodeType>::IteratorType &PostorderIterator<NodeType>::operator--()
{
	if (ptr) {

		if (ptr->right) 
			ptr = ptr->right;

		else if (ptr->left) 
			ptr = ptr->left;

		else {

			while (true) {

				if (ptr->parent == nullptr) {
					ptr = nullptr;
					break;
				}
				else if ( (ptr->parent->left == ptr) || (ptr->parent->left == nullptr) )
					ptr = ptr->parent;

				else {
					ptr = ptr->parent->left;
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
	NodePtrType previous_ptr = ptr;

	if (ptr) {

		if (ptr->right)
			ptr = ptr->right;

		else if (ptr->left)
			ptr = ptr->left;

		else {

			while (true) {

				if (ptr->parent == nullptr) {
					ptr = nullptr;
					break;
				}
				else if ((ptr->parent->left == ptr) || (ptr->parent->left == nullptr))
					ptr = ptr->parent;

				else {
					ptr = ptr->parent->left;
					break;
				}
			}
		}
	}

	return IteratorType(previous_ptr);
}



template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
class BinarySearchTree {
private:

	using NodeType = TreeNodeType<KeyType, ValueType>;
	using NodePtrType = NodeType*;
	using TreeType = DerivedTreeType<KeyType, ValueType>;

protected:

	NodePtrType head;

	BinarySearchTree() :
		head(nullptr) {
		;
	}

	explicit BinarySearchTree(const KeyType &key, const ValueType &value) {
		head = new NodeType(key, value);
	}

	explicit BinarySearchTree(const KeyType *key, const ValueType *value) {
		head = new NodeType(*key, *value);
	}

	BinarySearchTree(const BinarySearchTree &tree);

	~BinarySearchTree();

public:

	TreeType &operator=(const TreeType &tree);

	const NodePtrType min_key() const;
	const NodePtrType max_key() const;
	const NodePtrType head_key() const;

	const NodePtrType find(const KeyType &key) const;
	const NodePtrType find(const KeyType *key) const;

};


template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::BinarySearchTree(const BinarySearchTree &tree)
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


template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::~BinarySearchTree()
{
	if (head) {

		while (true) {

			if (head->left) 
				head = head->left;

			else if (head->right) 
				head = head->right;

			else if (head->parent) {

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
			else break;
		}

		delete head;
	}
}


template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::TreeType &BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::operator=(const BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::TreeType &tree)
{
	if (this != &tree) {

		// delete current tree nodes (see destructor)
		if (head) {

			while (true) {

				if (head->left)
					head = head->left;

				else if (head->right)
					head = head->right;

				else if (head->parent) {

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
				else break;
			}

			delete head;
			head = nullptr;
		}

		// copy new nodes if needed
		if (tree.head) {
			
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
	}

	return *this;
}


template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
const typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::min_key() const
{
	if (!head)
		return nullptr;

	const NodePtrType ptr = head;

	while (ptr->left)
		ptr = ptr->left;

	return ptr;
}


template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
const typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::max_key() const
{
	if (!head)
		return nullptr;

	const NodePtrType ptr = head;

	while (ptr->right)
		ptr = ptr->right;

	return ptr;
}


template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
inline const typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::head_key() const
{
	return head;
}


template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
const typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::find(const KeyType &key) const
{
	const NodePtrType ptr = head;

	while (ptr && (key != ptr->key))
		ptr = (key < ptr->key) ? ptr->left : ptr->right;

	return ptr;
}


template< template<typename, typename> class DerivedTreeType, template<typename, typename> class TreeNodeType, typename KeyType, typename ValueType>
const typename BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::NodePtrType BinarySearchTree<DerivedTreeType, TreeNodeType, KeyType, ValueType>::find(const KeyType *key) const
{
	const NodePtrType ptr = head;

	while (ptr && (*key != ptr->key))
		ptr = (*key < ptr->key) ? ptr->left : ptr->right;

	return ptr;
}



template<typename KeyType, typename ValueType>
class SimpleNode : public BaseNode<SimpleNode, KeyType, ValueType> {
private:

	using BaseNodeType = BaseNode<::SimpleNode, KeyType, ValueType>;
	using NodeType = SimpleNode<KeyType, ValueType>;
	using NodePtrType = NodeType*;

	//friend class BinarySearchTree<::SimpleNode, KeyType, ValueType>;
	//friend class InorderIterator<::SimpleNode>;

	SimpleNode() = default;

protected:

	explicit SimpleNode(const KeyType &key, const ValueType &value) :
		BaseNodeType(key, value) {
		;
	}

	SimpleNode(const SimpleNode &node, const NodePtrType parent = nullptr) :
		BaseNodeType(node, parent) {
		;
	}

	explicit SimpleNode(const NodePtrType node, const NodePtrType parent = nullptr) :
		BaseNodeType(node, parent) {
		;
	}
};



template<typename KeyType, typename ValueType>
class SimpleTree : public BinarySearchTree<SimpleTree, SimpleNode, KeyType, ValueType> {
private:
	
	using BaseTreeType = BinarySearchTree<::SimpleTree, SimpleNode, KeyType, ValueType>;

public:

	SimpleTree() :
		BaseTreeType() {
		;
	}

	explicit SimpleTree(const KeyType &key, const ValueType &value) :
		BaseTreeType(key, value) {
		;
	}

	explicit SimpleTree(const KeyType *key, const ValueType *value) :
		BaseTreeType(key, value) {
		;
	}

	SimpleTree(const SimpleTree &tree) :
		BaseTreeType(tree) {
		;
	}

	void add(const KeyType &key, const ValueType &value);
	void add(const KeyType *key, const ValueType *value);
	void add(const KeyType &key, const ValueType *value);
	void add(const KeyType *key, const ValueType &value);
	void remove(const KeyType &key);
	void remove(const KeyType *key);

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

	int *a = nullptr;
	
	std::cout << foo().x << std::endl;

	Sleep(2000);
	return 0;
}


