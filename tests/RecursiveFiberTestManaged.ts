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

const FACTORIAL_N = 11
const THREADS_N = 4
let completionCount = 0;

function print_factorial(s: string) {
    serial.writeLine(s)
}

function factorial(n: number): number {
    let s = "Factorial depth: "
    s = s + n;

    print_factorial(s);

    loops.pause(10);
    return (n == 1) ? 1 : n * factorial(n - 1);
}

function factorial_fiber() {
    factorial(FACTORIAL_N);
    completionCount++;

    serial.writeLine("POP: " + completionCount)
}

serial.writeLine("HELLO");

control.deviceHeapPrint();

for (let i = 0; i < THREADS_N; i++)
    control.runInBackground(factorial_fiber);

while (completionCount != THREADS_N) {
    loops.pause(10)
}

control.deviceHeapPrint();

completionCount = 0;

for (let i = 0; i < THREADS_N; i++)
    control.runInBackground(factorial_fiber);

while (completionCount != THREADS_N) {
    loops.pause(10)
}

control.deviceHeapPrint();

serial.writeLine("OUT LAST")

while (true) { }


