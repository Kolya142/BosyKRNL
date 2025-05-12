#include <fs/tarfs.h>

static int readoct(const char *s, int fw) {
    int n = 0;
    for (int i = 0; i < fw && s[i]; ++i) {
	char c = s[i];
	if (c >= '0' && '7' >= c) {
	    n = n * 8 + (c - '0');
	}
    }
    return n;
}


tarfs_header_t *tarfs_find_file(const char *fn, void *tarfs) {
    tarfs_header_t *hd = tarfs;
    if (kstrcmp(hd->h_magic, TARFS_MAGIC)) return NULL;
    while (hd->h_name[0]) {
	uintarch_t size = readoct(hd->h_size, 12);
	uintarch_t total = ((size + 511) / 512) * 512;
	if (!kstrcmp(hd->h_name, fn)) {
	    return hd;
	}
	hd = ((void*)((char*)hd) + 512) + total;
    }
    return NULL;
}
