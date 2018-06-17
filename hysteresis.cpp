#include <bcm2835.h>
#include <iostream>
#include <bitset>

using namespace std;

// hyst == 1: turn hysteresis on
// hyst == 0: turn hysteresis off
const int hyst = 0;

const int pin = 21;

int main() {
    if (!bcm2835_init()) {
        return 1;
    }

    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
    uint32_t* gpioBASE = bcm2835_regbase(BCM2835_REGBASE_GPIO);

    uint32_t pads = bcm2835_peri_read(bcm2835_pads + BCM2835_PADS_GPIO_0_27 / 4);
    cout << "Current pads value:\t" << bitset<32>(pads) << endl;

    uint32_t new_pads = pads;
    if (hyst)
        new_pads |= 1UL << 3;
    else
        new_pads &= ~(1UL << 3);

    new_pads &= 0x00FFFFFF;
    new_pads |= 0x5A000000;
    cout << "Setting new value:\t" << bitset<32>(new_pads) << endl;

    bcm2835_peri_write(bcm2835_pads + BCM2835_PADS_GPIO_0_27 / 4, new_pads);
    pads = bcm2835_peri_read(bcm2835_pads + BCM2835_PADS_GPIO_0_27 / 4);
    cout << "New pads reg value:\t" << bitset<32>(pads) << endl;

    while(1) {
        int lev = bcm2835_gpio_lev(pin);
        cout << lev << '\r';
    }

    return 0;
}
