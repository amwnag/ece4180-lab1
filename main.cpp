#include "mbed.h"
PwmOut myled(p21);
AnalogIn mypotentiometer(p20);

int main()
{
    while(1) {
        myled = mypotentiometer;
        wait(0.01);
    }
}