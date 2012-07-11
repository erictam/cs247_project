#include <algorithm>

#include "Subject.h"
#include "Observer.h"

void Subject::notify() {
    for(unsigned int i = 0; i < subscribers_.size(); ++i) {
        subscribers_.at(i)->update();
    }
}

void Subject::subscribe(Observer* obs) {
    subscribers_.push_back(obs);
}

void Subject::unsubscribe(Observer* obs) {
    std::vector<Observer*>::iterator itr = std::find(subscribers_.begin(), subscribers_.end(), obs);

    if(itr != subscribers_.end())
        subscribers_.erase(itr);
}

