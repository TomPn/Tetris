#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Subject;

class Observer
{
    bool text;

public:
    Observer(bool text) : text{text} {}
    virtual void notify() = 0;
    bool getText();
    virtual ~Observer() = default;
};

#endif
