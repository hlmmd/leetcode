# 设计模式

## singleton 单例模式

创建一个唯一的变量对象。可用于替换全局变量。常和抽象工厂模式一起使用

### singleton.h

```cpp
#ifndef _SINGLETON_H_
#define _SINGLETON_H_

class Singleton{
private:
    static Singleton * instance;
    Singleton();
public:
    static Singleton* Instance();
};
#endif
```

### singleton.cpp

```cpp
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
```

## Factory 简单工厂

C++通过基类指针申请子类对象实现多态性。

面向对象中，面临着创建对象的问题，Factory封装了创建对象的接口，同时将类的实例化延迟到子类。

问题：需要为每一个具体的product类提供一个实例化函数，这样Factory接口是不可能封闭的，需要维护以适应新的类。当然也可以通过创建子类通过多态来实现，但这样也是新创建了一个类，代价高。

可以通过参数化工厂的方法，即传递一个参数来决定具体创建哪一个Product。

Factory适用于一类类，即他们有一个共同的基类。如果是不同的类，那么需要用AbstractFactory

### product.h

```cpp
#ifndef _PRODUCT_H_
#define _PRODUCT_H_

class Product
{

public:
    virtual ~Product() = 0;

protected:
    Product();
};

class ConcreteProduct : public Product
{
public:
    ConcreteProduct();
    ~ConcreteProduct();
};

#endif
```

### product.cpp

```cpp
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
```

### factory.h

```cpp
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
```

### factory.cpp

```cpp
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
```

## AbstractFactory 抽象工厂

用途：创建一组相关或者相互依赖的对象

如：游戏中的不同难度对应的不同等级的敌人

将一组对象的创建封装到一个用于创建对象的类中，维护一个创建类比维护n多相关对象的创建过程要简单得多。

相当于多个simple factory

## builder 生成器

按一系列步骤创建一个对象

例：大学四年，每年是一个步骤，读完四年创建一个大学生。每一个步骤可以不同，创造结果也不同。

## prototype 原型模式

使用原型实例指定要创建对象的类型，通过复制这个原型来创建新对象。

