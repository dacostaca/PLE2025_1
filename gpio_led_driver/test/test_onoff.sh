#!/bin/bash
./gpio_led_user on
sleep 1
./gpio_led_user state | grep -q ON
./gpio_led_user off
sleep 1
./gpio_led_user state | grep -q OFF
echo "Prueba on/off PASADA"
