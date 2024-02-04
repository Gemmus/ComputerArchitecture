#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>

#define EXERCISE1 // EXERCISE1 or EXERCISE2

__attribute__(( naked )) int prt(const char *a)
{
    // the pointer to a character array is passed to the
    // subroutine in R0
    // remember to follow AAPCS:
    // push any register above r3 at the beginning and pop the same registers at the end
    // note: lr needs to be pushed because we are calling another subroutine
    // cortex-M0 requires popping to PC if LR was pushed. See the code below
    asm volatile
            (
            "push { r4, lr } \n" // we need to save return address because we call another subroutine
            // r0 - r3 can (and will be) modified by putchar
            // so you have save the values yourself if you wish to keep
            // them safe. R4-R7 will not be modified by Board_UARTPutChar

            #ifdef EXERCISE1

            /*******************************/
            /* Beginning of inserted code: */
            /*******************************/

            "mov r4, r0 \n"

            /* Loops until '\0': */
            "loop_begin: \n"

            // Loads value to ro and increment address by one byte:
            "ldrb r0, [r4] \n"              // loads one byte size of value from r4
            "add r4, r4, #1 \n"             // moves r4 address by one byte

            // Checks if value is terminating zero, if yes, goes to loop_end:
            "cmp r0, #0 \n"                 // compares if r0 value is '\0'
            "beq loop_end \n"               // if equals, go to loop_end label

            // Checks if it's A-Z:
            "cmp r0, #65 \n"                // compares r0 value to 'A' (ASCII: 65)
            "blt not_uppercase \n"          // if less than, go to label not_uppercase
            "cmp r0, #90 \n"                // compares r0 value to 'Z' (ASCII: 90)
            "bgt not_uppercase \n"          // if greater than, go to label not_uppercase

            // Converts uppercase to lowercase:
            "add r0, r0, #32 \n"            // adds difference between ASCII codes of upper- and lowercase

            // If not uppercase or letter:
            "not_uppercase: \n"

            // Print character:
            "bl putchar \n"

            // Goes back to loop_begin:
            "bl loop_begin \n"

            /* Label when '\0' is met: */
            "loop_end: \n"

            /************************/
            /* End of inserted code */
            /************************/

            #endif

            #ifdef EXERCISE2

            /*******************************/
            /* Beginning of inserted code: */
            /*******************************/

            "mov r4, r0 \n"

            /* Loops until '\0': */
            "loop_begin: \n"

            // Loads value to ro and increment address by one byte:
            "ldrb r0, [r4] \n"              // loads one byte size of value from r4
            "add r4, r4, #1 \n"             // moves r4 address by one byte

            // Checks if value is terminating zero, if yes, goes to loop_end:
            "cmp r0, #0 \n"                 // compares if r0 value is '\0'
            "beq loop_end \n"               // if equals, go to loop_end label

            // Checks if it's A-Z, if not go to label not_uppercase:
            "cmp r0, #65 \n"                // compares r0 value to 'A' (ASCII: 65)
            "blt not_uppercase \n"          // if less than, go to label not_uppercase
            "cmp r0, #90 \n"                // compares r0 value to 'Z' (ASCII: 90)
            "bgt not_uppercase \n"          // if greater than, go to label not_uppercase

            // If uppercase, rotates 13 and checks if it should be rolled over:
            "add r0, r0, #13 \n"
            "cmp r0, #90 \n"
            "ble not_uppercase \n"
            "sub r0, r0, #26 \n"

            // If it was not uppercase, checks if it's a-z, if not go to label not_letter:
            "not_uppercase: \n"
            "cmp r0, #97 \n"                // compares r0 value to 'a' (ASCII: 97)
            "blt not_letter \n"             // if less than, go to label not_letter
            "cmp r0, #122 \n"                // compares r0 value to 'z' (ASCII: 122)
            "bgt not_letter \n"             // if greater than, go to label not_letter

            // If lowercase, rotates 13 and checks if it should be rolled over:
            "add r0, r0, #13 \n"
            "cmp r0, #122 \n"
            "ble not_letter \n"
            "sub r0, r0, #26 \n"

            // If not a letter, come to this label:
            "not_letter: \n"

            // Print character:
            "bl putchar \n"

            // Goes back to loop_begin:
            "bl loop_begin \n"

            /* Label when '\0' is met: */
            "loop_end: \n"

            /************************/
            /* End of inserted code */
            /************************/

            #endif

            "pop { r4, pc } \n" // cortex-M0 requires popping to PC if LR was pushed
        // popping to PC will cause return from subroutine (~same as "bx lr")
            );
}

void fail() {
    printf("Failed\n"); // set a break point here
    while(1) {
        tight_loop_contents();
    }
}

void ok() {
    printf("\nAll ok\n"); // set a break point here
}

int main(void) {

    const uint led_pin = 22;

    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    // Initialize chosen serial port
    stdio_init_all();

    // TODO: insert code here
    printf("\nExercise5\n");

    char test1[] = "Computer Architecture\n";
    char test2[] = "Computer Architecture\n";
    prt(test1);
    if(strcmp(test1, test2)) {
        fail(); // error - string modified
    }
    char test3[] = "Johnny Ca$h:Live @Folsom\n";
    char test4[] = "Johnny Ca$h:Live @Folsom\n";
    prt(test3);
    if(strcmp(test3, test4)) {
        fail(); // error - string modified
    }

    char test5[] = "If you like to gamble, I tell you I'm your man\n";
    char test6[] = "If you like to gamble, I tell you I'm your man\n";
    prt(test5);
    if(strcmp(test5, test6)) {
        fail(); // error - string modified
    }

    ok();

    // Loop forever
    while (true) {
        // Blink LED
        gpio_put(led_pin, true);
        sleep_ms(1000);
        gpio_put(led_pin, false);
        sleep_ms(1000);
    }
    return 0 ;
}
