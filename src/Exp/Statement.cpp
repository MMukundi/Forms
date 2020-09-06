/*
Basic forms supplied by Forms are statements of the forms:
a * b
a / b
a + b
a - c
*/
namespace Forms{

    /** 
     * The numerical type used to represent numbers in Forms
    */
    typedef float ConstantType;

    /**
     * The building block of Forms, Expressions recursively represent discrete chunks of math i.e. 4 all the way up to ln(xthRoot(a^18)-3x)
    */
    class Expression{};
    
    /**
    A thin wrapper around a floating point value
    */
    class Constant:public Expression{

    };
    // template<typename EType1, typename EType2>
    // struct multiply{
    //     EType1 operator()(EType1 v1,EType2 v2){
    //         return void;
    //     }
    // }
}
