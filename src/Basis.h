#pragma once
#include "common.h"
#include "Vector.h"

template <typename Component>
class Basis : public std::vector<Vector<Component>>
{
public:
    int spaceDimensions;
    int vectorDimensions;
    Basis(std::initializer_list<Vector<Component>> _basis) : std::vector<Vector<Component>>(_basis) , vectorDimensions(_basis.begin()->dimensions) , spaceDimensions(_basis.size())
    {
        if (spaceDimensions == 0)
        {
            vectorDimensions = 0;
        }
    }
    Basis(std::vector<Vector<Component>> _basis) : std::vector<Vector<Component>>(_basis) , vectorDimensions(_basis.at(0).dimensions) , spaceDimensions(_basis.size())
    {
        if (spaceDimensions == 0)
        {
            vectorDimensions = 0;
        }
    }
    Basis()
    {
        this->resize(0);
        vectorDimensions = 0;
        spaceDimensions = 0;
    }
};