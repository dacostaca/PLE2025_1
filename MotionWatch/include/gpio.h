#ifndef GPIO_H
#define GPIO_H

/**
 * @brief Inicializa un pin GPIO para salida.
 * @param pin Número del pin (por ejemplo, 112).
 */
void gpio_init(int pin);

/**
 * @brief Establece el estado de un pin GPIO.
 * @param pin Número del pin.
 * @param value 1 para encender, 0 para apagar.
 */
void gpio_set(int pin, int value);

#endif // GPIO_H
