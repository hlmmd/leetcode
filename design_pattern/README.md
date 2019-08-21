# 设计模式

## 创建型模式

### singleton 单例模式

创建一个唯一的变量对象。可用于替换全局变量。常和抽象工厂模式一起使用

#### singleton.h

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

#### singleton.cpp

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

### Factory 简单工厂

C++通过基类指针申请子类对象实现多态性。

面向对象中，面临着创建对象的问题，Factory封装了创建对象的接口，同时将类的实例化延迟到子类。

问题：需要为每一个具体的product类提供一个实例化函数，这样Factory接口是不可能封闭的，需要维护以适应新的类。当然也可以通过创建子类通过多态来实现，但这样也是新创建了一个类，代价高。

可以通过参数化工厂的方法，即传递一个参数来决定具体创建哪一个Product。

Factory适用于一类类，即他们有一个共同的基类。如果是不同的类，那么需要用AbstractFactory

#### product.h

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

#### product.cpp

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

#### factory.h

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

#### factory.cpp

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

### AbstractFactory 抽象工厂

用途：创建一组相关或者相互依赖的对象

如：游戏中的不同难度对应的不同等级的敌人

将一组对象的创建封装到一个用于创建对象的类中，维护一个创建类比维护n多相关对象的创建过程要简单得多。

相当于多个simple factory

### builder 生成器

按一系列步骤创建一个对象

例：大学四年，每年是一个步骤，读完四年创建一个大学生。每一个步骤可以不同，创造结果也不同。

### prototype 原型模式

使用原型实例指定要创建对象的类型，通过复制这个原型来创建新对象。

核心：拷贝构造函数

## 创建型模式总结

实际上Prototype模式和Builder模式、AbstractFactory模式都是通过一个类（对象实例）来专门负责对象的创建工作（工厂对象），它们之间的区别是：Builder模式重在复杂对象的一步步创建（并不直接返回对象），AbstractFactory模式重在产生多个相互依赖类的对象，而Prototype模式重在从自身复制自己创建新类。

## 结构型模式

总结面向对象实际上就两句话：一是松耦合（Coupling），二是高内聚（Cohesion）。面向对象系统追求的目标就是尽可能地提高系统模块内部的内聚（Cohesion）、尽可能降低模块间的耦合（Coupling）

### bridge 桥接模式

将系统分成两个相对独立的部分，抽象部分和实现部分。

Favor Composition Over Inheritance

组合大于继承。

#### abstraction.h

```cpp
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
```

#### abstraction.cpp

```cpp
#include "abstraction.h"
#include "abstractionImp.h"
#include <iostream>
using namespace std;

Abstraction::Abstraction()
{
}

Abstraction::~Abstraction()
{
}

RefinedAbstraction::RefinedAbstraction(AbstractionImp *imp)
{
    _imp = imp;
}
RefinedAbstraction::~RefinedAbstraction()
{
}

void RefinedAbstraction::Operation()
{
    _imp->Operation();
}
```

#### abstractionImp.h

```cpp
#ifndef _ABSTRACTIONIMP_H
#define _ABSTRACTIONIMP_H

class AbstractionImp
{
public:
    virtual ~AbstractionImp();
    virtual void Operation() = 0;

protected:
    AbstractionImp();
};

class ConcreteAbstractionImpA : public AbstractionImp
{
public:
    ConcreteAbstractionImpA();
    ~ConcreteAbstractionImpA();
    virtual void Operation();
};

class ConcreteAbstractionImpB : public AbstractionImp
{
public:
    ConcreteAbstractionImpB();
    ~ConcreteAbstractionImpB();
    virtual void Operation();
};

#endif
```

#### abstractionImp.cpp

```cpp
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
```

### Adapter 适配器模式

主要用于转换第三方接口。类比转接线的功能。

实现方法：双重继承/组合

继承：接口继承/实现继承。C++ public方式是接口+实现继承。可以通过用private继承获得实现继承。通过纯虚函数得到接口继承。但实际上C++中的纯虚函数也可以提供默认实现。

### Decorator 装饰

可以为类动态添加功能

为一个已经设计好的类添加新的功能，我们可以通过继承来实现，但这样会导致继承深度变深。所以可以用组合的方法实现。

有一个指向其他对象的指针，通过组合的方式来提供更多的操作。

### Composite 组合

Composite模式通过和Decorator模式有着类似的结构图，但是Composite模式旨在构造类，而Decorator模式重在不生成子类即可给对象添加职责。Decorator模式重在修饰，而Composite模式重在表示。

### flyweight 享元模式

对象可能存在一些能够共享的元素，将对象分为外部状态和内部状态。比如字母'a'，存在很多示例，但他们的字体颜色、大小相同等。

### Facade 外观模式

提供了一个统一的接口，用来访问子系统中的一群接口，从而让子系统更容易使用。

提供一些接口，但是这些接口存在于不同的类中，使用一个代理人来整合这些接口。

类里面组合了各个类的指针，定义一个接口函数，调用各个类的接口。

### Proxy 代理模式

控制对其它对象的访问

代理有以下四类：

* 远程代理（Remote Proxy）：控制对远程对象（不同地址空间）的访问，它负责将请求及其参数进行编码，并向不同地址空间中的对象发送已经编码的请求。
* 虚拟代理（Virtual Proxy）：根据需要创建开销很大的对象，它可以缓存实体的附加信息，以便延迟对它的访问，例如在网站加载一个很大图片时，不能马上完成，可以用虚拟代理缓存图片的大小信息，然后生成一张临时图片代替原始图片。
* 保护代理（Protection Proxy）：按权限控制对象的访问，它负责检查调用者是否具有实现一个请求所必须的访问权限。
* 智能代理（Smart Reference）：取代了简单的指针，它在访问对象时执行一些附加操作：记录对象的引用次数；当第一次引用一个对象时，将它装入内存；在访问一个实际对象前，检查是否已经锁定了它，以确保其它对象不能改变它。

逻辑和实现的彻底解耦

## 行为模式

### Template

定义算法框架，并将一些步骤的实现延迟到子类。

通过模板方法，子类可以重新定义算法的某些步骤，而不用改变算法的结构。

继承

### Strategy

定义一系列算法，封装每个算法，并使它们可以互换。

策略模式可以让算法独立于使用它的客户端。

组合

### State

允许对象在内部状态改变时改变它的行为，对象看起来好像修改了它所属的类。

### Observer

定义对象之间的一对多依赖，当一个对象状态改变时，它的所有依赖都会收到通知并且自动更新状态。

### Momento

### Command

### Visitor

### Chain of Responsibility

### Iterator

### Interpreter