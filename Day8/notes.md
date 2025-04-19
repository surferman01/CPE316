# Day 8 (4/18/2025)

## How to get rising edge

- current is B (high)
- prev is A (low)

B(A^B)

= B(A~B + ~AB) = ~AB

## Timers

don't really want to use a counter because we need to know clock spd and make it count up really high (80MHz)
- upcount = counting up (i++)
- downcount = counting down (i--)

Use Downcounting

- because when you hit 0, we trigger interrupt

- load a value (some high value)
- count down until 0
- at 0, timer interrupt triggered

## Clock 

- slow down clock using prescaler
