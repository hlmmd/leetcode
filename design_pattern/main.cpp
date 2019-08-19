#include "singleton.h"
#include "factory.h"
#include "product.h"
#include <iostream>
using namespace std;

int main()
{

    if (1)
    {
        Singleton *s = Singleton::Instance();
        delete s ;
    }

    if(1)
    {
       Factory * fac = new ConcreteFactory();
       Product * p = fac->CreateProduct();
       delete p;
       delete fac;
    }

    return 0;
}