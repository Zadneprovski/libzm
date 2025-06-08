#include "clock.h"

__IO uint32_t sysTicks = 0;


/**
  * @brief This function handles System tick timer.
  */
void sysTickInterrupt()
{
	sysTicks += 1;
}
