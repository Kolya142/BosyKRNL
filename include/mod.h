#pragma once
#include <kernel.h>

#define MOD_CAUSE_SYSTEM_FINISH 0
#define MOD_CAUSE_CPU_ERROR 1

#define MOD_FLAGS_SYSTEM (1 << 0)
#define MOD_FLAGS_FILESYSTEM (1 << 1)
#define MOD_FLAGS_DISK (1 << 2)
#define MOD_FLAGS_VIDEO (1 << 3)
#define MOD_FLAGS_CHAROUT (1 << 4)
#define MOD_FLAGS_CONTROLLER (1 << 5)
#define MOD_FLAGS_DEBUGONLY (1 << 6)
#define MOD_FLAGS_OTHER (1 << 7)

#define EPERM -1
#define ENOTSUP -2
#define ENOSYS -3
#define EINVAL -4

#define IO_CURSET 0

typedef struct dev {
    struct mod_t *drive;
    void *data;
    uintarch_t id;
} dev_t;

#define FS_RW_ARGS uintarch_t fd, void *buf, uintarch_t count

typedef struct mod {
    void(*load)(dev_t *dev);
    int32_t(*unload)(dev_t *dev, int32_t cause);
    uintarch_t(*open)(dev_t *dev, const char *fn, int flags);
    void(*close)(dev_t *dev, uintarch_t fd);
    uintarch_t(*read)(dev_t *dev, FS_RW_ARGS);
    uintarch_t(*write)(dev_t *dev, FS_RW_ARGS);
    uintarch_t(*ioctl)(dev_t *dev, uintarch_t fd, uint32_t type, uintarch_t a, uintarch_t b, uintarch_t c, uintarch_t d);
    uintarch_t(*tty)(dev_t *dev); 
    uint32_t flags;
} mod_t;

typedef struct afs {
    void(*load)(dev_t *dev, mod_t *drive);
    int32_t(*unload)(dev_t *dev, int32_t cause);
    uintarch_t(*read)(dev_t *dev, mod_t *drive, uintarch_t offset, const char *name, void *buf, uintarch_t count);
    uintarch_t(*write)(dev_t *dev, mod_t *drive, uintarch_t offset, const char *name, void *buf, uintarch_t count);
    uintarch_t(*ioctl)(dev_t *dev, mod_t *drive, uintarch_t fd, uint32_t type, uintarch_t a, uintarch_t b, uintarch_t c, uintarch_t d);
} afs_t;

#define MEMDEV_READ 1
#define MEMDEV_WRITE 2
#define MEMDEV_EXEC 4
#define MEMDEV_PRESENT 8
#define MEMDEV_USER 16
// ...

typedef struct memorydev {
    uintarch_t page_size;
    uintarch_t(*get_hardware_flags)(uintarch_t krnlflags);
    uintarch_t(*alloc_page)();
    uintarch_t(*map_page)(uintarch_t real, uintarch_t virt, uintarch_t flags);
} memorydev_t;

#define MODSC 512
#define DEVSC 512

extern mod_t *mods[MODSC];
extern dev_t devs[DEVSC];
