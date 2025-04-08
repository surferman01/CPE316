# Day 3 (4/7/2025)

## Memory Map

- bottom = text
- then data (initted + uninitted)
- heap
  - dynamically allocated memory
- top = stack
  - temporary memory
  - holds local variables

## Variables

- static variables dont get 'abandoned'
  - they live in the heap so they exist in global scope
- local variables live in stack so they get 'abandoned' on function exit...

## Pull up/down Resistors

- target 0.1mA - 10mA
- for 3.3V, 10k ohm gives 0.33mA
- for debounce, we need a pull-up resistor

## Debounce

- allow 10ms for debounce to settle

## Registers (Recap)

- ODR
  - output data register
- IDR
  - input data register
- BSSR
  - bit set reset register
  - performs this atomically
  
- GPIOA
  - 0x4800_0000

## Read/Write IO

(int*) GPIOA->ODR


lets set GPIOC 2nd bit to 1

ATOMIC:
GPIOC->BSRR=0x4
NON-ATOMIC
GPIOC->ODR = 0x4;

lets reset GPIOC 3rd bit

ATOMIC:
GPIOC->BRR |= 0x8
NON_ATOMIC:
GPIOC->ODR &= ~0x8
