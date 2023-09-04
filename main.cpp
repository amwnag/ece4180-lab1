#include "mbed.h"

// The sinewave is created on this pin
// https://os.mbed.com/handbook/AnalogOut
AnalogOut aout(p18);

int main()
{
    const double pi = 3.141592653589793238462;
    double rads = 0.0;
    double sample = 0;
    
    while(1) {
        // sinewave output
        for (int i = 0; i < 360; i+=18) { // 20 samples per cycle
            rads = (pi * i) / 180.0f;
            sample = ((0.5f)*sin(rads + pi) + 0.5f);
            aout.write(sample);
        }
    }
}
 