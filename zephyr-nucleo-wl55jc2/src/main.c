/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/zephyr.h>


#include <zephyr/drivers/gpio.h>

//#define LED0_NODE DT_ALIAS(led0)
//#define LEDBLUE_NODE DT_ALIAS(ledblue)

#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#warning --- --- --- macro evaluating 'led0' dts alias returns true --- --- ---
#define LED0_LABEL   DT_GPIO_LABEL(LED0_NODE, gpios)
#define LED0_PIN     DT_GPIO_PIN(LED0_NODE, gpios)
#define LED0_FLAGS   DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
#warning --- --- --- macro evaluating 'led0' dts alias returns false --- --- ---
#define LED0_LABEL   ""
#define LED0_PIN     0
#define LED0_FLAGS   0
#endif


#define LED1_NODE DT_ALIAS(ledblue)

#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
#warning --- --- --- macro evaluating 'led1' dts alias returns true --- --- ---
#define LED1_LABEL   DT_GPIO_LABEL(LED1_NODE, gpios)
#define LED1_PIN     DT_GPIO_PIN(LED1_NODE, gpios)
#define LED1_FLAGS   DT_GPIO_FLAGS(LED1_NODE, gpios)
#else
#warning --- --- --- macro evaluating 'led1' dts alias returns false --- --- ---
#define LED1_LABEL   ""
#define LED1_PIN     0
#define LED1_FLAGS   0
#endif


// Not actuating either green nor blue LEDs:
//static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
//static const struct gpio_dt_spec ledblue = GPIO_DT_SPEC_GET(LEDBLUE_NODE, gpios);

static const struct device *dev;
static const struct device *dev_led_blue;


void main(void)
{
    uint32_t led_is_on = 0;
    uint32_t rstatus = 0;

    printk("Hello World! %s\n", CONFIG_BOARD);

// - Zephyr device initialization for LED zero:

    dev = device_get_binding(LED0_LABEL);
    if (dev == NULL) {
        return;
    }

    rstatus = gpio_pin_configure(dev, LED0_PIN, GPIO_OUTPUT_ACTIVE | LED0_FLAGS);
    if (rstatus < 0) {
        return;
    }

    dev_led_blue = device_get_binding(LED1_LABEL);
    if (dev_led_blue == NULL) {
        return;
    }

    rstatus = gpio_pin_configure(dev_led_blue, LED1_PIN, GPIO_OUTPUT_ACTIVE | LED1_FLAGS);
    if (rstatus < 0) {
        return;
    }


    while ( 1 )
    {
	printk("Hello world - zztop -  %s\n", CONFIG_BOARD);

//        rstatus = gpio_pin_toggle_dt(&led);
//        rstatus = gpio_pin_toggle_dt(&ledblue);

        gpio_pin_set(dev, LED0_PIN, (int)led_is_on);
        led_is_on = !led_is_on;
        gpio_pin_set(dev_led_blue, LED1_PIN, (int)led_is_on);

        k_msleep(1152);
    }
}
