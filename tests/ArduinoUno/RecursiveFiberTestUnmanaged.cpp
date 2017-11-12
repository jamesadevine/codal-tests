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

#include "ArduinoUno.h"
#include "CodalDmesg.h"

ArduinoUno uno;

#define FACTORIAL_N     11
#define THREADS_N       4

int completionCount = 0;

extern void device_heap_print();

void set_gpio(int pin_number, int state)
{
    uno.io.pin[pin_number].setDigitalValue(state);
}

void print_factorial(char* s)
{
    DMESG("%s\r\n", s);
}

int factorial(int n)
{
    char buf[32];
    sprintf(buf, "Factorial depth: %d", n);
    print_factorial(buf);

    uno.sleep(10);
    return (n == 1) ? 1 : n * factorial(n - 1);
}

void factorial_fiber()
{
    factorial(FACTORIAL_N);
    completionCount++;
    DMESGF("POP: %d\r\n", completionCount, THREADS_N - 1);
}

int main()
{
    DMESGF("HELLO\r\n");

    device_heap_print();

    for(int i = 0; i < THREADS_N; i++)
        create_fiber(factorial_fiber);

    while(completionCount != THREADS_N)
        uno.sleep(10);

    device_heap_print();
    completionCount = 0;

    for(int i = 0; i < THREADS_N; i++)
        create_fiber(factorial_fiber);

    while(completionCount != THREADS_N)
        uno.sleep(10);

    device_heap_print();
    DMESGF("OUT LAST\r\n");

    while(1);
}