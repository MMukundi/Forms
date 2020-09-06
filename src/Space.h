#pragma once
#include "common.h"
#include "Basis.h"
#include "Vector.h"
// #include "Basis.h"
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
    Space():basis(Basis<Component>())
    {
    }

    static Space Orthonormal(std::initializer_list<Vector<Component> > basis, int indexToPreserve = 0)
    {
        if (basis.size() == 0)
            return Space();
        std::vector<Vector<Component>> newBasisVectors = std::vector<Vector<Component>>();
        auto toSkip = basis.begin() + indexToPreserve;
        newBasisVectors.push_back(Vector<Component>::normalized(*toSkip));
        Space<Component> otherSpace = Space<Component>{newBasisVectors.at(0)};
        for (auto i = toSkip, e = basis.end(); i != e; i++)
        {
            Vector<Component> v = *i;
            Vector<Component> newV = Vector<Component>::normalized(v.clone().subtract(otherSpace.projectionOf(v)));
            newBasisVectors.push_back(newV);
            otherSpace = Space(newBasisVectors);
        }
        return otherSpace;
    }
    static Space Orthogonal(std::initializer_list<Vector<Component>> basis, int indexToPreserve = 0)
    {
        if (basis.size() == 0)
            return Space();
        std::vector<Vector<Component>> newBasisVectors = std::vector<Vector<Component>>();
        auto toSkip = basis.begin() + indexToPreserve;
        newBasisVectors.push_back(*toSkip);
        Space<Component> otherSpace = Space<Component>{newBasisVectors.at(0)};
        for (auto i = toSkip, e = basis.end(); i != e; i++)
        {
            if (i == toSkip)
                continue;
            Vector<Component> v = *i;
            Vector<Component> newV = v.clone().subtract(otherSpace.projectionOf(v));
            newBasisVectors.push_back(newV);
            otherSpace = Space(newBasisVectors);
        }
        return otherSpace;
    }

    Vector<Component> projectionOf(Vector<Component> v)
    {
        return v.clone().projectInto(*this);
    };
    std::string toString()
    {
        if (basis.spaceDimensions == 0)
            return "Space[]";
        std::stringstream s;
        s << "Space[";
        s << (basis[0].toString());
        for (int i = 1; i < basis.spaceDimensions; i++)
        {
            s << ", " << (basis[i].toString());
        }
        s << ("]");
        return s.str();
    }
};
