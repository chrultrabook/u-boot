#include <asm/armv8/mmu.h>
#include <asm/io.h>
#include <cb_sysinfo.h>
#include <mapmem.h>

#define MAX_MEM_MAP_REGIONS 16

static struct mm_region
    coreboot_mem_map[MAX_MEM_MAP_REGIONS] __section(".data") = {0};
struct mm_region *mem_map = coreboot_mem_map;

int dram_init(void) { return coreboot_dram_init(); }

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
