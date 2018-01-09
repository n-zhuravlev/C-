#include <iostream>
#include "tree.cpp"



class Point2D {
public:

    int x;
    int y;

    Point2D() : x(0), y(0) {
        std::cout << "New point2d default constructor" << std::endl;
    }

    Point2D(int x, int y) : x(x), y(y) {
        std::cout << "New point2d constructor with x:" << x << " and y:" << y << std::endl;
    }

    Point2D(const Point2D &obj) : x(obj.x), y(obj.y) {
        std::cout << "Copy point2d constructor" << std::endl;
    }

    ~Point2D() {
        std::cout << "Destructor point2d " << std::endl;
    }

    void foo() { std::cout << "foo point 2D" << std::endl; }

    bool operator<(const Point2D& point) const{
        return static_cast<bool>(x < point.x);
    }

    bool operator>(const Point2D& point) const{
        return static_cast<bool>(x > point.x);
    }

    bool operator==(const Point2D& point) const{
        return static_cast<bool>((x == point.x) && (y == point.y));
    }

    bool operator!=(const Point2D& point) const{
        return static_cast<bool>((x != point.x) && (y != point.y));
    }
};


int main()
{
    Point2D point(10, 20);
    btree::SimpleTree<Point2D, Point2D> tree;


    tree.add(point, point);
    tree.add(point, point);
    tree.add(point, point);
    tree.add(point, point);

    return 0;
}

