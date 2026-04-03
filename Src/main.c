#include <stdint.h>
#include "gpio.h"

static void delay(volatile uint32_t count) {
    while (count--);
}

int main(void) {

    gpio_clock_enable(GPIOA);
    gpio_set_mode(GPIOA, 5, GPIO_MODE_OUTPUT);
    gpio_set_output_type(GPIOA, 5, GPIO_OTYPE_PP);
    gpio_set_pupd(GPIOA, 5, GPIO_PUPD_NONE);

    while (1) {
        gpio_toggle(GPIOA, 5);
        delay(500000);
    }
}
