// A for each concrete class define the following:
//     1) a C struct for the data in each class instance plus the Vpointer
//     2) member functions
//       a) add _this formal parameter
//       b) prefix methods with _this->
//     3) vtable
//     4) constructor
//       a) must call the parent constructor
//       b) must set the vpointer

// B Write the main
// General C includes and definitions:

#include <malloc.h>
#include <iostream>
using namespace std;


// A vtable is an array of method pointers.
// The specific profile for each method will depend on how the programmer declared the parameters and return type.

// this example, the methods all return type double and they only take the this parameter,
// you have draw() and area() which have different profiles (so I defined the union below for you to use in your homework)

typedef double (*double_method_type)(void *);
typedef void (*void_method_type)(void *);

typedef union {
    double_method_type double_method; // this is for area()
    void_method_type void_method;     // this is for draw()
} VirtualTableEntry;

typedef VirtualTableEntry * VTableType;


// these are the indices of the virtual functions in this class hierarchy, starting 0, 1, ...
#define AREA_INDEX 0
#define CIRCUMFERENCE_INDEX 1

#define PI 3.14159

// Start of Class Circle


struct Circle
{
    VTableType VPointer;
    double radius;
};



double Circle_area(Circle * _this)
{
    return PI * _this->radius * _this->radius;
}

double Circle_circumference(Circle * _this)
{
    return 2.0 * PI * _this->radius;
}

VirtualTableEntry Circle_VTable [] =
{
    {.double_method=(double_method_type)Circle_area}, // VTable[AREA_INDEX] - the first virtual method
    {.double_method=(double_method_type)Circle_circumference} // VTable[CIRCUMFERENCE_INDEX] - the second virtual method
};

Circle * Circle_Circle(Circle * _this, double newRadius)
{
    _this->VPointer = Circle_VTable;
    _this->radius = newRadius;
    // having our constructors return _this allows us to create array of heap objects very easily, see main below...
    return _this;
}

// End of Class Circle

// Start of Class ACircle

struct ACircle
    // extends Circle
{
    VTableType VPointer;
    double radius;
    double aData;
};

double ACircle_area(ACircle * _this)
{
    return PI * _this->radius * _this->radius / _this->aData;
}

VirtualTableEntry ACircle_VTable [] =
{
    {.double_method=(double_method_type)ACircle_area}, // Over-ride area
    {.double_method=(double_method_type)Circle_circumference} // inherit Circle::circumference
};

ACircle * ACircle_ACircle(ACircle * _this, double newRadius, double aValue)
{
    Circle_Circle((Circle *)_this, newRadius); // call parents constructor
    _this->VPointer = ACircle_VTable; // set the vpointer AFTER parent
    _this->aData = aValue;
    return _this;
}

// End of Class ACircle

int main()
{
Circle * a [] = {
    Circle_Circle((Circle *)malloc(sizeof(Circle)), 1.0),
    Circle_Circle((Circle *)malloc(sizeof(Circle)), 10.0),
    Circle_Circle((Circle *)malloc(sizeof(Circle)), 100.0),
    (Circle *)ACircle_ACircle((ACircle *)malloc(sizeof(ACircle)),
        1000.0, 2.0),
    (Circle *)ACircle_ACircle((ACircle *)malloc(sizeof(ACircle)),
        10000.0, PI)
    };
for (int i=0; i<sizeof(a)/sizeof(*a); i++)
{
    cout << "Area = " << (a[i]->VPointer[AREA_INDEX]).double_method(a[i]) << endl;
    cout << "Circumference = " << (a[i]->VPointer[CIRCUMFERENCE_INDEX]).double_method(a[i]) << endl;
}
}