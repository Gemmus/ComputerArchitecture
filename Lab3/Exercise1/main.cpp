#include <stdio.h>
#include "pico/stdlib.h"

// TODO: insert other definitions and declarations here
void tst(void)
{
    short a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    short *v = a;
    int k = 3;
    short temp = 0;
    temp = v[k];
    v[k] = v[k+1];
    v[k+1] = temp;
}

#if 0
void fail() {
    printf("Failed\n"); // set a break point here
    while(1) {
        tight_loop_contents();
    }
}

void ok() {
    printf("All ok\n"); // set a break point here
}
#endif

int main() {

    const uint led_pin = 22;

    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    // Initialize chosen serial port
    stdio_init_all();

    // TODO: insert code here
    tst();
#if 0
    // Loop forever
    while (true) {
        // Blink LED
        gpio_put(led_pin, true);
        sleep_ms(1000);
        gpio_put(led_pin, false);
        sleep_ms(1000);
    }
#endif
    return 0;
}
