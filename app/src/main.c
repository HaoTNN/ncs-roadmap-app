/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <app_version.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

int main(void)
{
    const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_NODELABEL(led0), gpios);

    printk("Zephyr Example Application %s\n", APP_VERSION_STRING);

    if (!gpio_is_ready_dt(&led))
    {
        LOG_ERR("LED GPIO is not ready");
        return 0;
    }

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT))
    {
        LOG_ERR("Unable to configure GPIO as output");
        return 0;
    }

    while (1)
    {
        if (gpio_pin_toggle_dt(&led))
        {
            LOG_ERR("Unable to toggle GPIO output");
            return 0;
        }

        k_sleep(K_MSEC(1000));
    }

    return 0;
}

