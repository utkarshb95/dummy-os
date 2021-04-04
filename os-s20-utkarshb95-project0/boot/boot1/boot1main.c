/*
 * Filename: boot1main.c
 * Description:
 *  - This is the main section of the second stage bootloader.
 *  - This finds the first bootable partition, parses the physical memory map,
 *    loads the kernel to the first bootable partition, and correctly transfers
 *    control to the 'exec_kernel' function.
 */

#include <boot1lib.h>

mboot_info_t * parse_e820(bios_smap_t *smap);
uint32_t load_kernel(uint32_t dkernel);

//arg1: return value from load_kernel()
//arg2: mboot_info which is defined below
extern void exec_kernel(uint32_t, mboot_info_t *);

mboot_info_t mboot_info =
    { .flags = (1 << 6), };


/* boot1main
 *
 *  mbr_t * mbr: pointer to the loaded boot sector (i.e. boot0)
 *  bios_smap_t *smap: the detected physical memory map
 *
 */
void
boot1main (mbr_t * mbr, bios_smap_t *smap)
{
    /* Roll sets the row we will print on for the VGA, this function is defined in the provided, boot1lib files. */
    roll(2);
    /* Since we can't use the standard C library yet, we have to directly print to the VGA to get printed output.*/
    putline("Start boot1 main ...");

    /*
     *  YOUR CODE HERE
     *  Functions parse_e820(), load_kernel(), and exec_kernel() are provided.
     *  Utilize them to implement the functionality of boot1main described above.
     */
    int i;
    uint32_t bootable_lba = 0;
    for (i = 0; i < 4; i++)
    {
      if ( mbr->partition[i].bootable == BOOTABLE_PARTITION)
        {
        bootable_lba = mbr->partition[i].first_lba;
        break;
        }
    }
    parse_e820(smap);

    /* exec_kernel should never return */
    if(i==4)
      panic ("Fail to load kernel.");

    putline ("Load kernel ...\n");
    uint32_t entry = load_kernel(bootable_lba);
    putline ("Start kernel ...\n");
    exec_kernel (entry, &mboot_info);

}

#define ELFHDR      ((elfhdr *) 0x20000)

uint32_t
load_kernel(uint32_t dkernel) // dkernel is the first_lba field of the partition table entry of the bootable partition
{
    // load kernel from the beginning of the first bootable partition
    proghdr *ph, *eph;

    readsection((uint32_t) ELFHDR, SECTOR_SIZE * 8, 0, dkernel);

    // is this a valid ELF?
    if (ELFHDR->e_magic != ELF_MAGIC)
        panic ("Kernel is not a valid elf.");

    // load each program segment (ignores ph flags)
    ph = (proghdr *) ((uint8_t *) ELFHDR + ELFHDR->e_phoff);
    eph = ph + ELFHDR->e_phnum;

    for (; ph < eph; ph++)
    {
        readsection(ph->p_va, ph->p_memsz, ph->p_offset, dkernel);
    }

    return (ELFHDR->e_entry & 0xFFFFFF);
}

mboot_info_t *parse_e820 (bios_smap_t *smap)
{
    bios_smap_t *p;
    uint32_t mmap_len;
    p = smap;
    mmap_len = 0;
    putline ("* E820 Memory Map *");
    while (p->base_addr != 0 || p->length != 0 || p->type != 0)
    {
        puti (p->base_addr);
        p ++;
        mmap_len += sizeof(bios_smap_t);
    }
    mboot_info.mmap_length = mmap_len;
    mboot_info.mmap_addr = (uint32_t) smap;
    return &mboot_info;
}
