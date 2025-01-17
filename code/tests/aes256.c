#include "../src/aes.h"
#include <stdio.h>
#include <string.h>

int main() {
    uint8_t iv[16] = {
        0xf5, 0x8c, 0x4c, 0x04,
        0xd6, 0xe5, 0xf1, 0xba,
        0x77, 0x9e, 0xab, 0xfb,
        0x5f, 0x7b, 0xfb, 0xd6
    };
    uint8_t key[32] = {
        0x60, 0x3d, 0xeb, 0x10,
        0x15, 0xca, 0x71, 0xbe,
        0x2b, 0x73, 0xae, 0xf0,
        0x85, 0x7d, 0x77, 0x81,
        0x1f, 0x35, 0x2c, 0x07,
        0x3b, 0x61, 0x08, 0xd7,
        0x2d, 0x98, 0x10, 0xa3,
        0x09, 0x14, 0xdf, 0xf4
    };
    uint8_t input[64] = {
        0x94, 0x06, 0xb8, 0x2f,
        0x18, 0x92, 0x23, 0xbf,
        0x36, 0xed, 0xa4, 0x39,
        0x98, 0x38, 0x00, 0x4b,
        0x29, 0xce, 0xd5, 0x2d,
        0x93, 0x83, 0x9d, 0x14,
        0x65, 0xf1, 0x99, 0x71,
        0xbc, 0x1a, 0x7f, 0xee,
        0x52, 0x20, 0x83, 0x85,
        0x97, 0x14, 0x4e, 0x78,
        0xf4, 0x8a, 0x6f, 0xb2,
        0x81, 0x5c, 0x68, 0x9e,
        0xa4, 0x79, 0xd0, 0x11,
        0xf1, 0x70, 0xed, 0x28,
        0xce, 0x56, 0xa2, 0x2d,
        0xea, 0x84, 0xbb, 0x33
    };
    uint8_t source[64];
    memcpy(source, input, 64);
    uint8_t expected[64] = {
        0x56, 0x7c, 0x61, 0x85,
        0x94, 0xac, 0x28, 0x94,
        0xee, 0xac, 0x9a, 0xc8,
        0x9b, 0xa0, 0x61, 0x46,
        0x66, 0xb6, 0x45, 0xd2,
        0x25, 0x8e, 0x84, 0x87,
        0x52, 0x5c, 0x66, 0xb9,
        0x65, 0xc2, 0xb9, 0x88,
        0x5f, 0xe5, 0x48, 0xf5,
        0xd4, 0xb5, 0xed, 0x93,
        0xdd, 0xd9, 0x62, 0x08,
        0x8e, 0x12, 0xe6, 0x3a,
        0x37, 0x63, 0xd2, 0x44,
        0x30, 0xfb, 0xb7, 0x58,
        0xab, 0xc9, 0x40, 0xf3,
        0x64, 0x68, 0xf2, 0x38
    };

    cbc_encrypt(input, key, 256, iv, 64);

    for (int i = 0; i < 63; i++) {
        {
            if (input[i] != expected[i]) {
                printf("Error at index %d\n", i);
                printf("Expected: %x\n", expected[i]);
                printf("Got: %x\n", input[i]);
                return 1;
            }
        }
    }

    cbc_decrypt(input, key, 256, iv, 64);

    for (int i = 0; i < 63; i++) {
        {
            if (input[i] != source[i]) {
                printf("Error at index %d\n", i);
                printf("Expected: %x\n", source[i]);
                printf("Got: %x\n", input[i]);
                return 1;
            }
        }
    }
    return 0;
}