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