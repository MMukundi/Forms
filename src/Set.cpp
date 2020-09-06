#include "Set.h"
/*
import java.util.Collection;
import java.util.Iterator;

public class Set<Element> extends java.util.HashSet<Element> {
    public static void main(String[] args) {
        Set<Integer> s = new Set<Integer>(1,5,2,6,7,1,67,7,78);
        Set<Integer> evens= new Set<Integer>(x->x%2==0);
        System.out.println(s.cartesianPoduct(evens));
        System.out.println(s.cartesianPoduct(evens, (a, b, set1, set2) -> {
            return s.contains(b - a);
        }));
    }

    SetBuilder<Element> builder = null;

    Set(Element... values) {
        for (Element e : values) {
            add(e);
        }
    }

    Set(SetBuilder<Element> b, Element... values) {
        builder = b;
        for (Element e : values) {
            add(e);
        }
    }

    Set(Collection<Element> values) {
        for (Element e : values) {
            add(e);
        }
    }

    Set() {
    }

    @Override
    public boolean contains(Object o) {
        try {
            Element e = (Element)o;
            return super.contains(e) || (builder != null && builder.contains(e));
        } catch (Exception ex) {
            return false;
        }
    }

    <OtherElement> Set<OrderedPair<Element, OtherElement>> cartesianPoduct(Set<OtherElement> s) {
        Set<OrderedPair<Element, OtherElement>> product = new Set<OrderedPair<Element, OtherElement>>();
        Iterator<Element> a = iterator();
        Iterator<OtherElement> b;

        while (a.hasNext()) {
            Element e = a.next();
            b = s.iterator();
            while (b.hasNext()) {
                product.add(new OrderedPair<Element, OtherElement>(e, b.next()));
            }
        }
        return product;
    }

    <OtherElement> Set<OrderedPair<Element, OtherElement>> cartesianPoduct(Set<OtherElement> s,
            Relation<Element, OtherElement> r) {
        Set<OrderedPair<Element, OtherElement>> product = new Set<OrderedPair<Element, OtherElement>>();
        Iterator<Element> a = iterator();
        Iterator<OtherElement> b;

        while (a.hasNext()) {
            Element e = a.next();
            b = s.iterator();
            while (b.hasNext()) {
                OtherElement oe = b.next();
                if (r.pairSatifies(e, oe, this, s))
                    product.add(new OrderedPair<Element, OtherElement>(e, oe));
            }
        }
        return product;
    }

}

class OrderedPair<A, B> {
    A first;
    B second;

    OrderedPair(A a, B b) {
        this.first = a;
        this.second = b;
    }

    @Override
    public String toString() {
        return String.format("<%s,%s>", first.toString(), second.toString());
    }
}

@FunctionalInterface
interface Relation<Element1, Element2> {
    boolean pairSatifies(Element1 e1, Element2 e2, Set<Element1> set1, Set<Element2> set2);
}

@FunctionalInterface
interface SetBuilder<Element> {
    boolean contains(Element a);
}
*/