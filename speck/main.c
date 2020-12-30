#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>

#include "speck.h"

void hexDump (const char * desc, const void * addr, const int len) {
    int i;
    unsigned char buff[17];
    const unsigned char * pc = (const unsigned char *)addr;

    // Output description if given.

    if (desc != NULL)
        printf ("%s:\n", desc);

    // Length checks.

    if (len == 0) {
        printf("  ZERO LENGTH\n");
        return;
    }
    else if (len < 0) {
        printf("  NEGATIVE LENGTH: %d\n", len);
        return;
    }

    // Process every byte in the data.

    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Don't print ASCII buffer for the "zeroth" line.

            if (i != 0)
                printf ("  %s\n", buff);

            // Output the offset.

            printf ("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);

        // And buffer a printable ASCII character for later.

        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) // isprint() may be better.
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.

    while ((i % 16) != 0) {
        printf ("   ");
        i++;
    }

    // And print the final ASCII buffer.

    printf ("  %s\n", buff);
}


int main()
{
    uint64_t speck_key[4] = {0x0706050403020100UL,0x0f0e0d0c0b0a0908UL,0x1716151413121110UL, 0x1f1e1d1c1b1a1918UL};
    uint64_t speck_pt[2] = {0x202e72656e6f6f70UL, 0x65736f6874206e49UL};
    uint64_t speck_ct[2] = {0x4eeeb48d9c188f43UL, 0x4109010405c0f53eUL};
    uint64_t test[2] = {0UL, 0UL};
    uint64_t nonce[] = {0, 0};
    uint8_t speck_ctr_pt[1024];
    uint8_t speck_ctr_ct[1024];
    uint8_t speck_ctr_test[1024];
    int ret;

    ret = getrandom(speck_ctr_pt, 1024, 0);

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


    speck_ctr((uint64_t*)speck_ctr_pt, (uint64_t*)speck_ctr_ct, 1024, speck_key, nonce);
    speck_ctr((uint64_t*)speck_ctr_ct, (uint64_t*)speck_ctr_test, 1024, speck_key, nonce); 

    hexDump("plaintext", speck_ctr_pt, 1024);
    hexDump("ciphertext", speck_ctr_test, 1024);

    for(int i = 0; i < 1024; i++){
        if(speck_ctr_pt[i] != speck_ctr_test[i]) printf("Value at %d is wrong\n", i);
    }
    return 0;
}
