#ifndef MYCLASS_H
#define MYCLASS_H

#include <string>

class MyClass {
private:
    int x;\n    std::string name;\n

public:
    MyClass(int x, std::string name);
    ~MyClass() = default;

    void doSomething();\n    std::string getName();\n
};

#endif
