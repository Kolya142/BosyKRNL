#include <arch/x86/drivers/vesa.h>

void vesa_load(dev_t dev) {
    ((short*)0xB8000)[0] = 0x0130;
}

mod_t mod_vesa = {
    .load = vesa_load,
};
