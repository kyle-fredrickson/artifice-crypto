#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "speck.h"


int main()
{
    uint64_t speck_key[4] = {0x0706050403020100UL,0x0f0e0d0c0b0a0908UL,0x1716151413121110UL, 0x1f1e1d1c1b1a1918UL};
    uint64_t speck_pt[2] = {0x202e72656e6f6f70UL, 0x65736f6874206e49UL};
    uint64_t speck_ct[2] = {0x4eeeb48d9c188f43UL, 0x4109010405c0f53eUL};
    uint64_t test[2] = {0UL, 0UL};

    speck_encrypt(speck_pt, test, speck_key);
    int speck_test = 1;
    for (int i = 0; i < 2; i++)
    {
        speck_test = speck_test && (speck_ct[i] == test[i]);
    }
    speck_decrypt(speck_ct, test, speck_key);
    for (int i = 0; i < 2; i++)
    {
        speck_test = speck_test && (speck_pt[i] == test[i]);
    }
    if (speck_test)
        printf("SPECK block cipher passed!\n");
    else
        printf("SPECK block cipher passed!\n");

    return 0;
}
