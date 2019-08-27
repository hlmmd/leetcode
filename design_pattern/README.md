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

### Template 模板方法

定义算法框架，并将一些步骤的实现延迟到子类。

通过模板方法，子类可以重新定义算法的某些步骤，而不用改变算法的结构。

继承

### Strategy 策略模式

定义一系列算法，封装每个算法，并使它们可以互换。

策略模式可以让算法独立于使用它的客户端。

组合

### State 状态模式

允许对象在内部状态改变时改变它的行为，对象看起来好像修改了它所属的类。

### Observer 观察者模式

定义对象之间的一对多依赖，当一个对象状态改变时，它的所有依赖都会收到通知并且自动更新状态。一对多关系。

subject:被观察者（一），observer:观察者（多）。

subject具有注册、移除、通知observer的功能，通过维护一张观察者表来实现。

#### subject.h

```cpp
#ifndef _SUBJECT_H
#define _SUBJECT_H

#include <list>
#include <string>
using namespace std;
typedef string State;
class Observer;
class Subject
{
public:
    virtual ~Subject();
    virtual void Attach(Observer *obv);
    virtual void Detach(Observer *obv);
    virtual void Notify();
    virtual void SetState(const State &st) = 0;
    virtual State GetState() = 0;

protected:
    Subject();

private:
    list<Observer *> *_obvs;
};

class ConcreteSubject : public Subject
{
public:
    ConcreteSubject();
    ~ConcreteSubject();
    State GetState();
    void SetState(const State &st);

protected:
private:
    State _st;
};

#endif
```

#### subject.cpp

```cpp
#include "subject.h"
#include "observer.h"
#include <iostream>
#include <list>
using namespace std;
typedef string state;
Subject::Subject()
{ //在模板的使用之前一定要new，创建
    _obvs = new list<Observer *>;
}
Subject::~Subject()
{
    delete _obvs;
}
void Subject::Attach(Observer *obv)
{
    _obvs->push_front(obv);
}
void Subject::Detach(Observer *obv)
{
    if (obv != NULL)
        _obvs->remove(obv);
}
void Subject::Notify()
{
    list<Observer *>::iterator it;
    it = _obvs->begin();
    for (; it != _obvs->end(); it++)
    { //关于模板和iterator的用法
        (*it)->Update(this);
    }
}
ConcreteSubject::ConcreteSubject()
{
    _st = "";
}
ConcreteSubject::~ConcreteSubject()
{
}
State ConcreteSubject::GetState()
{
    return _st;
}
void ConcreteSubject::SetState(const State &st)
{
    _st = st;
}
```

#### observer.h

```cpp
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
```

#### observer.cpp

```cpp
#include "observer.h"
#include "subject.h"

#include <iostream>
#include <string>
using namespace std;
Observer::Observer()
{
    _st = "";
}

Observer::~Observer()
{
}

ConcreteObserverA::ConcreteObserverA(Subject *sub)
{
    _sub = sub;
    _sub->Attach(this);
}

ConcreteObserverA::~ConcreteObserverA()
{
    _sub->Detach(this);
    if (_sub != NULL)
        delete _sub;
}
Subject *ConcreteObserverA::GetSubject()
{
    return _sub;
}

void ConcreteObserverA::PrintInfo()
{
    cout << "ConcreteObserverA observer.... " << _sub->GetState() << endl;
}

void ConcreteObserverA::Update(Subject *sub)
{
    _st = sub->GetState();
    PrintInfo();
}


ConcreteObserverB::ConcreteObserverB(Subject *sub)
{
    _sub = sub;
    _sub->Attach(this);
}

ConcreteObserverB::~ConcreteObserverB()
{
    _sub->Detach(this);
    if (_sub != NULL)
        delete _sub;
}
Subject *ConcreteObserverB::GetSubject()
{
    return _sub;
}

void ConcreteObserverB::PrintInfo()
{
    cout << "ConcreteObserverB observer.... " << _sub->GetState() << endl;
}

void ConcreteObserverB::Update(Subject *sub)
{
    _st = sub->GetState();
    PrintInfo();
}
```

### Momento 备忘录模式

Memento模式的关键就是要在不破坏封装行的前提下，捕获并保存一个类的内部状态，这样就可以利用该保存的状态实施恢复操作

撤销操作

### Mediator 中介者模式

集中相关对象之间复杂的沟通和控制方式。

### Command 命令模式

将命令封装成对象中，具有以下作用：

* 使用命令来参数化其它对象
* 将命令放入队列中进行排队
* 将命令的操作记录到日志中
* 支持可撤销的操作

Command模式在实现的实现和思想都很简单，其关键就是将一个请求封装到一个类中（Command），再提供处理对象（Receiver），最后Command命令由Invoker激活.

### Visitor 访问者模式

当需求发生变更的时候，如果直接修改已经封装好的类，会很繁琐。

Visitor模式则提供了一种解决方案：将更新（变更）封装到一个类中（访问操作），并由待更改类提供一个接收接口，则可达到效果。

### Chain of Responsibility 责任链模式

使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。将这些对象连成一条链，并沿着这条链发送该请求，直到有一个对象处理它为止。

### Iterator 迭代器模式

提供一种顺序访问聚合对象元素的方法，并且不暴露聚合对象的内部表示。

stl中list、vector的遍历

### Interpreter 解释器模式

为语言创建解释器，通常由语言的语法和语法分析来定义。