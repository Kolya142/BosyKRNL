#pragma once
#include <kernel.h>

#define MOD_CAUSE_SYSTEM_FINISH 0
#define MOD_CAUSE_CPU_ERROR 1

#define MOD_FLAGS_SYSTEM (1 << 0)
#define MOD_FLAGS_FILESYSTEM (1 << 1)
#define MOD_FLAGS_DISK (1 << 2)
#define MOD_FLAGS_VIDEO (1 << 3)
#define MOD_FLAGS_CHAROUT (1 << 4)
#define MOD_FLAGS_OTHER (1 << 5)

#define EPERM 0
#define ENOTSUP 1
#define ENOSYS 2
#define EINVAL 3

#define IO_CURSET 0

typedef uintmax_t dev_t;

#define FS_RW_ARGS uintmax_t fd, void *buf, uintmax_t count

typedef struct mod {
    void(*load)(dev_t dev);
    int32_t(*unload)(dev_t dev, int32_t cause);
    uintmax_t(*read)(dev_t dev, FS_RW_ARGS);
    uintmax_t(*write)(dev_t dev, FS_RW_ARGS);
    uintmax_t(*ioctl)(dev_t dev, uintmax_t fd, uint32_t type, uintmax_t a, uintmax_t b, uintmax_t c, uintmax_t d);
    // uintmax_t(*tty)(dev_t dev); 
    uint32_t flags;
} mod_t;
