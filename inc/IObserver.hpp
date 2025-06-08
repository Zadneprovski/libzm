#ifndef LIBZM_INC_IOBSERVER_HPP_
#define LIBZM_INC_IOBSERVER_HPP_

struct ISubject;

struct IObserverBase {
    using Notification = void (*)(ISubject*, IObserverBase*, int);

    IObserverBase* next = nullptr;
    Notification notification_ = nullptr;

    void notify(ISubject* subject, int value) {
    	notification_(subject, this, value);
    }

    constexpr IObserverBase(Notification notification) : notification_(notification){}
};

template<typename T>
struct IObserver : IObserverBase {
    IObserver()
        : IObserverBase([](ISubject* subject, IObserverBase* observer, int value) {
            static_cast<T*>(observer)->onNotify(subject, value);
        }) {}
};

class MyObserver1 : public IObserver<MyObserver1> {
public:
    void onNotify(ISubject* subject,int value) {
    	libzm::trace("MyObserver1");
    }
};

class MyObserver2 : public IObserver<MyObserver2> {
public:
    void onNotify(ISubject* subject, int value) {
    	libzm::trace("MyObserver2");
    }
};

#endif /* LIBZM_INC_IOBSERVER_HPP_ */
