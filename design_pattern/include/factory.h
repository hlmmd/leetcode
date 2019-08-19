#ifndef _FACTORY_H
#define _FACTORY_H

class Product;

class Factory
{
public:
    virtual ~Factory() = 0;
    virtual Product *CreateProduct() = 0;

protected:
    Factory();
};

class ConcreteFactory : public Factory
{
public:
    ~ConcreteFactory();
    ConcreteFactory();
    Product *CreateProduct();
};

#endif