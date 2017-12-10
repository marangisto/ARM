#pragma once

static inline void delayMicroseconds(uint32_t) __attribute__((always_inline, unused));
static inline void delayMicroseconds(uint32_t usec)
{
    // Based on Paul Stoffregen's implementation for Teensy 3.0 (http://www.pjrc.com/)

    if (usec == 0)
        return;

    uint32_t n = usec * (F_CPU / 3000000);

    asm volatile(
        "L_%=_delayMicroseconds:"       "\n\t"
        "subs   %0, #1"                 "\n\t"
        "bne    L_%=_delayMicroseconds" "\n"
        : "+r" (n) :
    );
}

static void delay(uint32_t millis)
{
    while (millis-- > 0)
        delayMicroseconds(1000);
}

