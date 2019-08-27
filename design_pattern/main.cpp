#include "singleton.h"
#include "factory.h"
#include "product.h"
#include "abstraction.h"
#include "abstractionImp.h"
#include "subject.h"
#include "observer.h"
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

    if (1)
    {
        AbstractionImp *IMP = new ConcreteAbstractionImpA();
        Abstraction *abs = new RefinedAbstraction(IMP);
        abs->Operation();
        delete abs;
        delete IMP;
    }

    if (1)
    {
        AbstractionImp *IMP = new ConcreteAbstractionImpB();
        Abstraction *abs = new RefinedAbstraction(IMP);
        abs->Operation();
        delete abs;
        delete IMP;
    }

    if(1)
    {
        ConcreteSubject *sub = new ConcreteSubject();
        Observer * o1 = new ConcreteObserverA(sub);
        Observer * o2 = new ConcreteObserverB(sub);
        sub->SetState("old");
        sub->Notify();
        sub->SetState("new");
        sub->Notify();
        delete o2;
        delete o1;
        delete sub;
    }

    return 0;
}