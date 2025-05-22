#include "kernel.h"
#include "mod.h"
#include <fs/iso9660.h>

// FIXME

iso9660_dir_entry_t *iso9660_get(mod_t *drive, dev_t *dev, const char *name) {
    uint8_t iso[2048];
    uint8_t dir[2048];
    drive->ioctl(dev, 0, IO_CURSET, 2048 * 16, 0, 0, 0);
    drive->read(dev, 0, iso, 2048);

    drive->ioctl(dev, 0, IO_CURSET, 2048 * (*(uint32_t*)(iso + 156 + 2)), 0, 0, 0);
    drive->read(dev, 0, dir, 2048);

    uintarch_t s = kstrlen(name);
    for (uintarch_t off = 0; off < 2048;) {
        iso9660_dir_entry_t *entry = (iso9660_dir_entry_t*)&dir[off];
	if (!entry->length) break;
	if (entry->name_len == s + 2) {
	    int cmp = TRUE;
	    for (uintarch_t i = 0; i < s; ++i) {
			if (entry->name[i] == ';') {
				break;
			}
			if ((entry->name[i] >= 'A' && entry->name[i] <= 'Z' ? entry->name[i] - 'A' + 'a' : entry->name[i]) != name[i]) {
				cmp = FALSE;
				break;
			}
	    }
	    if (cmp) {
			return entry;
	    }
	}
	off += entry->length;
    }
    kputsa("not founded");
    return NULL;
}

static uintarch_t read(dev_t *dev, mod_t *drive, uintarch_t offset, const char *name, void *buf, uintarch_t count) {
    iso9660_dir_entry_t *dep = iso9660_get(drive, dev, name);
    if (!dep) return 0;
    iso9660_dir_entry_t de = *dep;
    if (de.data_length_le * 2048 <= offset) return 0;
    // TODO: Malloc it
    uintarch_t dlle = de.data_length_le * 2048;
    byte_t dbuf[1024*16];
    if (dlle > 1024*16) dlle = 1024*16;
    drive->ioctl(dev, 0, IO_CURSET, de.extent_lba_le * 2048, 0, 0, 0);
    drive->read(dev, 0, dbuf, dlle);

    kmemcpy(buf, dbuf + offset, count - offset);
    return count - offset;
}

afs_t iso9660fs = {
    .read = read
};
