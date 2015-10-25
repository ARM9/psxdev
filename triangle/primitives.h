#ifndef PRIMITIVES_H
#define PRIMITIVES_H

typedef struct {
    short x, y, z;
} vec3fp;

typedef union {
    unsigned yx; 
    struct {
        short x, y;
    } p;
} vec2fp;

typedef struct {
    unsigned color0;
    vec2fp v0;
    unsigned color1;
    vec2fp v1;
} line_t;

typedef struct {
    unsigned color;
    vec2fp verts[3];
} triangle_t;

typedef struct {
    unsigned color;
    vec2fp verts[4];
} quad_t;

triangle_t tri1 = { 0x808080,{ {.p={240, 100}}, {.p={540+40, 140}}, {.p={240-40, 140}} } };

triangle_t pyramid[] = {
    { 0xA08000,{ {.p={0x24, 0x20}}, {.p={0x44, 0x40}}, {.p={-20 , 0x49}} } },
    { 0x008000,{ {.p={0x80, -20 }}, {.p={0xa0, 0x20}}, {.p={0x60, 0x20}} } },
    { 0x000080,{ {.p={0x60, 210 }}, {.p={0xa0, 360 }}, {.p={0x20, 360 }} } }
};

size_t pyramid_size = sizeof(pyramid)*sizeof(*pyramid);

quad_t quad1 = { 0x000080, { {.p={0x10, 0x10}}, {.p={0x30, 0x10}}, {.p={0x30, 0x30}}, {.p={0x10, 0x30}} } };

line_t cube_face0[] =
{
    {
        0x0000ff,
        .v0.p={100, 100},
        0x00ff00,
        .v1.p={150, 100}
    },
    {
        0xff0000,
        .v0.p={150, 150},
        0xffff00,
        .v1.p={100, 150}
    }
};
line_t cube_face1[] =
{
    {
        0x00ffff,
        .v0.p={110, 110},
        0xff00ff,
        .v1.p={140, 110}
    },
    {
        0x0000ff,
        .v0.p={110, 140},
        0xf0f00f,
        .v1.p={140, 140}
    }
};
line_t cube_face2[] =
{
    {
        0x0000ff,
        .v0.p={100, 100},
        0x00ffff,
        .v1.p={110, 110}
    },
    {
        0xf0f00f,
        .v0.p={110, 140},
        0xffff00,
        .v1.p={100, 150}
    }
};
line_t cube_face3[] =
{
    {
        0xff00ff,
        .v0.p={140, 110},
        0x00ff00,
        .v1.p={150, 100}
    },
    {
        0xff0000,
        .v0.p={150, 150},
        0x0000ff,
        .v1.p={140, 140}
    }
};

line_t myline = { .color0=0x00ff0000, .v0={.p.x=20,.p.y=20},
                  .color1=0x000000ff, .v1={.p.x=50,.p.y=40} };

#endif
