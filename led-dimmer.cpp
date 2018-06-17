#include <bcm2835.h>

#include <iostream>

// Approximate output frequency is 300 Hz

const int out = 18;
const int pwm_channel = 0;
const int pwm_mode = 1;
const int pwm_divisor = 512;
const int pwm_range = 128;
int pwm_data = 1;

const int in1 = 26;
const int in2 = 19;

int main() {
    if (!bcm2835_init())
        return 1;

    bcm2835_gpio_fsel(out, BCM2835_GPIO_FSEL_ALT5);
    bcm2835_pwm_set_clock(pwm_divisor);
    bcm2835_pwm_set_mode(pwm_channel, pwm_mode, 1);

    bcm2835_gpio_fsel(in1, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(in2, BCM2835_GPIO_FSEL_INPT);

    bcm2835_gpio_set_pud(in1, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_set_pud(in2, BCM2835_GPIO_PUD_UP);

    bcm2835_pwm_set_range(pwm_channel, pwm_range);
    bcm2835_pwm_set_data(pwm_channel, pwm_data);

    while (1) {
        int lev1 = bcm2835_gpio_lev(in1);
        if (!lev1) {
            if (--pwm_data < 0) pwm_data = 0;
            bcm2835_delay(50);
            bcm2835_pwm_set_data(pwm_channel, pwm_data);
            std::cout << pwm_data << std::endl;
            continue;
        }

        int lev2 = bcm2835_gpio_lev(in2);
        if (!lev2) {
            if (++pwm_data > pwm_range) pwm_data = pwm_range;
            bcm2835_delay(50);
            bcm2835_pwm_set_data(pwm_channel, pwm_data);
            std::cout << pwm_data << std::endl;
        }
    }

    bcm2835_close();

    return 0;
}
