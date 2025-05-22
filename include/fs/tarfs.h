#pragma once
#include <mod.h>

typedef struct tarfs_header {
    char h_name[100]
        ,h_mode[8]
	,h_uid[8]
	,h_gid[8]
	,h_size[12]
	,h_mtime[12]
	,h_chksum[8]
	,h_typeflag
	,h_linkname[100]
	,h_magic[6];
    char pad[512-263];
    /* there is more, but i really don't care */
} tarfs_header_t;

#define TARFS_MAGIC "ustar  "

#define TARFS_IF_REG  '0'
#define TARFS_IF_AREG 0
#define TARFS_IF_LINK '1'
#define TARFS_IF_SYM  '2'
#define TARFS_IF_CHR  '3'
#define TARFS_IF_BLK  '4'
#define TARFS_IF_DIR  '5'
#define TARFS_IF_FIFO '6'
#define TARFS_IF_CONT '7'


tarfs_header_t *tarfs_find_file(const char *fn, void *tarfs);

extern afs_t tarfs;
