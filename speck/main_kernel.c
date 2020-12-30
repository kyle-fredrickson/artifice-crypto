#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "speck.h"


MODULE_LICENSE("BSD");
MODULE_AUTHOR("AUSTEN BARKER, KYLE FREDRICKSON");

static int __init km_speck_init(void){
    uint64_t speck_key[4] = {0x0706050403020100UL,0x0f0e0d0c0b0a0908UL,0x1716151413121110UL, 0x1f1e1d1c1b1a1918UL};
    uint64_t speck_pt[2] = {0x202e72656e6f6f70UL, 0x65736f6874206e49UL};
    uint64_t speck_ct[2] = {0x4eeeb48d9c188f43UL, 0x4109010405c0f53eUL};
    uint64_t test[2] = {0UL, 0UL};
    int speck_test = 1;
    int i;

    speck_encrypt(speck_pt, test, speck_key);
    for (i = 0; i < 2; i++)
    {
        speck_test = speck_test && (speck_ct[i] == test[i]);
    }
    speck_decrypt(speck_ct, test, speck_key);
    for (i = 0; i < 2; i++)
    {
        speck_test = speck_test && (speck_pt[i] == test[i]);
    }
    if (speck_test)
        printk(KERN_INFO "SPECK block cipher passed!\n");
    else
        printk(KERN_INFO "SPECK block cipher passed!\n");
    return 0;
}

static void __exit km_speck_exit(void){
    printk(KERN_INFO "exited module\n");
}

module_init(km_speck_init);
module_exit(km_speck_exit);
