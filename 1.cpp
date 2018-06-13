#include <bcm2835.h>
#include <stdio.h>

const int pin = 18;
const int channel = 0;
const int span = 1000;

int main() {
    if (!bcm2835_init())
        return 1;

    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_ALT5);
    bcm2835_pwm_set_clock(8);
    bcm2835_pwm_set_mode(channel, 0, 1);
    bcm2835_pwm_set_range(channel, span);

    //while (1) {
        int data = 300;
        bcm2835_pwm_set_data(channel, data);
      //  bcm2835_delay(1000);
    //}

    bcm2835_close();
    return 0;
}
