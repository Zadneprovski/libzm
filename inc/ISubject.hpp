#ifndef LIBZM_INC_ISUBJECT_HPP_
#define LIBZM_INC_ISUBJECT_HPP_

#include <forward_list>
#include "IObserver.hpp"

class ISubject {
private:
    std::forward_list<IObserverBase*> observers;

public:
    template<typename T>
    void addObserver(T& observer) {
        static_assert(std::is_base_of<IObserverBase, T>::value,
            "Observer must derive from IObserverBase");
        observers.push_front(static_cast<IObserverBase*>(&observer));
    }

    void notifyAll(int value) {
        for (auto observer : observers)
            observer->notify(this, value);
    }
};

#endif /* LIBZM_INC_ISUBJECT_HPP_ */
