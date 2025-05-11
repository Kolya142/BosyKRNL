#pragma once
#include <kernel.h>
#include <mod.h>

typedef struct framebuffer {
    void *buf;
    unsigned short width, height, bpp;
} framebuffer_t;

#define VIO_SET_RES 1
#define VIO_GET_RES 2
#define VIO_COUNT_DISPLAYS 3
#define VIO_PUT_PIXEL 4
