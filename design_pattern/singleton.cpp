#include "singleton.h"

#include <iostream>
using namespace std;

Singleton* Singleton::instance = NULL;

Singleton::Singleton()
{
    cout<<"Singleton Constructor"<<endl;
}

Singleton* Singleton::Instance()
{
    if(instance == NULL)
    {
        instance = new Singleton();
    }
    return instance;
}