#ifndef _OBSERVER_H
#define _OBSERVER_H
#include "subject.h"
#include <string>
using namespace std;
typedef string State;
class Observer
{
public:
    virtual ~Observer();
    virtual void Update(Subject *sub) = 0;
    virtual void PrintInfo() = 0;

protected:
    Observer();
    State _st;

private:
};

class ConcreteObserverA : public Observer
{
public:
    virtual Subject *GetSubject();
    ConcreteObserverA(Subject *sub);
    virtual ~ConcreteObserverA();
    void Update(Subject *sub);
    void PrintInfo();

protected:
private:
    Subject *_sub;
};

class ConcreteObserverB : public Observer
{
public:
    virtual Subject *GetSubject();
    ConcreteObserverB(Subject *sub);
    virtual ~ConcreteObserverB();
    void Update(Subject *sub);
    void PrintInfo();

protected:
private:
    Subject *_sub;
};

#endif