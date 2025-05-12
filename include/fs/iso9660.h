#pragma once
#include <mod.h>

typedef struct iso9660_dir_entry {
    uint8_t length;
    uint8_t ext_attr_length;
    uint32_t extent_lba_le;
    uint32_t extent_lba_be;
    uint32_t data_length_le;
    uint32_t data_length_be;
    uint8_t date[7];
    uint8_t flags;
    uint8_t file_unit_size;
    uint8_t interleave_gap;
    uint16_t volume_seq_le;
    uint16_t volume_seq_be;
    uint8_t name_len;
    char name[];
} __attribute__((packed)) iso9660_dir_entry_t;

iso9660_dir_entry_t *iso9660_get(mod_t *drive, dev_t *dev, const char *name);    
