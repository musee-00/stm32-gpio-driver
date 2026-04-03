#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/* Base addresses for each GPIO port (from STM32F4 reference manual) */
#define GPIOA_BASE  0x40020000UL
#define GPIOB_BASE  0x40020400UL
#define GPIOC_BASE  0x40020800UL
#define GPIOD_BASE  0x40020C00UL

/* RCC base and AHB1ENR offset — needed to clock-enable each port */
#define RCC_BASE    0x40023800UL
#define RCC_AHB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x30))

/* Clock enable bits in RCC_AHB1ENR */
#define RCC_GPIOA_EN  (1U << 0)
#define RCC_GPIOB_EN  (1U << 1)
#define RCC_GPIOC_EN  (1U << 2)
#define RCC_GPIOD_EN  (1U << 3)

/* GPIO register map — matches the peripheral layout exactly */
typedef struct {
    volatile uint32_t MODER;    /* offset 0x00 — pin mode */
    volatile uint32_t OTYPER;   /* offset 0x04 — output type */
    volatile uint32_t OSPEEDR;  /* offset 0x08 — output speed */
    volatile uint32_t PUPDR;    /* offset 0x0C — pull-up/pull-down */
    volatile uint32_t IDR;      /* offset 0x10 — input data (read-only) */
    volatile uint32_t ODR;      /* offset 0x14 — output data */
    volatile uint32_t BSRR;     /* offset 0x18 — bit set/reset */
    volatile uint32_t LCKR;     /* offset 0x1C — configuration lock */
    volatile uint32_t AFR[2];   /* offset 0x20/0x24 — alternate function */
} GPIO_TypeDef;

/* Cast base addresses to our struct */
#define GPIOA  ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB  ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC  ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD  ((GPIO_TypeDef *) GPIOD_BASE)

/* Pin mode options (2 bits per pin in MODER) */
typedef enum {
    GPIO_MODE_INPUT  = 0x00,
    GPIO_MODE_OUTPUT = 0x01,
    GPIO_MODE_AF     = 0x02,
    GPIO_MODE_ANALOG = 0x03
} GPIO_Mode;

/* Output type options (1 bit per pin in OTYPER) */
typedef enum {
    GPIO_OTYPE_PP = 0,   /* push-pull */
    GPIO_OTYPE_OD = 1    /* open-drain */
} GPIO_OType;

/* Pull-up/pull-down options (2 bits per pin in PUPDR) */
typedef enum {
    GPIO_PUPD_NONE     = 0x00,
    GPIO_PUPD_PULLUP   = 0x01,
    GPIO_PUPD_PULLDOWN = 0x02
} GPIO_PUPD;

/* Pin state */
typedef enum {
    GPIO_PIN_LOW  = 0,
    GPIO_PIN_HIGH = 1
} GPIO_PinState;

/* Public API */
void gpio_clock_enable(GPIO_TypeDef *port);
void gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, GPIO_Mode mode);
void gpio_set_output_type(GPIO_TypeDef *port, uint8_t pin, GPIO_OType otype);
void gpio_set_pupd(GPIO_TypeDef *port, uint8_t pin, GPIO_PUPD pupd);
void gpio_write(GPIO_TypeDef *port, uint8_t pin, GPIO_PinState state);
void gpio_toggle(GPIO_TypeDef *port, uint8_t pin);
GPIO_PinState gpio_read(GPIO_TypeDef *port, uint8_t pin);

#endif /* GPIO_H */
