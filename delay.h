#pragma once

extern "C"
{
extern uint32_t GetTickCount();
extern void yield();
}

void delay( uint32_t ms )
{
    if (ms == 0)
        return;
    uint32_t start = GetTickCount();
    do {
        yield();
    } while (GetTickCount() - start < ms);
}

