#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <gtkmm.h>

class Observer{
    public:
        virtual ~Observer() {}
        virtual void update() = 0;

    protected:
        Observer() {} //abstract base class

    private:
        Observer(const Observer& rhs);              //non-copyable
        Observer& operator=(const Observer& rhs);   //non-copyable
};

#endif

