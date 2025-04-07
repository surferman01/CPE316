# Day 2 (4/4/2025)

## Architecture

- cpu most important part = registers
- cpu has busses to peripherals

## GPIO

- general purpose I/O
- 16 bits:
  - GPIOA
  - GPIOB
  - GPIOC
- GPIOD -> 1 bit
- GPIOH -> 2 bits

## Struct

- short is 16 bits
- int is 32 bits

struct GPIO {
    unsigned short ODR;     // output data register
    unsigned short IDR;     // input data register
    unsigned short BSSR;    // bit set reset register
}

typedef struct GPIO GPIO_T;

GPIO_T *GPIOA;
GPIO_T *GPIOB;

GPIOA -> IDR
GPIOA -> ODR
GPIOA -> BSSR

## Push / Pull

- push because push current (allow current to flow out)
- pull because pull current down to gnd (create route to gnd; inward current flow)

## Semiconductor

- called barrier potential since they maintain a constant voltage drop
- diodes drop 0.7V

## SYSCLK

External Clock Sources

- crystal
- very accurate

Internal Clock Sources

- 