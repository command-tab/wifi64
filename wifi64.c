#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>

// libdragon start
// libdragon make && cen wifi64.z64
// libdragon make && 64drive -c 6102 -v -l wifi64.z64

static resolution_t res = RESOLUTION_320x240;
static bitdepth_t bit = DEPTH_32_BPP;

/*
http://ultra64.ca/files/documentation/online-manuals/man/pro-man/pro09/index9.3.html

CPU virtual address translation takes place in either of two ways: via direct mapping,
or through the translation lookaside buffer (TLB). When running in kernel mode (as
applications do on the Nintendo 64 platform) the address ranges are:

32 Bit Kernel Mode Addressing

Beginning   Ending	    Name   Behavior
0X00000000  0X7FFFFFFF  KUSEG  TLB mapped
0X80000000  0X9FFFFFFF  KSEG0  Direct mapped, cached
0XA0000000  0XBFFFFFFF  KSEG1  Direct mapped, uncached
0XC0000000  0XDFFFFFFF  KSSEG  TLB mapped
0XE0000000  0XFFFFFFFF  KSEG3  TLB mapped
*/

#define UDEV 0x55444556

static inline uint32_t sixtyfourdrive_hardware_magic(void) {
    //return UDEV;
    return *(volatile const uint32_t *)0xB80002EC; // 0xA0000000 + 0x180002EC
}

static inline uint16_t sixtyfourdrive_button_status(void) {
    return *(volatile const uint16_t *)0xB80002F8; // 0xA0000000 + 0x180002F8
}

int main (void)
{
    // Enable interrupts on the CPU
    init_interrupts();

    // Initialize peripherals
    display_init(res, bit, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);
    console_init();

    console_set_render_mode(RENDER_MANUAL);

    int testv = 0;
    int has_64drive = 1;

    // Main loop
    while(has_64drive) {
        console_clear();

        // Detect 64drive hardware magic 'UDEV'
        const uint32_t magic = sixtyfourdrive_hardware_magic();
        if (magic != UDEV) {
            printf("64drive not detected. Halting.\n\n");
            has_64drive = 0;
            console_render();
            continue;
        }

        const uint16_t button_status = sixtyfourdrive_button_status();

        printf("Count          %d\n\n", testv++);
        printf("64drive button %u\n\n", button_status);
        console_render();
    }
}
