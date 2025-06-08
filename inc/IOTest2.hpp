#ifndef LIBZM_INC_IOTEST_HPP_
#define LIBZM_INC_IOTEST_HPP_

#include "trace.hpp"

class OutputBase {
public:
    virtual ~OutputBase() = default;

    // Виртуальная функция, вызываемая для установки
    virtual void onSet() = 0;
};

class PhisicalOutput : public OutputBase {
public:
    void onSet() override {
        libzm::trace("Set phisical");
    }
};

class LogicOutput : public OutputBase {
public:
    void onSet() override {
        libzm::trace("Set logic");
    }
};

PhisicalOutput p;
LogicOutput l;

int test()
{
    OutputBase* outs[] = {&p, &l};

    for (auto o : outs) {
		o->onSet();
	}

    return 0;
}


#endif /* LIBZM_INC_IOTEST_HPP_ */
