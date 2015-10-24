
#include <stdint.h>
#include <psx/gpu.h>

void setDisplayMode(unsigned mode) {
    GP1_DO(DisplayMode, mode);
}

void setDisplayOrigin(uint16_t x, uint16_t y) {
    // probably neglible overhead
    //GP1_DO(0x05, ((y & 0x1FF)<<10) | (x & 0x3FF));
    GP1_DO(DisplayArea, (y<<10) | x);
}

inline void waitGpu(unsigned status) {
    while((GP[1] & status) == 0);
}

