#pragma once
#include "common.h"

template <typename>
class Space;

// <Component> must be defined as a Field
template <typename Component = Number>
class Vector
{
   // typedef Component Component;
   std::vector<Component> components;

public:
   int dimensions;
   typedef Component componentType;
   typedef Component &cRef;
   typedef Vector<Component> Vector_C;
   typedef Vector_C &AbstractVectorRef;
   // const int dimensions;

   Vector(std::initializer_list<Component> l) : dimensions(l.size())
   {
      components = l;
   }
   Vector(std::vector<Component> l) : dimensions(l.size())
   {
      components = l;
   }
   // Vector(const Vector<Component> &v) : dimensions(v.dimensions)
   // {
   //    components.resize(v.dimensions);
   //    auto tc = components.begin();
   //    auto c = v.components.begin();
   //    auto e = v.components.end();

   //    while (c != e)
   //    {
   //       *tc = *(c++);
   //    }
   // }
   Vector() : dimensions(0)
   {
   }

   Component magnitude()
   {
      Component sum = 0;
      for (Component n : components)
         sum += n * n;
      return sqrt(sum);
   }
   Component magnitudeSquared()
   {
      Component sum = 0;
      for (Component n : components)
         sum += n * n;
      return sum;
   }

   Vector<Component> &add(Vector_C v)
   {
      if (dimensions != v.dimensions)
         throw("Dimension mismatch");
      for (int i = 0; i < dimensions; i++)
         components[i] += v.components[i];
      return *this;
   }

   Vector<Component> &subtract(Vector_C v)
   {
      if (dimensions != v.dimensions)
         throw("Dimension mismatch");
      for (int i = 0; i < dimensions; i++)
         components[i] -= v.components[i];
      return *this;
   };
   Vector<Component> &scale(Component n)
   {
      if (dimensions != dimensions)
         throw("Dimension mismatch");

      for (int i = 0; i < dimensions; i++)
         components[i] *= n;

      return *this;
   }

   Component dot(Vector_C v)
   {
      if (dimensions != v.dimensions)
         throw("Dimension mismatch");
      Component product = 0;
      for (int i = 0; i < dimensions; i++)
         product += components[i] * v.components[i];
      return product;
   }

   Vector_C cross(Vector_C v);

   Vector<Component> &projectOnto(Vector_C v)
   {
      if (dimensions != v.dimensions)
         throw("Dimension mismatch");
      Component dProduct = components[0] * v.components[0];
      Component magSquaredV = v.components[0] * v.components[0];

      for (int i = 1; i < dimensions; i++)
      {
         dProduct += components[i] * v.components[i];
         magSquaredV += v.components[i] * v.components[i];
         // std::cout<<v.components[i]<<"=>"<<magSquaredV<<std::endl;
      }
      Component scaleVBy = dProduct / magSquaredV;

      for (int i = 0; i < dimensions; i++)
      {
         components[i] = v.components[i] * scaleVBy;
      }

      return *this;
   }
   Vector<Component> projectInto(Space<Component> s)
   {
      if (s.basis.vectorDimensions != dimensions)
         throw("Dimension mismatch");
      std::vector<Component> projectionComponents = std::vector<Component>(s.basis.vectorDimensions);
      // printf("Projecting %s into %s\n", toString().c_str(), s.toString().c_str());
      for (Vector<Component> basisVector : s.basis)
      {
         // Code adapted from "projectedOnto"
         // printf("\nProjecting %s onto %s\nCurrent Projection:%s\n", toString().c_str(), basisVector.toString().c_str(), "pc");
         Component dProduct = 0;
         Component basisVectorMagSquared = 0;

         for (int i = 0; i < dimensions; i++)
         {
            dProduct += basisVector.components[i] * components[i];
            basisVectorMagSquared += basisVector.components[i] * basisVector.components[i];
         }

         // printf("Dot Product: %f, Msq:%f\n", dProduct, basisVectorMagSquared);
         if (dProduct * basisVectorMagSquared == 0)
         {
            // projectionComponents[i]=0;
            continue;
         }

         Component scaleBasisVectorBy = dProduct / basisVectorMagSquared;

         for (int i = 0; i < dimensions; i++)
         {
            projectionComponents[i] += basisVector.components[i] * scaleBasisVectorBy;
         }
      }
      // Component[] newComponents = new Component[dimensions];
      // for(int i = 0; i < dimensions;i++)newComponents[i] =
      // components[i]+v.components[i];
      // printf("Projection: %s\n\n", "pc");
      return projectionComponents;
   }
   auto begin() const noexcept
   {
      return components.begin();
   }
   auto end() const noexcept
   {
      return components.end();
   }

   std::string toString() const noexcept
   {
      if (dimensions == 0)
         return std::string("Vector[]");
      std::stringstream s;
      s << "Vector[";
      // s.append(String.format("%.2f", components[0]));
      s << components[0];
      for (int i = 1; i < dimensions; i++)
      {
         s << ", " << components[i];
         //s.append(String.format(",%.2f", components[i]));
      }
      s << ("]");
      return s.str();
   }

   bool equals(Vector<Component> v)
   {
      if (dimensions != v.dimensions)
         return false;
      for (int i = 0; i < dimensions; i++)
      {
         if (components[i] != v.components[i])
            return false;
      }
      return true;
   }

   Vector<Component> normalize()
   {
      // return *this;
      return scale(1 / magnitude());
   }

   std::size_t hash() const
   {
      return std::hash<Vector<Component>>{}(*this);
   }

   Vector<Component> clone() const
   {
      return Vector<Component>(components);
   }

   friend Vector<Component> operator*(Vector<Component> &v, Component c);
   //    friend Vector<Component> operator*(Vector<Component> v, Component c);

   friend Vector<Component> operator*(Component c, Vector<Component> &v);
   //    friend Vector<Component> operator*(Component c, Vector<Component> v);

   friend Vector<Component> operator/(Vector<Component> &v, Component c);
   //    friend Vector<Component> operator/(Vector<Component> v, Component c);

   friend Vector<Component> operator/(Component c, Vector<Component> &v);
   //    friend Vector<Component> operator/(Component c,Vector<Component>v);

   friend std::ostream &operator<<(std::ostream &s, Vector<Component> v);

   friend Vector<Component> operator+(Vector<Component> &v, Vector<Component> w);
   //    friend Vector<Component> operator+(Vector<Component> v, Vector<Component> w);

   friend Vector<Component> operator-(Vector<Component> &v, Vector<Component> w);
   //    friend Vector<Component> operator-(Vector<Component> v, Vector<Component> w);

   const Component &operator[](int i)
   {
      // if
      return *(components.data() + i);
   }
   // Vector<Component> &operator=(const Vector<Component>) = default;
   Vector<Component> &operator*=(Component c);
   Vector<Component> &operator/=(Component c);

   Vector<Component> &operator+=(Vector<Component> &v);
   Vector<Component> &operator-=(Vector<Component> &v);

   // Vector<Component> &operator=(const Vector &o)
   // {
   //    if (this != &o)
   //    {
   //       this->dimensions = o.dimensions;
   //       for (int i = 0; i < this->dimensions;i++){
   //          components[i]=o.components[i];
   //       }
   //    }
   //    return *this;
   // }
};
template <typename Component>
std::ostream &operator<<(std::__1::basic_ostream<char, std::__1::char_traits<char>> &s, Vector<Component> v)
{

   return (s << v.toString().c_str());
}
template <typename Component>
Vector<Component> operator*(Vector<Component> &v, Component c)
{
   return v.clone().scale(c);
};
template <typename Component>
Vector<Component> operator*(Component c, Vector<Component> &v)
{
   return v.clone().scale(c);
};

template <typename Component>
Vector<Component> operator*(Vector<Component> v, Component c)
{

   return v.scale(c);
};
template <typename Component>
Vector<Component> operator*(Component c, Vector<Component> v)
{
   return v.scale(c);
};

template <typename Component>
Vector<Component> operator/(Vector<Component> &v, Component c)
{
   return v.clone().scale(1 / c);
};
template <typename Component>
Vector<Component> operator/(Component c, Vector<Component> &v)
{
   return v.clone().scale(1 / c);
};

template <typename Component>
Vector<Component> operator/(Vector<Component> v, Component c)
{
   return v.scale(1 / c);
};
template <typename Component>
Vector<Component> operator/(Component c, Vector<Component> v)
{
   return v.scale(1 / c);
};

template <typename Component>
Vector<Component> operator+(Vector<Component> &v, Vector<Component> w)
{
   return v.clone().add(w);
};
template <typename Component>
Vector<Component> operator+(Vector<Component> v, Vector<Component> w)
{
   return v.add(w);
};

template <typename Component>
Vector<Component> operator-(Vector<Component> &v, Vector<Component> w)
{
   return v.clone().subtract(w);
};
template <typename Component>
Vector<Component> operator-(Vector<Component> v, Vector<Component> w)
{
   return v.subtract(w);
};

template <typename Component>
Vector<Component> &Vector<Component>::operator*=(Component c)
{
   return scale(c);
};
template <typename Component>
Vector<Component> &Vector<Component>::operator/=(Component c)
{
   return scale(1 / c);
};

template <typename Component>
Vector<Component> &Vector<Component>::operator+=(Vector<Component> &v)
{
   return add(v);
};
template <typename Component>
Vector<Component> &Vector<Component>::operator-=(Vector<Component> &v)
{
   return subtract(v);
};

namespace std
{
   template <typename Component>
   struct hash<Vector<Component>>
   {
      std::size_t operator()(Vector<Component> const &v) const noexcept
      {
         std::size_t h = 301;
         auto hasher = std::hash<Component>{};
         int i = 0;
         for (Component c : v)
         {
            h = h ^ (hasher(c) << (i++));
         }
         return h;
      }
   };
}; // namespace std
