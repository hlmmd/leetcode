#include "product.h"

#include <iostream>
using namespace std;

Product::Product()
{
}

Product::~Product()
{
}

ConcreteProduct::ConcreteProduct()
{
    cout << "ConcreteProduct  constructor" << endl;
}

ConcreteProduct::~ConcreteProduct()
{
    cout << "ConcreteProduct destructor" << endl;
}