#pragma once
#include "common.h"
#include "Basis.h"
#include "Vector.h"
// #include "Basis.h"

template <typename>
class Basis;
template <typename>
class Vector;

template <typename Component = Number>
class Space
{
public:
    Basis<Component> basis;
    // const int vectorDimensions;
    // const int spaceDimensions;

    Space(std::initializer_list<Vector<Component> > basisList) : basis(basisList)
    {
    }
    Space(std::vector<Vector<Component> > basisV) : basis(basisV)
    {
    }
    Space(Basis<Component>b):basis(b){}
    Space():basis(Basis<Component>())
    {
    }
    //     static Basis<Component> Orthonormal(std::initializer_list<Vector<Component> > basis, int indexToPreserve = 0)
    // {}
    //     static Basis<Component> Orthogonal(std::initializer_list<Vector<Component>> basis, int indexToPreserve = 0)
    // {}

    Vector<Component> projectionOf(Vector<Component> v)
    {
        return v.clone().projectInto(*this);
    };
    std::size_t hash() const{
        return std::hash<Space<Component> >{}(*this);
    }
    
    std::string toString() const noexcept
    {
        return "Space with "+basis.toString();
    }
    friend std::ostream &operator<<(std::ostream &, Space<Component>);

    // friend void Basis<Component>::toOrthogonal(int indexToPreserve = 0);
    // friend void Basis<Component>::toOrthonormal(int indexToPreserve = 0);
};
template <typename Component>
std::ostream &operator<<(std::__1::basic_ostream<char, std::__1::char_traits<char>> &s, Space<Component> sp)
{
    return (s << sp.toString().c_str());
}

namespace std
{
   template <typename Component>
   struct hash<Space<Component> >
   {
      std::size_t operator()(Space<Component> const &v) const noexcept
      {
        return v.basis.hash();
      }
   };
};