#include <bcm2835.h>
//#include <iostream>

const int in = 21;
const int out = 20;

const int in1 = 26;
const int in2 = 19;

int N = 20;           // % of the lightness; min 20%
const int Nmin = 20;
const int Nmax = 100;

const int T2 = 10000; // us = 1/2 period
const int P = 2000;   // pulse width in us

int cycle = 0;

int delta() {
    if (N < 30) return 1;
    if (N < 50) return 3;
    return 10;
}

void check_buttons() {
    if (cycle) return;

    int lev1 = bcm2835_gpio_lev(in1);
    if (!lev1) {
        N -= delta();
        if (N < Nmin) N = 0;
        cycle = 20;
        // std::cout << N << std::endl;
    }

    int lev2 = bcm2835_gpio_lev(in2);
    if (!lev2) {
        N += delta();
        if (N < Nmin) N = Nmin;
        else if (N > Nmax) N = Nmax;
        cycle = 20;
       // std::cout << N << std::endl;
    }
}

int main() {
    if (!bcm2835_init()) {
        return 1;
    }

    bcm2835_gpio_fsel(in, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(out, BCM2835_GPIO_FSEL_OUTP);

    bcm2835_gpio_fsel(in1, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(in2, BCM2835_GPIO_FSEL_INPT);

    bcm2835_gpio_set_pud(in1, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_set_pud(in2, BCM2835_GPIO_PUD_UP);

    int prev = -1;

    while(1) {
        check_buttons();        

        int lev = bcm2835_gpio_lev(in);

        if (lev == 1 && prev == 0) {
            bcm2835_delayMicroseconds(10);
            int lev1 = bcm2835_gpio_lev(in);
            if (lev1) {
                if (cycle) cycle--;

                if (N > 0) {
                    int delta = T2 * (100 - N) / 100;
                    if (delta) bcm2835_delayMicroseconds(delta);
                    bcm2835_gpio_set(out);
                    bcm2835_delayMicroseconds(P);
                    bcm2835_gpio_clr(out);

                    bcm2835_delayMicroseconds(T2 - P);
                    bcm2835_gpio_set(out);
                    bcm2835_delayMicroseconds(P);
                    bcm2835_gpio_clr(out);
                }
                else {
                    bcm2835_delayMicroseconds(T2);
                }
            }
        }

        prev = lev;
    }

    return 0;
}
