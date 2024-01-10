#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/logging/log_ctrl.h>

#include <stdio.h>

#include <osek.h>
#include <os_api.h>
#include <sg_appmodes.h> /* os_builder generated code */

#include <EcuM.h>
#include <Dio.h>




///////////////////////////////////////////////////////////////////////////////
// Macros
#define OS_TICK_MS	(1) /* ms per tick */
#define LED_ONTIME_MS	(250)



///////////////////////////////////////////////////////////////////////////////
// Globals
static struct k_timer OsTickTimer;

LOG_MODULE_REGISTER(autosar_os, LOG_LEVEL_DBG);



///////////////////////////////////////////////////////////////////////////////
// Functions
static void os_ticks(struct k_timer *timer)
{
	static int count = (LED_ONTIME_MS/OS_TICK_MS);

	_OsHandleTicks(); // every 1 ms

	if (--count == 0) {
		Dio_FlipChannel(25); // Main LED is at GPIO25
		count = (LED_ONTIME_MS/OS_TICK_MS);
	}
}


int main(void)
{
	EcuM_Init(); // TODO: Try to call Call EcuM_Init() much earlier from assembly code.

        /* setup logging */
        LOG_INIT();
	LOG_DBG("\n\nWelcome to Car-OS.Zephyr!");

	k_timer_init(&OsTickTimer, os_ticks, NULL);
	k_timer_start(&OsTickTimer, K_MSEC(OS_TICK_MS), K_MSEC(OS_TICK_MS)); // every 1 ms

	/* Calling a non-returning function */
	StartOS(OSDEFAULTAPPMODE);

	/* The execution should never reach here */
	LOG_DBG("ERROR: AUTOSAR OS exited! The execution will be trapped!");
	while (1) {
		k_msleep(5000);
	}

	return 0;
}