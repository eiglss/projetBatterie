#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "drivers/mpu9250.h"
#include "drivers/gpio.h"

int main(void)
{
    /* local declaration */

    /* initialization */
    init_platform();
    /* Program statement */
    printf("Hello world!\n");
    gpio_write(GPIO_LED, 0x0001);
    cleanup_platform();
    return EXIT_SUCCESS;
}
