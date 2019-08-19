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
        cout << "sizeof(Singleton):" << sizeof(Singleton) << endl;
        delete s;
    }

    if (1)
    {
        Factory *fac = new ConcreteFactory();
        Product *p = fac->CreateProduct();
        cout << "sizeof(Factory):" << sizeof(Factory) << endl;
        cout << "sizeof(Product):" << sizeof(Product) << endl;
        delete p;
        delete fac;
    }

    return 0;
}