#include <mod.h>

static uintarch_t get_hardware_flags(uintarch_t krnlflags) {
    uintarch_t flags = 0;
    if ((krnlflags & (MEMDEV_READ | MEMDEV_WRITE)) == (MEMDEV_READ | MEMDEV_WRITE)) {
	flags |= 2;
    }
    if (krnlflags & MEMDEV_PRESENT) {
	flags |= 1;
    }
    if (krnlflags & MEMDEV_USER) {
	flags |= 4;
    }
    return flags;
}

static volatile uint32_t pd[1024] __attribute__((used)) __attribute__((aligned(4096)));
static volatile uint32_t pt[1024*4096] __attribute__((used)) __attribute__((aligned(4096)));

volatile void init_paging() {
    for (uint32_t i = 0; i < 1024*1024; ++i) {
	pt[i] = (i * 4096) | 3;
    }
    for (uint32_t i = 0; i < 1024; ++i) {
	pd[i] = ((uint32_t)&pt[i * 1024]) | 3;
    }

    asm volatile (
	"mov %0, %%eax\n"
	"mov %%eax, %%cr3\n"

	"mov %%cr0, %%eax\n"
	"or $0x80000000, %%eax\n"
	"mov %%eax, %%cr0\n"
	:: "r"(pd)
	: "eax", "memory"
    );
}

static void invlpg(uint32_t page) {
    asm volatile (
	"mov %0, %%eax\n"
	"invlpg (%%eax)"
	:: "r"(page)
	: "eax", "memory"
    );
}

static uintarch_t map_page(uintarch_t real, uintarch_t virt, uintarch_t flags) {
    uint32_t pdid = virt >> 22;
    uint32_t ptid = (virt >> 12) & 0x3FF;
    uint32_t *_pt = (uint32_t *)(pd[pdid] & ~0xFFF);
    _pt[ptid] = real | flags;
    invlpg(virt);
    return virt | flags;
}

static uint8_t pat[1024 * 1024 / 8];

static uintarch_t alloc_page() {
    for (uint32_t i = 0; i < 1024 * 1024 / 8; ++i) {
	if (pat[i] != 0xFF) {
	    uint32_t j = __builtin_ffs(~pat[i]) - 1;
	    uint32_t k = i * 8 + j;
	    pat[i] |= 1 << j;
	    return 1024*1024*1024 + k * 4096;
	    break;
	}
    }
    return NULL;
}

memorydev_t paging = {
    .page_size = 0x1000,
    .get_hardware_flags = get_hardware_flags,
    .map_page = map_page,
    .alloc_page = alloc_page
};
