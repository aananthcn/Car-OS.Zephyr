#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include <stdio.h>


#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(autosar_os, LOG_LEVEL_DBG);


#define DELAY_MS	250

#define LED		DT_ALIAS(led0)


static const struct gpio_dt_spec LedStruct = GPIO_DT_SPEC_GET(LED, gpios);

static struct k_timer OsTickTimer;



static void os_ticks(struct k_timer *timer)
{
	static int count = 1000;

	if (--count == 0) {
		gpio_pin_toggle_dt(&LedStruct);
		count = 1000;
		LOG_DBG("OsTick");
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
	k_timer_start(&OsTickTimer, K_MSEC(1), K_MSEC(1));


	while (1) {
		k_msleep(DELAY_MS);
	}

	return 0;
}