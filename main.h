extern "C"
{
    extern void init();
}

extern void setup();
extern void loop();

int main()
{
    init();
    setup();
    for (;;)
        loop();
}

