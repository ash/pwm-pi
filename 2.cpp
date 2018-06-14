#include <bcm2835.h>
#include <stdio.h>

const int pin = 19;
const int channel = 1;
const int divisor = 1024;
const int range = 300;
const int data = 50;

int main() {
    if (!bcm2835_init())
        return 1;

    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_ALT5);
    bcm2835_pwm_set_clock(divisor);
    bcm2835_pwm_set_mode(channel, 1, 1);

    bcm2835_pwm_set_range(channel, range);
    bcm2835_pwm_set_data(channel, data);

    bcm2835_close();
    return 0;
}
