# Bare-metal GPIO Driver — STM32F411RE

Register-level GPIO driver with zero HAL dependencies. All pin configuration done through direct manipulation of MODER, OTYPER, PUPDR, BSRR, and IDR registers.

---

## Features

- Clock enable per GPIO port (GPIOA–GPIOD)
- Pin mode: input / output / alternate function / analog
- Output type: push-pull / open-drain
- Pull-up / pull-down configuration
- Atomic pin set/reset using BSRR (no read-modify-write race)
- Pin toggle via ODR XOR
- Pin read from IDR

---

## Hardware

- STM32 Nucleo F411RE (ARM Cortex-M4)

---

## API

```c
gpio_clock_enable(GPIOA);
gpio_set_mode(GPIOA, 5, GPIO_MODE_OUTPUT);
gpio_set_output_type(GPIOA, 5, GPIO_OTYPE_PP);
gpio_set_pupd(GPIOA, 5, GPIO_PUPD_NONE);
gpio_toggle(GPIOA, 5);
gpio_write(GPIOA, 5, GPIO_PIN_HIGH);
GPIO_PinState s = gpio_read(GPIOA, 5);
```

---

## File Structure

| File | Purpose |
|------|---------|
| `Inc/gpio.h` | Register map, structs, enums, function declarations |
| `Src/gpio.c` | Driver implementation |
| `Src/main.c` | Demo — blinks onboard LED on PA5 |

---

## Build & Flash

Open in **STM32CubeIDE**, build with `Ctrl+B`, flash with `Run`.

---

## Stack

**C · STM32F411RE · ARM Cortex-M4 · Bare-metal · No HAL**
