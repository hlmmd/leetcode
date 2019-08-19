#ifndef _ABSTRACTION_H
#define _ABSTRACTION_H

class AbstractionImp;
class Abstraction
{
public:
    virtual ~Abstraction();
    virtual void Operation() = 0;

protected:
    Abstraction();
};

class RefinedAbstraction : public Abstraction
{
private:
    AbstractionImp *_imp;

public:
    RefinedAbstraction(AbstractionImp *imp);
    ~RefinedAbstraction();
    void Operation();
};

#endif