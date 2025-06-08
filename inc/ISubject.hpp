#ifndef LIBZM_INC_ISUBJECT_HPP_
#define LIBZM_INC_ISUBJECT_HPP_

#include "IObserver.hpp"

class ISubject {
private:
	IObserverBase* head = nullptr;

public:
    void addObserver(IObserverBase& observer) {
        if (head == nullptr) {
            head = &observer;
        } else {
        	IObserverBase* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = &observer;
        }
    }

    void notify(int value) {
    	IObserverBase* current = head;
        while (current != nullptr) {
            current->notify(this, value);
            current = current->next;
        }
    }
};

class MySubject : public ISubject
{

};

#endif /* LIBZM_INC_ISUBJECT_HPP_ */
