#include "factory.h"
#include "product.h"

#include <iostream>

using namespace std;

Factory::Factory()
{
}

Factory::~Factory()
{
}

ConcreteFactory::ConcreteFactory()
{
    cout << "ConcreteFactory constructor" << endl;
}

ConcreteFactory::~ConcreteFactory()
{
    cout << "ConcreteFactory destructor" << endl;
}

Product *ConcreteFactory::CreateProduct()
{
    return new ConcreteProduct();
}