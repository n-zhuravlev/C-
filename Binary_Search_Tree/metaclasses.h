#ifndef SEARCHTREE_METACLASSES_H
#define SEARCHTREE_METACLASSES_H

#include <type_traits>

// class has operator <
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


// class has operator >
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


// class has operator ==
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


// class has operator !=
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

#endif //SEARCHTREE_METACLASSES_H