#include "gpio.h"

/*
 * Enable the clock for a GPIO port.
 * The STM32 gates every peripheral's clock off by default to save power.
 * Nothing works until you enable it here first.
 */
void gpio_clock_enable(GPIO_TypeDef *port) {
    if      (port == GPIOA) RCC_AHB1ENR |= RCC_GPIOA_EN;
    else if (port == GPIOB) RCC_AHB1ENR |= RCC_GPIOB_EN;
    else if (port == GPIOC) RCC_AHB1ENR |= RCC_GPIOC_EN;
    else if (port == GPIOD) RCC_AHB1ENR |= RCC_GPIOD_EN;
}

/*
 * Set a pin's mode (input / output / alternate function / analog).
 * MODER uses 2 bits per pin → pin n lives at bits [2n+1 : 2n].
 * Pattern: clear the 2 bits first, then OR in the new value.
 */
void gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, GPIO_Mode mode) {
    port->MODER &= ~(0x3U << (pin * 2));   /* clear */
    port->MODER |=  (mode  << (pin * 2));   /* set   */
}

/*
 * Set push-pull or open-drain output type.
 * OTYPER uses 1 bit per pin.
 */
void gpio_set_output_type(GPIO_TypeDef *port, uint8_t pin, GPIO_OType otype) {
    port->OTYPER &= ~(1U   << pin);
    port->OTYPER |=  (otype << pin);
}

/*
 * Configure pull-up or pull-down resistor.
 * PUPDR uses 2 bits per pin, same layout as MODER.
 */
void gpio_set_pupd(GPIO_TypeDef *port, uint8_t pin, GPIO_PUPD pupd) {
    port->PUPDR &= ~(0x3U << (pin * 2));
    port->PUPDR |=  (pupd  << (pin * 2));
}

/*
 * Write a pin high or low.
 * We use BSRR instead of ODR — it's atomic.
 * Lower 16 bits of BSRR = SET a pin.
 * Upper 16 bits of BSRR = RESET a pin.
 * Writing to BSRR never causes a read-modify-write race condition.
 */
void gpio_write(GPIO_TypeDef *port, uint8_t pin, GPIO_PinState state) {
    if (state == GPIO_PIN_HIGH) {
        port->BSRR = (1U << pin);          /* set bit */
    } else {
        port->BSRR = (1U << (pin + 16));   /* reset bit */
    }
}

/*
 * Toggle a pin by reading ODR and flipping the bit.
 */
void gpio_toggle(GPIO_TypeDef *port, uint8_t pin) {
    port->ODR ^= (1U << pin);
}

/*
 * Read the current state of an input pin from IDR.
 */
GPIO_PinState gpio_read(GPIO_TypeDef *port, uint8_t pin) {
    return (port->IDR >> pin) & 1U;
}
