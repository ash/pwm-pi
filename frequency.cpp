#include <bcm2835.h>
#include <iostream>
#include <sys/time.h>

using namespace std;

const int pin = 21;

int main() {
    if (!bcm2835_init()) {
        return 1;
    }

    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);

    int n = 0;
    int prev = -1;

    struct timeval tp;
    gettimeofday(&tp, NULL);
    long long t0_ms = (long long) tp.tv_sec * 1000L + tp.tv_usec / 1000;

    while(1) {
        int lev = bcm2835_gpio_lev(pin);

        if (lev == 1 && prev == 0) {
            n++;
        }
        if (n == 1000) {
            break;
        }

        prev = lev;

        bcm2835_delay(1);
    }

    gettimeofday(&tp, NULL);
    long long t_ms = (long long) tp.tv_sec * 1000L + tp.tv_usec / 1000;

    double t = (t_ms - t0_ms) / 1000.0;

    cout << n << " pulses in " << t << " seconds" << endl;
    cout << "f = " << (double) n / t << " Hz" <<endl;

    return 0;
}
