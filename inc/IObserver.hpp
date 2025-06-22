#ifndef LIBZM_INC_IOBSERVER_HPP_
#define LIBZM_INC_IOBSERVER_HPP_

class ISubject;

struct IObserverBase {
    using Notification = void (*)(ISubject*, IObserverBase*, int);

    Notification notification_ = nullptr;

    void notify(ISubject* subject, int value) {
        notification_(subject, this, value);
    }

    constexpr IObserverBase(Notification notification) : notification_(notification) {}
};

template<typename T>
struct IObserver : IObserverBase {
    IObserver()
        : IObserverBase([](ISubject* subject, IObserverBase* observer, int value) {
        static_cast<T*>(observer)->onNotify(subject, value);
            }) {}
};



#endif /* LIBZM_INC_IOBSERVER_HPP_ */
