#include "test.h"

class FleepFlorp
{
public:
    FleepFlorp(Number f) : fleep(f){};
    Number fleep = 0;
    friend FleepFlorp operator*(FleepFlorp &a, FleepFlorp &b);
    friend std::ostream &operator<<(std::ostream &a, FleepFlorp b);
    FleepFlorp &operator+=(FleepFlorp ff)
    {
        fleep += ff.fleep;
        return *this;
    }
};

std::ostream &operator<<(std::ostream &a, FleepFlorp b)
{
    return (a << b.fleep);
}

FleepFlorp operator*(FleepFlorp &a, FleepFlorp &b)
{
    return FleepFlorp(a.fleep * b.fleep);
};

int main()
{
    // Vector<Number> v{1.1, 2, 3};
    //  printf("%f,%f,%f",v[0],v[1],v[2]);
    // Space<Number>
    // Vector<FleepFlorp> v{0,1,0.2,0.3};
    // v.projectOnto(v.scale(1 / (v.magnitudeSquared())));
    // printf("%s\n", v.toString().c_str());
    // printf("%d\n", v.dot({1,2,3}));
    // printf("%f\n", v.dot({1, 2, 3}));
    // printf("%f\n", v.dot({1,2,3}).fleep);
    Vector<Number> v{3, 2, 1};
    Space s = Space<Number>::Orthogonal({Vector<Number>{1, 2, 2}, Vector<Number>{-1, 0, 2},  Vector<Number>{0, 0, 1}},1);
    printf("%s\n",s.toString().c_str());

    Vector vectorProjection = v.clone().projectInto(s);
    Vector spaceProjection = s.projectionOf(v);
    printf("The vector version %s match the space version\n",vectorProjection.equals(spaceProjection) ? "does" : "doesn't");
    printf("The vector version %s match {1,2,3}\n",vectorProjection.equals({1,2,3}) ? "does" : "doesn't");
}