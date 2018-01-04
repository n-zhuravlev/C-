#include <iostream>
#include "tree.h"


/*
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
*/





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

    void foo() { std::cout << "foo point 2D" << std::endl; }

    float operator<(const Point2D& point) { return 1.f; }
};




int main()
{
    Point2D point(10, 20);

    return 0;
}

