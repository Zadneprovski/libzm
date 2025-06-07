#ifndef LIBZ_INC_USER_DEFINED_LITERALS_HPP_
#define LIBZ_INC_USER_DEFINED_LITERALS_HPP_

constexpr uint32_t operator"" _Hz(unsigned long long val)   { return val; }
constexpr uint32_t operator"" _kHz(unsigned long long val)  { return val * 1000; }
constexpr uint32_t operator"" _MHz(unsigned long long val)  { return val * 1000000; }


#endif /* LIBZ_INC_USER_DEFINED_LITERALS_HPP_ */
