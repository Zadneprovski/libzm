#ifndef CORE_INC_TRACE_HPP_
#define CORE_INC_TRACE_HPP_

#include "stm32g431xx.h"
#include <type_traits>
#include <charconv>  // for std::to_chars
#include <array>

extern "C"
{
	int __io_putchar(int ch)
	{
		ITM_SendChar(ch);
		return (ch);
	}
}

namespace libzm
{
	template<typename T>
	__STATIC_FORCEINLINE void trace(T value)
	{

		#ifndef NDEBUG
			if constexpr (std::is_same_v<T, const char*>)
				printf("%s\n", value);
			else
			{
				std::array<char, 32> buffer{ };

				if constexpr (std::is_integral_v<T>)
					std::to_chars(buffer.data(), buffer.data() + buffer.size(), value);
				else if constexpr (std::is_floating_point_v<T>)
					std::to_chars(buffer.data(), buffer.data() + buffer.size(), value);

				printf("%s\n", buffer.data());
			}
		#endif
	}
}

#endif /* CORE_INC_TRACE_HPP_ */
