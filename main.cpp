#include "mbed.h"
#include "PinDetect.h"


PinDetect incr(p28);
PinDetect decr(p27);

PinDetect rSwitch(p15);
PinDetect gSwitch(p16);
PinDetect bSwitch(p17);

PwmOut rOut(p26);
PwmOut gOut(p25);
PwmOut bOut(p24);

PwmOut debugLED(LED4);
DigitalOut debugSwitch(LED1);

float volatile pwmVal;

void incrCallback(void) {
    pwmVal = (pwmVal >= 1) ? 1 : (pwmVal + 0.1);
    wait(0.1);
}

void decrCallback(void) {
    pwmVal = (pwmVal <= 0) ? 0 : (pwmVal - 0.1);
    wait(0.1);
}

int main() {
    pwmVal = 1;

    incr.mode(PullUp);
    decr.mode(PullUp);

    rSwitch.mode(PullUp);
    gSwitch.mode(PullUp);
    bSwitch.mode(PullUp);

    wait(0.001); // delay for initial pullup

    // interrupt callback function
    incr.attach_deasserted(&incrCallback);
    decr.attach_deasserted(&decrCallback);

    // sampling freq
    incr.setSampleFrequency();
    decr.setSampleFrequency();

    debugLED = 1;
    while (1) {
        rOut = rSwitch ? 0 : pwmVal; // check if grounded
        gOut = gSwitch ? 0 : pwmVal;
        bOut = bSwitch ? 0 : pwmVal;

        debugSwitch = rSwitch;

        debugLED = pwmVal;
        wait(1);
    }
}