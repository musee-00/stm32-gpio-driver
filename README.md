# STM32 Bare-Metal GPIO Driver

A bare-metal GPIO driver library for the STM32F411RE (Nucleo-F411RE) written in C with no HAL dependencies. All pin configuration is done through direct register access.

## Features
- Clock enable per GPIO port
- Pin mode configuration (input / output / alternate function / analog)
- Output type (push-pull / open-drain)
- Pull-up / pull-down configuration
- Atomic pin set/reset using BSRR
- Pin toggle and read

## Hardware
- STM32F411RE (ARM Cortex-M4, 100MHz)
- Nucleo-F411RE development board

## Usage
```c
gpio_clock_enable(GPIOA);
gpio_set_mode(GPIOA, 5, GPIO_MODE_OUTPUT);
gpio_set_output_type(GPIOA, 5, GPIO_OTYPE_PP);
gpio_toggle(GPIOA, 5);
```

## Build
Built with STM32CubeIDE 2.1.1 targeting ARM Cortex-M4.
