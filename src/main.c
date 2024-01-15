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

#define CAR_OS_COLOR	"\x1B[92m"
#define DEFAULTCOLOR	"\x1B[0m"


///////////////////////////////////////////////////////////////////////////////
// Globals
static struct k_timer OsTickTimer;

LOG_MODULE_REGISTER(Car_OS, LOG_LEVEL_DBG);



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
        /* Setup logging */
        LOG_INIT();

        /* Car-OS's startup banner */
	LOG_RAW("%sStarting Aananth's Car-OS.Zephyr...%s\n", CAR_OS_COLOR, DEFAULTCOLOR);

	/* AUTOSAR's first function to execute before running OS */
	EcuM_Init(); // TODO: Try to call Call EcuM_Init() much earlier from assembly code.

	/* Setup Car-OS Tick events */
	k_timer_init(&OsTickTimer, os_ticks, NULL);
	k_timer_start(&OsTickTimer, K_MSEC(OS_TICK_MS), K_MSEC(OS_TICK_MS)); // every 1 ms

	/* Start Car-OS, calling a non-returning function */
	StartOS(OSDEFAULTAPPMODE);

	/* The execution should never reach here */
	LOG_ERR("ERROR: AUTOSAR OS exited! The execution will be trapped!");

	/* Loop for ever till restart */
	while (1) {
		k_msleep(5000);
	}

	return 0;
}