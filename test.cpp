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
    Basis initial{Vector<Number>{1, 2, 2}, Vector<Number>{-1, 0, 2},  Vector<Number>{0, 0, 1}};
    // Basis initial = Basis<Number>::standardBasis(3);
    Space org = initial.clone().toOrthogonal();
    Space orn = initial.clone().toOrthonormal();
    printf("Initial Basis: %s\n",initial.toString().c_str());
    printf("Orthographic projection : %s\n",org.toString().c_str());
    printf("OrthN: %s\n",orn.toString().c_str());
    printf("Inital again: %s\n",initial.toString().c_str());
    printf("Other: %s\n",Basis<Number>{{0,0,1,1},{0,1,1,0},{1,1,0,0}}.toOrthogonal().toString().c_str());

    Vector initialProjection = v.clone().projectInto(initial);
    Vector ornProjection = v.clone().projectInto(orn);
    Vector orgProjection = v.clone().projectInto(org);
    // Vector spaceProjection = s.projectionOf(v);
    printf("The inital version(%s) %s match the orthonormal version(%s)\n", initialProjection.toString().c_str(),initialProjection.equals(ornProjection) ? "does" : "doesn't", ornProjection.toString().c_str());
    printf("The inital version(%s) %s match the orthogonal version(%s)\n", initialProjection.toString().c_str(), initialProjection.equals(orgProjection) ? "does" : "doesn't", orgProjection.toString().c_str());
    printf("The orthonormal version(%s) %s match the orthonormal version(%s)\n", orgProjection.toString().c_str(), orgProjection.equals(ornProjection) ? "does" : "doesn't", ornProjection.toString().c_str());
}