#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <psx/io.h>
#include <psx/gpu.h>
#include <psx/interrupts.h>

#include "primitives.h"

#define BIT(x) (1<<x)

void initGpu(void) {
    GP1_DO(ResetGpu, 0);
    GP1_DO(EnableDisplay, 0);

    GP0_DO(DrawMode,            BIT(10));
    GP0_DO(DrawAreaTopLeft,     (0<<10) | 0);
    GP0_DO(DrawAreaBottomRight, ((0+480/2)<<10) | (0 + 640/2));
    //GP0_DO(DrawAreaTopLeft,     0x002000);
    //GP0_DO(DrawAreaBottomRight, 0x039D3F);
    GP0_DO(DrawOffset,          0x000000);
    GP0NOP;
}

inline void glFlatTri2fp(const triangle_t *tri){
    GP0_DO(0x20, tri->color);
    GP[0] = tri->verts[0].yx;
    GP[0] = tri->verts[1].yx;
    GP[0] = tri->verts[2].yx;
}

inline void glFlatQuad2fp(const quad_t *quad){
    GP0_DO(0x20, quad->color);
    GP[0] = quad->verts[0].yx;
    GP[0] = quad->verts[1].yx;
    GP[0] = quad->verts[2].yx;
    GP[0] = quad->verts[3].yx;
}

inline void glFlatLine2fp(const line_t *line) {
    GP0_DO(ShadedLineOpaque, line->color0);
    GP[0] = line->v0.yx;
    GP[0] = line->color1;
    GP[0] = line->v1.yx;
    /*GP[0] = 0x55555555;*/
}

inline void glShadedQuad2fp(const line_t *line) {
    GP0_DO(ShadedQuadOpaque, line->color0);
    GP[0] = line->v0.yx;
    GP[0] = line->color1;
    GP[0] = line->v1.yx;
    ++line;
    GP[0] = line->color0;
    GP[0] = line->v0.yx;
    GP[0] = line->color1;
    GP[0] = line->v1.yx;
}

inline void glShadedWireframe2fp(const line_t *line, size_t n_lines) {
    const line_t *linep = line;

    GP0_DO(ShadedPolyLineOpaque, linep->color0);
    GP[0] = (unsigned)linep->v0.yx;
    GP[0] = linep->color1;
    GP[0] = (unsigned)linep->v1.yx;
    ++linep;
    for(size_t i = 0; i < n_lines-1; i++) {
        GP[0] = linep->color0;
        GP[0] = (unsigned)linep->v0.yx;
        GP[0] = linep->color1;
        GP[0] = (unsigned)linep->v1.yx;
        ++linep;
    }
    GP[0] = (unsigned)line->color0;
    GP[0] = line->v0.yx;
    GP[0] = (unsigned)line->color1;
    GP[0] = line->v1.yx;

    GP[0] = 0x55555555;
}

void glDrawTris(const triangle_t *tris, size_t len) {
    for(size_t i = 0; i < len; i++) {
        glFlatTri2fp(tris++);
    }
}

// todo don't use linked lists
struct list_node {
    struct list_node *tail;
    int head;
};

size_t length(const struct list_node *p) {
    size_t length = 0;
    if(p != NULL) {
        do {
            length++;
        } while((p = p->tail));
    }
    return length;
}

struct list_node l5 = {.tail=NULL};
struct list_node l4 = {.tail=&l5};
struct list_node l3 = {.tail=&l4};
struct list_node l2 = {.tail=&l3};
struct list_node l1 = {.tail=&l2};
struct list_node mylist = {.tail=&l1};

void initIRQ(short);

int main(void)
{
    //initIRQ(IRQ_VBLANK);
    //IRQ_MASK |= IRQ_VBLANK;
    initGpu();

    printf("yx: 0x%08X x: %04x y: %04x\n", tri1.verts[2].yx, tri1.verts[2].p.x, tri1.verts[2].p.y);
    printf("Length of list: %d\n", length((struct list_node*)&mylist));
    printf("Length of list: %d\n", length((struct list_node*)mylist.tail));
    printf("Length of list: %d\n", length((struct list_node*)mylist.tail->tail));
    printf("Length of list: %d\n", length((struct list_node*)&l5));
    printf("Length of list: %d\n", length(NULL));

    //uint16_t fb_page = 0;

    while(1) {
        waitVblank();

        GP1_DO(DmaDirection,0); // Disable DMA
        GP1_DO(ResetCommandBuffer,0);
        GP0_DO(ClearCache,0);

        waitGpu(Gp0CmdReady);
        GP0_DO(FillRectVram, 0x101010);
        GP[0] = 0x00000000;
        GP[0] = (230<<16) | (256);

        waitGpu(Gp0CmdReady);
        // 15bpp format: bbbbb---ggggg---rrrrr---
        glFlatTri2fp(&tri1);
        //waitGpu(Gp0CmdReady);

        glDrawTris(pyramid, pyramid_size);
        /*glFlatLine2fp(&myline);*/

        glShadedWireframe2fp(cube_face0,
                sizeof(cube_face0)/sizeof(*cube_face0));
        glShadedQuad2fp(cube_face1);
        /*glShadedWireframe2fp(cube_face1,
                sizeof(cube_face1)/sizeof(*cube_face1));*/
        glShadedWireframe2fp(cube_face2,
                sizeof(cube_face2)/sizeof(*cube_face2));
        glShadedWireframe2fp(cube_face3,
                sizeof(cube_face3)/sizeof(*cube_face3));

        //while (1);
        //fb_page ^= 224;
        //setDisplayOrigin(0, fb_page);
    }
    return 0;
}

