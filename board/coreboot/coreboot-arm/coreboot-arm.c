#include <asm/armv8/mmu.h>
#include <asm/io.h>
#include <cb_sysinfo.h>
#include <mapmem.h>

#define MAX_MEM_MAP_REGIONS 16

static struct mm_region
    coreboot_mem_map[MAX_MEM_MAP_REGIONS] __section(".data") = {0};
struct mm_region *mem_map = coreboot_mem_map;

int dram_init(void) {
	return coreboot_dram_init();
}

/*
 * This function looks for the highest region of memory lower than 4GB which
 * has enough space for U-Boot where U-Boot is aligned on a page boundary. It
 * overrides the default implementation found elsewhere which simply picks the
 * end of ram, wherever that may be. The location of the stack, the relocation
 * address, and how far U-Boot is moved by relocation are set in the global
 * data structure.
 */
phys_addr_t board_get_usable_ram_top(phys_size_t total_size)
{
    uintptr_t dest_addr = 0;
    int i;

    log_err("board_get_usable_ram_top().\n");
    for (i = 0; i < lib_sysinfo.n_memranges; i++) {
        struct memrange *memrange = &lib_sysinfo.memrange[i];
        /* Force U-Boot to relocate to a page aligned address. */
        uint64_t start = roundup(memrange->base, 1 << 12);
        uint64_t end = memrange->base + memrange->size;

        /* Ignore non-memory regions. */
        if (memrange->type != CB_MEM_RAM)
            continue;

        /* Filter memory over 4GB. */
        if (end > 0xffffffffULL)
            end = 0x100000000ULL;
        /* Skip this region if it's too small. */
        if (end - start < total_size)
            continue;

        /* Use this address if it's the largest so far. */
        if (end > dest_addr)
            dest_addr = end;
    }

    /* If no suitable area was found, return an error. */
    if (!dest_addr)
        printf("No available memory found for relocation");
    log_err("board_get_usable_ram_top() returns %#lx\n", (ulong)dest_addr);
    return (ulong)dest_addr;
}

void reset_cpu(void) { /* Stub */ };

int board_init(void) {
  printf("board_init().\n");
  // sc7180 display
  /*
  writel(0x1, 0x0AE6B800);
  lib_sysinfo.framebuffer->physical_address = readl(0x0AE05014);
  */
  return 0;
}

int board_late_init(void) {
  log_err("board_late_init().\n");
  return 0;
}

void enable_caches() {
    log_err("skip enable_caches().\n");
}
