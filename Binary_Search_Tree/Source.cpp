#include <windows.h>
#include "Header.h"
#include <iostream>    
#include <new>    
#include <type_traits>
#include <iostream>
#include <string>


template<typename T>
struct has_lt
{
private:

	static void detect(...);

	template<typename U>
	static decltype(static_cast<bool>(std::declval<U>() < std::declval<U>())) detect(const U &);

public:

	static constexpr bool value = std::is_same<bool, decltype(detect(std::declval<T>()))>::value;
};


template<typename T>
struct has_gt
{
private:

	static void detect(...);

	template<typename U>
	static decltype(static_cast<bool>(std::declval<U>() > std::declval<U>())) detect(const U &);

public:

	static constexpr bool value = std::is_same<bool, decltype(detect(std::declval<T>()))>::value;
};


template<typename T>
struct has_eq
{
private:

	static void detect(...);

	template<typename U>
	static decltype(static_cast<bool>(std::declval<U>() == std::declval<U>())) detect(const U &);

public:

	static constexpr bool value = std::is_same<bool, decltype(detect(std::declval<T>()))>::value;
};


template<typename T>
struct has_neq
{
private:

	static void detect(...);

	template<typename U>
	static decltype(static_cast<bool>(std::declval<U>() != std::declval<U>())) detect(const U &);

public:

	static constexpr bool value = std::is_same<bool, decltype(detect(std::declval<T>()))>::value;
};


template<typename T>
struct has_lt_eq
{
public:
	static constexpr bool value = (has_lt<T>::value && has_eq<T>::value);
};


template<typename T>
struct has_lt_neq
{
public:
	static constexpr bool value = (has_lt<T>::value && !has_eq<T>::value && has_neq<T>::value);
};


template<typename T>
struct has_gt_eq
{
public:
	static constexpr bool value = (!has_lt<T>::value && has_gt<T>::value && has_eq<T>::value);
};


template<typename T>
struct has_gt_neq
{
public:
	static constexpr bool value = (!has_lt<T>::value && has_gt<T>::value && !has_eq<T>::value && has_neq<T>::value);
};


template<typename T>
struct has_nothing
{
public:
	static constexpr bool value = (!has_lt_eq<T>::value && !has_lt_neq<T>::value && !has_gt_eq<T>::value && !has_gt_neq<T>::value);
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

	bool operator==(const Point2D &point) const {
		return static_cast<bool>((x == point.x) && (y == point.y));
	}
	
	bool operator<(const Point2D &point) const {
		return static_cast<bool>(x < point.x);
	}
	
};


template<typename T, typename Enable = void> 
class A;

template<typename T>
class A<T, typename std::enable_if<has_nothing<T>::value>::type> {
public:
	void foo(const T &t) {
		static_assert(false, "ASSERTION");
	}
};

template<typename T>
class A<T, typename std::enable_if<has_lt_eq<T>::value>::type> {
public:
	void foo(const T &t) {
		std::cout << "Has < and ==" << std::endl;
	}
};


template<typename T>
class A<T, typename std::enable_if<has_lt_neq<T>::value>::type> {
public:
	void foo(const T &t) {
		std::cout << "Has < and !=" << std::endl;
	}
};


template<typename T>
class A<T, typename std::enable_if<has_gt_eq<T>::value>::type> {
public:
	void foo(const T &t) {
		std::cout << "Has > and ==" << std::endl;
	}
};


template<typename T>
class A<T, typename std::enable_if<has_gt_neq<T>::value>::type> {
public:
	void foo(const T &t) {
		std::cout << "Has > and !=" << std::endl;
	}
};





int main() 
{
	Point2D point(10, 20);

	A<Point2D> a;
	a.foo(point);
	
	Sleep(2000);
	return 0;
}


