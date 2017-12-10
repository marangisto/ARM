//#include "init.h"

extern void setup();
extern void loop();

int main()
{
    ///init_controller();

    setup();
    for (;;)
        loop();
}

