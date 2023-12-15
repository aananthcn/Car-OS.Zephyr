#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define DELAY_MS	500

#define LED		DT_ALIAS(led0)


static const struct gpio_dt_spec led_struct = GPIO_DT_SPEC_GET(LED, gpios);


int main(void)
{
	int ret;

	if (!gpio_is_ready_dt(&led_struct)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led_struct, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	while (1) {
		ret = gpio_pin_toggle_dt(&led_struct);
		if (ret < 0) {
			return 0;
		}

		k_msleep(DELAY_MS);
	}

	return 0;
}