#pragma once

static inline void delayMicroseconds(uint32_t) __attribute__((always_inline, unused));
static inline void delayMicroseconds(uint32_t usec)
{
    // Based on Paul Stoffregen's implementation for Teensy 3.0 (http://www.pjrc.com/)

    if (usec == 0)
        return;

    //uint32_t n = usec * (F_CPU / 3000000L);
    uint32_t n = usec; // FIXME: something is clearly wrong here!

    asm volatile(
        "L_%=_delayMicroseconds:"       "\n\t"
        "subs   %0, #1"                 "\n\t"
        "bne    L_%=_delayMicroseconds" "\n"
        : "+r" (n) :
    );
}

static void delay(uint32_t millis)
{
    for (uint32_t i = 0; i < millis; ++i)
        delayMicroseconds(1000);
}

