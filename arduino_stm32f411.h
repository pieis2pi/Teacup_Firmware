
/** \file
  \brief MCU pin mappings.

  Here we map the pins required by Teacup to the names known by CMSIS.
*/

/** I/O pins.

  In MBED, I/O pin handling is rather complicated. Lots of enums, lots of
  functions, spread over various files, slow execution (pin toggling about
  15 times slower than what we have here).

  FASTIO by setting the BSRR (bit set/reset register),
  - Bit0-15 to set
  - Bit16-31 to reset.

  Pins set for Nucleo F411RE, for other STM32F4-boards you need to add them.
*/

#include "cmsis-stm32f4xx.h"

#define F_CPU __SYSTEM_CLOCK

/** Pins for UART, the serial port.
*/
#define RXD_PORT        PIOA_3_PORT
#define RXD_PIN         PIOA_3_PIN
#define TXD_PORT        PIOA_2_PORT
#define TXD_PIN         PIOA_2_PIN

/**
  We define only pins available on the Nucleo F411RE here.
  Use alphas for PORT and numerics for PIN, close to the design.
*/

// say hello to arduino.h and ignore the test
#define PIO0_1_PIN
// maybe add new test to arduino.h

#define PIOA_0_PIN      0
#define PIOA_0_PORT     GPIOA
#define PIOA_0_ADC      0

#define PIOA_1_PIN      1
#define PIOA_1_PORT     GPIOA
#define PIOA_1_ADC      1

#define PIOA_2_PIN      2
#define PIOA_2_PORT     GPIOA
#define PIOA_2_ADC      2

#define PIOA_3_PIN      3
#define PIOA_3_PORT     GPIOA
#define PIOA_3_ADC      3

#define PIOA_4_PIN      4
#define PIOA_4_PORT     GPIOA
#define PIOA_4_ADC      4

#define PIOA_5_PIN      5
#define PIOA_5_PORT     GPIOA
#define PIOA_5_ADC      5

#define PIOA_6_PIN      6
#define PIOA_6_PORT     GPIOA
#define PIOA_6_ADC      6

#define PIOA_7_PIN      7
#define PIOA_7_PORT     GPIOA
#define PIOA_7_ADC      7

#define PIOA_8_PIN      8
#define PIOA_8_PORT     GPIOA

#define PIOA_9_PIN      9
#define PIOA_9_PORT     GPIOA

#define PIOA_10_PIN     10
#define PIOA_10_PORT    GPIOA

#define PIOA_11_PIN     11
#define PIOA_11_PORT    GPIOA

#define PIOA_12_PIN     12
#define PIOA_12_PORT    GPIOA

#define PIOA_13_PIN     13
#define PIOA_13_PORT    GPIOA

#define PIOA_14_PIN     14
#define PIOA_14_PORT    GPIOA

#define PIOA_15_PIN     15
#define PIOA_15_PORT    GPIOA

#define PIOB_0_PIN      0
#define PIOB_0_PORT     GPIOB
#define PIOB_0_ADC      8

#define PIOB_1_PIN      1
#define PIOB_1_PORT     GPIOB
#define PIOB_1_ADC      9

#define PIOB_2_PIN      2
#define PIOB_2_PORT     GPIOB

#define PIOB_3_PIN      3
#define PIOB_3_PORT     GPIOB

#define PIOB_4_PIN      4
#define PIOB_4_PORT     GPIOB

#define PIOB_5_PIN      5
#define PIOB_5_PORT     GPIOB

#define PIOB_6_PIN      6
#define PIOB_6_PORT     GPIOB

#define PIOB_7_PIN      7
#define PIOB_7_PORT     GPIOB

#define PIOB_8_PIN      8
#define PIOB_8_PORT     GPIOB

#define PIOB_9_PIN      9
#define PIOB_9_PORT     GPIOB

#define PIOB_10_PIN     10
#define PIOB_10_PORT    GPIOB

#define PIOB_12_PIN     12
#define PIOB_12_PORT    GPIOB

#define PIOB_13_PIN     13
#define PIOB_13_PORT    GPIOB

#define PIOB_14_PIN     14
#define PIOB_14_PORT    GPIOB

#define PIOB_15_PIN     15
#define PIOB_15_PORT    GPIOB

#define PIOC_0_PIN      0
#define PIOC_0_PORT     GPIOC
#define PIOC_0_ADC      10

#define PIOC_1_PIN      1
#define PIOC_1_PORT     GPIOC
#define PIOC_1_ADC      11

#define PIOC_2_PIN      2
#define PIOC_2_PORT     GPIOC
#define PIOC_2_ADC      12

#define PIOC_3_PIN      3
#define PIOC_3_PORT     GPIOC
#define PIOC_3_ADC      13

#define PIOC_4_PIN      4
#define PIOC_4_PORT     GPIOC
#define PIOC_4_ADC      14

#define PIOC_5_PIN      5
#define PIOC_5_PORT     GPIOC
#define PIOC_5_ADC      15

#define PIOC_6_PIN      6
#define PIOC_6_PORT     GPIOC

#define PIOC_7_PIN      7
#define PIOC_7_PORT     GPIOC

#define PIOC_8_PIN      8
#define PIOC_8_PORT     GPIOC

#define PIOC_9_PIN      9
#define PIOC_9_PORT     GPIOC

#define PIOC_10_PIN     10
#define PIOC_10_PORT    GPIOC

#define PIOC_11_PIN     11
#define PIOC_11_PORT    GPIOC

#define PIOC_12_PIN     12
#define PIOC_12_PORT    GPIOC

#define PIOC_13_PIN     13
#define PIOC_13_PORT    GPIOC

#define PIOC_14_PIN     14
#define PIOC_14_PORT    GPIOC

#define PIOC_15_PIN     15
#define PIOC_15_PORT    GPIOC

#define PIOD_2_PIN      2
#define PIOD_2_PORT     GPIOD

#define PIOH_0_PIN      0
#define PIOH_0_PORT     GPIOH

#define PIOH_1_PIN      1
#define PIOH_1_PORT     GPIOH
