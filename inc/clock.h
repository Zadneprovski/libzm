#ifndef CORE_INC_CLOCK_H_
#define CORE_INC_CLOCK_H_

#include "stm32g431xx.h"

#define NVIC_PRIORITYGROUP_4    (0x00000003U)  // 4 bits for pre-emption priority, 0 bit for subpriority
#define PRE_EMPTION_PRIORITY    (0U)
#define SUBPRIORITY             (0U)

#ifdef __cplusplus
extern "C" {
#endif

	extern __IO uint32_t sysTicks;

	void sysTickInterrupt();

	 __STATIC_FORCEINLINE uint32_t getSysTick()
	 {
	   return sysTicks;
	 }

	__STATIC_FORCEINLINE uint32_t setSysTickFrequency(const uint32_t hz)
	{
	  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	  uint32_t prioritygroup = NVIC_GetPriorityGrouping();

	  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(prioritygroup, PRE_EMPTION_PRIORITY, SUBPRIORITY));

	  uint32_t result = SysTick_Config(SystemCoreClock / hz);

	  SystemCoreClockUpdate();

	  return result;
	}

#ifdef __cplusplus
}
#endif

#endif /* CORE_INC_CLOCK_H_ */
