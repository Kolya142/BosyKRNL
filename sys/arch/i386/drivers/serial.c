#include <arch/x86/drivers/serial.h>

void serial1_load(dev_t *dev) {}
uintarch_t serial1_write(dev_t *dev, FS_RW_ARGS) {}

mod_t serial1 = {
    .load = serial1_load,
    .write = serial1_write,
    .flags = MOD_FLAGS_CHAROUT,
};
