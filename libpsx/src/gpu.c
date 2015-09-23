
#include <stdint.h>
#include <psx/gpu.h>

void setDisplayMode(unsigned mode) {
    GP1(0x08, mode);
}

void setDisplayOrigin(uint16_t x, uint16_t y) {
    //GP1(0x05, ((y & 0x1FF)<<10) | (x & 0x3FF));
    GP1(0x05, (y<<10) | x);
}

