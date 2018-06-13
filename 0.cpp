#include <bcm2835.h>
#include <stdio.h>

int main() {
    if (!bcm2835_init())
        return 1;

    bcm2835_gpio_fsel(18, BCM2835_GPIO_FSEL_ALT5);
    bcm2835_pwm_set_clock(8);
    bcm2835_pwm_set_mode(0, 0, 1);
    bcm2835_pwm_set_range(0, 1000);

    bcm2835_pwm_set_data(0, 300);

    bcm2835_close();
    return 0;
}
