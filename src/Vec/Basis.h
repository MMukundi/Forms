#pragma once
#include "common.h"
#include "Vector.h"
#include "Space.h"

template <typename Component>
class Basis
{
    std::vector<Vector<Component>> vectors;

public:
    int spaceDimensions;
    int vectorDimensions;
    Basis(std::initializer_list<Vector<Component>> vecs) : vectors(vecs), vectorDimensions(vecs.begin()->dimensions), spaceDimensions(vecs.size())
    {
        if (spaceDimensions == 0)
        {
            vectors.resize(0);
            vectorDimensions = 0;
        }
    }
    Basis(std::vector<Vector<Component>> vecs) : vectors(vecs), vectorDimensions(vecs.at(0).dimensions), spaceDimensions(vecs.size())
    {
        if (spaceDimensions == 0)
        {
            vectors.resize(0);
            vectorDimensions = 0;
        }
    }
    Basis()
    {
        vectors.resize(0);
        vectorDimensions = 0;
        spaceDimensions = 0;
    }
    static Basis<Component> toOrthonormal(Basis<Component> b, int indexToPreserve = 0)
    {
        return b.clone().toOrthonormal(indexToPreserve);
    }
    static Basis<Component> toOrthogonal(Basis<Component> b, int indexToPreserve = 0)
    {
        return b.clone().toOrthogonal(indexToPreserve);
    }

    Basis<Component> toOrthonormal(int indexToPreserve = 0)
    {
        if (this->spaceDimensions == 0)
        {
            return *this;
        }
        if (indexToPreserve != 0)
        {
            Vector<Component> temp = vectors[0];
            vectors[0] = vectors[indexToPreserve];
            vectors[indexToPreserve] = temp;
        }
        for (int i = 0; i < spaceDimensions; i++)
        {
            for (int j = 0; j < i; j++)
            {
                vectors[i].subtract(vectors[i].clone().projectOnto(vectors[j]));
            }
            vectors[i].normalize();
        }
        if (indexToPreserve != 0)
        {
            Vector<Component> temp = vectors[0];
            vectors[0] = vectors[indexToPreserve];
            vectors[indexToPreserve] = temp;
        }
        return *this;
    }
    Basis<Component> toOrthogonal(int indexToPreserve = 0)
    {
        if (this->spaceDimensions == 0)
        {
            return *this;
        }
        if (indexToPreserve != 0)
        {
            Vector<Component> temp = vectors[0];
            vectors[0] = vectors[indexToPreserve];
            vectors[indexToPreserve] = temp;
        }
        for (int i = 0; i < spaceDimensions; i++)
        {
            for (int j = 0; j < i; j++)
            {
                vectors[i].subtract(vectors[i].clone().projectOnto(vectors[j]));
            }
            // vectors[i].normalize();
        }
        if (indexToPreserve != 0)
        {
            Vector<Component> temp = vectors[0];
            vectors[0] = vectors[indexToPreserve];
            vectors[indexToPreserve] = temp;
        }
        return *this;
    }

    static Basis<Component> standardBasis(unsigned int dimensions)
    {
        if (dimensions == 0)
        {
            return Basis();
        }
        std::vector<Vector<Component>> basisVectors = std::vector<Vector<Component>>(dimensions);
        for (int i = 0; i < dimensions; i++)
        {
            std::vector<Component> comps = std::vector<Component>(dimensions);
            comps[i] = 1;
            basisVectors[i] = comps;
        }
        return basisVectors;
    }
    std::size_t hash() const
    {
        return std::hash<Basis<Component>>{}(*this);
    }
    auto begin() const noexcept
    {
        return vectors.begin();
    }
    auto end() const noexcept
    {
        return vectors.end();
    }
    Vector<Component> getVector(int i)
    {
        return vectors.at(i);
    }
    Vector<Component> operator[](int i)
    {
        return vectors.operator[](i);
    }
    Basis<Component> clone() const noexcept
    {
        std::vector<Vector<Component>> newVectors = std::vector<Vector<Component>>(spaceDimensions);
        int i = 0;
        for (Vector<Component> v : *this)
        {
            newVectors[i++] = v;
        }
        return newVectors;
    }
    std::string toString() const noexcept
    {
        if (spaceDimensions == 0)
            return std::string("Basis[]");
        std::stringstream s;
        s << "Basis[";
        // s.append(String.format("%.2f", components[0]));
        s << vectors[0].toString();
        for (int i = 1; i < spaceDimensions; i++)
        {
            s << ", " << vectors[i].toString();
            //s.append(String.format(",%.2f", components[i]));
        }
        s << ("]");
        return s.str();
    }

    friend std::ostream &operator<<(std::ostream &, Basis<Component>);
    friend class Space<Component>;
    // Basis<Component>& operator=(Basis<Component>&){

    // }
};
template <typename Component>
std::ostream &operator<<(std::__1::basic_ostream<char, std::__1::char_traits<char>> &s, Basis<Component> b)
{
    return (s << b.toString().c_str());
}
namespace std
{
    template <typename Component>
    struct hash<Basis<Component>>
    {
        size_t operator()(Basis<Component> const &b) const noexcept
        {
            size_t h = 301;
            auto hasher = hash<Vector<Component>>{};
            int i = 0;
            for (Vector<Component> v : b)
            {
                h = h ^ (hasher(v) << (i++));
            }
            return h;
        }
    };
}; // namespace std
