#pragma once

#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <initializer_list>

typedef float Number;

// template<typename T>
// typename std::enable_if<std::is_arithmetic<T>::value, T>::type
// static unsigned long __hash(T n)
// {
//    return n * (913 * 19);
// }

// template<
//     typename T, //real type
//     typename = typename std::enable_if<!std::is_arithmetic<T>::value, T>::type
// >static unsigned long __hash(T t)
// {
//    return __hash(t._hash());
// }
template <class T,
          typename std::enable_if<!std::is_arithmetic<T>::value, T>::type = 0>
unsigned long __hash( T toHash)
{
   return __hash(toHash._hash());
}

template <class T,
          typename U= typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
unsigned long __hash( T toHash)
{
   return toHash * (913 * 19);
}