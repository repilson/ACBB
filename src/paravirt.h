#ifndef __PV_H
#define __PV_H

#include "config.h" // CONFIG_*
#include "biosvar.h" // GET_GLOBAL

// Types of paravirtualized platforms.
#define PF_QEMU     (1<<0)
#define PF_XEN      (1<<1)
#define PF_KVM      (1<<2)

// misc.c
extern int PlatformRunningOn;

static inline int runningOnQEMU(void) {
    return CONFIG_QEMU || (
        CONFIG_QEMU_HARDWARE && GET_GLOBAL(PlatformRunningOn) & PF_QEMU);
}
static inline int runningOnXen(void) {
    return CONFIG_XEN && GET_GLOBAL(PlatformRunningOn) & PF_XEN;
}
static inline int runningOnKVM(void) {
    return CONFIG_QEMU && GET_GLOBAL(PlatformRunningOn) & PF_KVM;
}

void qemu_ramsize_preinit(void);
void qemu_biostable_setup(void);
void qemu_cfg_preinit(void);
int qemu_cfg_show_boot_menu(void);
void qemu_cfg_get_uuid(u8 *uuid);
int qemu_cfg_irq0_override(void);
u16 qemu_cfg_acpi_additional_tables(void);
u16 qemu_cfg_next_acpi_table_len(void);
void *qemu_cfg_next_acpi_table_load(void *addr, u16 len);
u16 qemu_cfg_smbios_entries(void);
size_t qemu_cfg_smbios_load_field(int type, size_t offset, void *addr);
int qemu_cfg_smbios_load_external(int type, char **p, unsigned *nr_structs,
                                  unsigned *max_struct_size, char *end);
int qemu_cfg_get_numa_nodes(void);
void qemu_cfg_get_numa_data(u64 *data, int n);
u16 qemu_cfg_get_max_cpus(void);
u32 qemu_cfg_e820_entries(void);
void* qemu_cfg_e820_load_next(void *addr);
void qemu_romfile_init(void);

#endif
