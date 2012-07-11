#ifndef SUBJECT_H_
#define SUBJECT_H_

#include <vector>

#include "Observer.h"

class Subject {
    public:
        virtual ~Subject(){}
        void subscribe(Observer* obs);
        void unsubscribe(Observer* obs);

    protected:
        void notify();
        Subject() {}
        Subject(const Subject* rhs);
        Subject& operator=(const Subject& rhs);

    private:
        std::vector<Observer*> subscribers_;
};

#endif

