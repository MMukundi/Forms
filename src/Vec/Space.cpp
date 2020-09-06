 #include "Space.h"
 /*
    public static Space Orthonormal(Vector... basis) {
        if (basis.length == 0)
            return new Space();
        ArrayList<Vector> newBasisVectors = new ArrayList<Vector>();
        newBasisVectors.add(Vector.normalized(basis[0]));
        Space otherSpace = new Space(newBasisVectors.get(0));
        for (int i =1;i<basis.length;i++) {
            Vector v = basis[i];
            Vector newV = Vector.normalized(Vector.subtract(v, Vector.projectedInto(v, otherSpace)));
            newBasisVectors.add(newV);
            otherSpace = new Space(newBasisVectors.toArray(new Vector[0]));
        }
        return otherSpace;
    }
    public static Space Orthogonal(Vector... basis) {
        if (basis.length == 0)
            return new Space();
        ArrayList<Vector> newBasisVectors = new ArrayList<Vector>();
        newBasisVectors.add(basis[0]);
        Space otherSpace = new Space(newBasisVectors.get(0));
        for (int i =1;i<basis.length;i++) {
            Vector v = basis[i];
            Vector newV = Vector.subtract(v, Vector.projectedInto(v, otherSpace));
            newBasisVectors.add(newV);
            otherSpace = new Space(newBasisVectors.toArray(new Vector[0]));
        }
        return otherSpace;
    }
    public static Space Orthonormal(int indexToPreserve,Vector... basis) {
        if (basis.length == 0)
            return new Space();
        ArrayList<Vector> newBasisVectors = new ArrayList<Vector>();
        newBasisVectors.add(Vector.normalized(basis[indexToPreserve]));
        Space otherSpace = new Space(newBasisVectors.get(0));
        for (int i =0;i<basis.length;i++) {
            if(i==indexToPreserve)continue;
            Vector v = basis[i];
            Vector newV = Vector.normalized(Vector.subtract(v, Vector.projectedInto(v, otherSpace)));
            newBasisVectors.add(newV);
            otherSpace = new Space(newBasisVectors.toArray(new Vector[0]));
        }
        return otherSpace;
    }
    public static Space Orthogonal(int indexToPreserve,Vector... basis) {
        if (basis.length == 0)
            return new Space();
        ArrayList<Vector> newBasisVectors = new ArrayList<Vector>();
        newBasisVectors.add(basis[indexToPreserve]);
        Space otherSpace = new Space(newBasisVectors.get(0));
        for (int i =0;i<basis.length;i++) {
            if(i==indexToPreserve)continue;
            Vector v = basis[i];
            Vector newV = Vector.subtract(v, Vector.projectedInto(v, otherSpace));
            newBasisVectors.add(newV);
            otherSpace = new Space(newBasisVectors.toArray(new Vector[0]));
        }
        return otherSpace;
    }

    public static Vector projectionOf(Space s, Vector v) {
        return Vector.projectedInto(v, s);
    }

    @Override
    public String toString() {
        if (spaceDimensions == 0)
            return "Space{}";
        StringBuilder s = new StringBuilder("Space{");
        s.append(String.format("%s", basis[0]));
        for (int i = 1; i < spaceDimensions; i++) {
            s.append(String.format(",%s", basis[i]));
        }
        s.append("}");
        return s.toString();
    }
}
*/