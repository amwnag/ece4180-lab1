#include "mbed.h"
#include "mbed.h"
#include "PinDetect.h"

PinDetect incr(p24);
PinDetect decr(p23);

PwmOut boardLED(LED1);
DigitalOut debugLED(LED4);

float volatile pwmVal;

void incrCallback(void) {
    pwmVal = (pwmVal >= 1) ? 1 : (pwmVal + 0.1);
    boardLED = pwmVal;
    wait(0.1);
}

void decrCallback(void) {
    pwmVal = (pwmVal <= 0) ? 0 : (pwmVal - 0.1);
    boardLED = pwmVal;
    wait(0.1);
}

int main() {
    pwmVal = 1;
    boardLED = pwmVal;

    incr.mode(PullUp);
    decr.mode(PullUp);
    wait(0.001); // delay for initial pullup

    // interrupt callback function
    incr.attach_deasserted(&incrCallback);
    decr.attach_deasserted(&decrCallback);

    // sampling freq
    incr.setSampleFrequency();
    decr.setSampleFrequency();

    debugLED = 1;
    while (1) {
        debugLED = !debugLED;
        wait(1);
    }
}