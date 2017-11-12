/*
The MIT License (MIT)

Copyright (c) 2017 Lancaster University.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include "CircuitPlayground.h"
#include "CodalDmesg.h"

CircuitPlayground cplay;

#define BUFFER_SIZE 0

void set_gpio(int pin_number, int state)
{
    cplay.io.pin[pin_number].setDigitalValue(state);
}

void high()
{
#if BUFFER_SIZE > 0
    volatile char b[BUFFER_SIZE] = {0};
#endif


    while(1)
    {
        set_gpio(1,1);
        schedule();
    }
}

void low()
{
#if BUFFER_SIZE > 0
    volatile char b[BUFFER_SIZE] = {0};
#endif

    while(1)
    {
        set_gpio(1,0);
        schedule();
    }
}


int main()
{
    DMESGF("HELLO!\r\n");
    set_gpio(1,0);

    create_fiber(low);
    create_fiber(high);

    release_fiber();
}