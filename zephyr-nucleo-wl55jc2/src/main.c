/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */



#include <zephyr/zephyr.h>

#include <zephyr/drivers/gpio.h>



#include "return-values.h"




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



// - DEV 0830 BEGIN -

static const struct device *dev_st_usart1;

// - DEV 0830 END -




uint32_t initialize_st_usart1(void)
{
    if ( dev_st_usart1 == NULL )
    {
//        dev_st_usart1 = device_get_binding(DT_LABEL(DT_NODELABEL("usart1")));
        dev_st_usart1 = device_get_binding(DT_LABEL(DT_NODELABEL(usart1)));
    }

    if ( dev_st_usart1 != NULL )
    {
        return Z__INFO__DEVICE_ALREADY_INITIALIZED_OR_NOT_NULL;
    }
    else
    {
        return Z__WARNING__NULL_DEVICE_POINTER;
    }
}




void main(void)
{
// - VAR BEGIN -
    uint32_t flag__led_green_ok = 1;
    uint32_t flag__led_blue_ok = 1;
    uint32_t flag__usart1_ok = 1;
    uint32_t led_is_on = 0;
    uint32_t rstatus = ROUTINE_OK;
// - VAR END -


    printk("Hello World! %s\n", CONFIG_BOARD);

// - Zephyr device initialization for LED zero:

    dev = device_get_binding(LED0_LABEL);
    if (dev == NULL) {
//        return;
        flag__led_green_ok &= 0;
    }

    if ( flag__led_green_ok )
    {
        rstatus = gpio_pin_configure(dev, LED0_PIN, GPIO_OUTPUT_ACTIVE | LED0_FLAGS);
        if (rstatus < 0) {
//            return;
            flag__led_green_ok &= 0;
        }
    }

    dev_led_blue = device_get_binding(LED1_LABEL);
    if (dev_led_blue == NULL) {
//        return;
        flag__led_blue_ok &= 0;
    }

    if ( flag__led_blue_ok )
    {
        rstatus = gpio_pin_configure(dev_led_blue, LED1_PIN, GPIO_OUTPUT_ACTIVE | LED1_FLAGS);
        if (rstatus < 0) {
            return;
        }
    }


    rstatus = initialize_st_usart1();
    if ( rstatus != Z__INFO__DEVICE_ALREADY_INITIALIZED_OR_NOT_NULL )
    {
	printk("- warning - could not initialize STM32WL55JC usart1!\n");
    }


    while ( 1 )
    {
	printk("Hello world - zztop 0830 -  %s\n", CONFIG_BOARD);

//        rstatus = gpio_pin_toggle_dt(&led);
//        rstatus = gpio_pin_toggle_dt(&ledblue);

        if ( flag__led_green_ok )
        {
            gpio_pin_set(dev, LED0_PIN, (int)led_is_on);
        }

        led_is_on = !led_is_on;

        if ( flag__led_blue_ok )
        {
            gpio_pin_set(dev_led_blue, LED1_PIN, (int)led_is_on);
        }





        k_msleep(1152);
    }
}
