#include "abstractionImp.h"
#include "abstraction.h"
#include <iostream>

using namespace std;

AbstractionImp::AbstractionImp()
{
}

AbstractionImp::~AbstractionImp()
{
}

// void AbstractionImp::Operation()
// {
//     cout << "AbstractionImp....imp..." << endl;
// }

ConcreteAbstractionImpA::ConcreteAbstractionImpA()
{
}

ConcreteAbstractionImpA::~ConcreteAbstractionImpA()
{
}

ConcreteAbstractionImpB::ConcreteAbstractionImpB()
{
}

ConcreteAbstractionImpB::~ConcreteAbstractionImpB()
{
}

void ConcreteAbstractionImpA::Operation()
{
    cout << "ConcreteAbstractionImpA Operation" << endl;
}

void ConcreteAbstractionImpB::Operation()
{
    cout << "ConcreteAbstractionImpB Operation" << endl;
}