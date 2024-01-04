#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#include <stdio.h>

#include <osek.h>
#include <os_api.h>
#include <sg_appmodes.h> /* os_builder generated code */



LOG_MODULE_REGISTER(autosar_os, LOG_LEVEL_DBG);


///////////////////////////////////////////////////////////////////////////////
// Macros
#define OS_TICK_MS	(1) /* ms per tick */
#define LED_ONTIME_MS	(250)
#define LED_GPIO25	DT_ALIAS(led0)



///////////////////////////////////////////////////////////////////////////////
// Globals
static const struct gpio_dt_spec LedStruct = GPIO_DT_SPEC_GET(LED_GPIO25, gpios);
static struct k_timer OsTickTimer;



///////////////////////////////////////////////////////////////////////////////
// Functions
static void os_ticks(struct k_timer *timer)
{
	static int count = (LED_ONTIME_MS/OS_TICK_MS);

	_OsHandleTicks();

	if (--count == 0) {
		gpio_pin_toggle_dt(&LedStruct);
		count = (LED_ONTIME_MS/OS_TICK_MS);
	}
}


int main(void)
{
	int ret;
	LOG_DBG("Welcome to CAR-OS (Zephyr)!");


	if (!gpio_is_ready_dt(&LedStruct)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&LedStruct, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	k_timer_init(&OsTickTimer, os_ticks, NULL);
	k_timer_start(&OsTickTimer, K_MSEC(OS_TICK_MS), K_MSEC(OS_TICK_MS));

	/* Calling a non-returning function */
	StartOS(OSDEFAULTAPPMODE);

	/* The execution should never reach here */
	LOG_DBG("ERROR: AUTOSAR OS exited! The execution will be trapped!");

	while (1) {
		k_msleep(5000);
	}

	return 0;
}