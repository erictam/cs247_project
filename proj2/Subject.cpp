#include <algorithm>

#include "Subject.h"
#include "Observer.h"

// Updates all subscribers by calling their update methods
void Subject::notify() {
    for(unsigned int i = 0; i < subscribers_.size(); ++i) {
        subscribers_.at(i)->update();
    }
}

// Adds an Observer to the subscription list
void Subject::subscribe(Observer* obs) {
    subscribers_.push_back(obs);
}

// Removes an Observer from the subscription list
void Subject::unsubscribe(Observer* obs) {
    std::vector<Observer*>::iterator itr = std::find(subscribers_.begin(), subscribers_.end(), obs);

    if(itr != subscribers_.end())
        subscribers_.erase(itr);
}

