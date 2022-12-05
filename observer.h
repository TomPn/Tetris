#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Subject;

class Observer {
    public:
        virtual void notify(bool over) = 0;
        virtual void prompt() = 0;
        virtual ~Observer() = default;
        virtual void clear() = 0;
};

#endif
