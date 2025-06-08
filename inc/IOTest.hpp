#ifndef LIBZM_INC_IOTEST_HPP_
#define LIBZM_INC_IOTEST_HPP_

#include "trace.hpp"

class OutputBase {
public:
	using SetFunction = void (*)(OutputBase*);
    SetFunction set_ = nullptr;

    constexpr OutputBase(SetFunction set) : set_(set){}

    void onSet(){
        set_(this);
    }
};

template<typename Derived>
class Output : public OutputBase {
public:
    Output()
    : OutputBase([](OutputBase* ab){
    	static_cast<Derived*>(ab)->onSet();
    }) {};
};

class PhisicalOutput : public Output<PhisicalOutput>{
public:
    void onSet() { libzm::trace("Set phisical"); }
};

class LogicOutput : public Output<LogicOutput> {
public:
    void onSet() { libzm::trace("Set logic"); }
};

PhisicalOutput p;
LogicOutput l;

int test()
{
    OutputBase outs[] = {p, l};

    for (auto o : outs) {
		o.onSet();
	}

    return 0;
}


#endif /* LIBZM_INC_IOTEST_HPP_ */
