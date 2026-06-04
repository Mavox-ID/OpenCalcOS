/*
    Mavox-ID | https://ye-a.pp.ua
    Copyright (C) 2026  Mavox-ID

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <os.h>
#include <stdint.h>
#include <libndls.h>

#include "atag.h"
#include "mmu.h"
#include "debug.h"

#define DEFAULT_KERNEL_LOCATION "/zCalc.tns"
#define DEFAULT_FILESYSTEM_LOCATION "/calcfs.tns"
#define DEFAULT_CMDLINE "earlyprintk debug keep_bootcon"
#define MACHINE_ID  3503
#define MAX_KERNEL_SIZE 0x400000
#define MAX_RAMDISK_SIZE 0x400000
#define PAGE_SIZE   4096

void wait_key_pressed(void);
void refresh_osscr(void);

void __crt0_exit(void) {
    puts("\n[!] Loader Panic: Unexpected exit.");
    puts("Press any key to reboot...");
    
    wait_key_pressed();
    refresh_osscr();
    
    volatile unsigned int *reset_reg = (unsigned int *)0x900B0000;
    *reset_reg = 0x01;
    
    while(1);
}

static void *ramdisk = NULL;
static int ramdiskSize = -1;

static int fileSize(const char * filename) {
    struct stat stats;
    if (stat(filename, &stats)) return -1;
    return stats.st_size;
}

static void loadRamdisk(const char * filename) {
    FILE *f = fopen(filename, "rb");
    int size;
    if (!f) {
        printk("No ramdisk found. Ignoring" NEWLINE);
        return;
    }
    if ( (size = fileSize(filename)) < 1 || size > MAX_RAMDISK_SIZE) {
        printk("Could not determine file size of %s" NEWLINE, filename);
        fclose(f);
        exit(-1);
    }
    ramdisk = malloc(size);
    if (!ramdisk) {
        fclose(f);
        printk("Could allocate %x bytes for ramdisk. Not loading ramdisk" NEWLINE, size);
        return;
    }
    fread(ramdisk, 1, MAX_RAMDISK_SIZE, f);
    fclose(f);
    ramdiskSize = size;
}

static void* loadKernel(const char * filename) {
    FILE *f = fopen(filename, "rb");
    int size;
    if (!f) {
        printk("Could not open kernel at %s" NEWLINE, filename);
        exit(-1);
    }
    if ( (size = fileSize(filename)) < 1 || size > MAX_KERNEL_SIZE) {
        printk("Could not determine file size of %s" NEWLINE, filename);
        fclose(f);
        exit(-1);
    }

    void * data = malloc(size);
    if (!data) {
        fclose(f);
        printk("Could allocate %x bytes for kernel" NEWLINE, size);
        exit(-1);
    }
    fread(data, 1, size, f);
    fclose(f);
    unsigned start = ((unsigned*)data)[10], end = ((unsigned*)data)[11];
    if ((unsigned int)(end - start) != (unsigned int)size) {
        ramdisk = (char*)data + (end - start);
        ramdiskSize = size - (end - start);
        printk("Found ramdisk appended to kernel of size %dbytes at %p" NEWLINE, size, (void*)ramdisk);
    }
    return data;
}

static void *buildParameters() {
    void *atag, *last;
    atagBegin(&atag, &last);

    atagAdd(&atag, &last, ATAG_MEM, /* size */ 0x4000000, /* start */ 0x10000000); //SDRAM
    //atagAdd(&atag, &last, ATAG_MEM, /* size */ 0x14000,   /* start */ 0xA4000000); //SRAM
    atagAdd(&atag, &last, ATAG_CMDLINE, DEFAULT_CMDLINE);

    if (ramdisk && ramdiskSize > 0) {
        printk("Added ATAGs for ramdisk" NEWLINE);
        atagAdd(&atag, &last, ATAG_RAMDISK, 0, MAX_RAMDISK_SIZE/1024, 0);
        atagAdd(&atag, &last, ATAG_INITRD2, 0x14000000-MAX_RAMDISK_SIZE, ramdiskSize);
    }

    atagEnd(&atag, &last);

    return atag;
}

static void reloc(char *dst, char *src, size_t size) {
    while (size--) *dst++ = *src++;
}

int main(int argc, char *argv[]) {
    void *parameters;
    char *kernel = DEFAULT_KERNEL_LOCATION;
    void (*entry)(int, int, void*);

    printk("==== TI-NSPIRE OCOS Loader ====" NEWLINE);
    if (argc > 1 && argv[1]) kernel = argv[1];
    entry = (void (*)(int, int, void*))loadKernel(kernel);
    printk("Kernel loaded to 0x%p" NEWLINE, (void*)entry);
    printk("Attempting to load CalcFS" NEWLINE);
    loadRamdisk(DEFAULT_FILESYSTEM_LOCATION);
    if (ramdisk) printk("CalcFS loaded to %p" NEWLINE, (void*)ramdisk);

    parameters = buildParameters();
    printk("ATAGs loaded to 0x%p" NEWLINE, (void*)parameters);
    printk("Moving ATAGs to 0x10000100" NEWLINE);
    reloc((char*)0x10000100, parameters, 0x4000-0x100);
    if (ramdisk) {
        printk("Moving ramdisk to 0x%x"NEWLINE, 0x14000000-MAX_RAMDISK_SIZE);
        reloc((char*)(0x14000000-MAX_RAMDISK_SIZE), ramdisk, ramdiskSize);
    }

    printk("OK, let's go!" NEWLINE);
    clear_cache();
    disableDcacheAndMmu();

    entry(0, MACHINE_ID, (void*)0x10000100);
    __builtin_unreachable();
}
