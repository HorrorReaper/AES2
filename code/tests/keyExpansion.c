#include "../src/aes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    u_int8_t * key = (u_int8_t *)malloc(16);
    u_int8_t * roundKeys = (u_int8_t *)malloc(176);

    u_int8_t check_round_key_1[176] = {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x62, 0x63, 0x63, 0x63,
        0x62, 0x63, 0x63, 0x63,
        0x62, 0x63, 0x63, 0x63,
        0x62, 0x63, 0x63, 0x63,
        0x9b, 0x98, 0x98, 0xc9,
        0xf9, 0xfb, 0xfb, 0xaa,
        0x9b, 0x98, 0x98, 0xc9,
        0xf9, 0xfb, 0xfb, 0xaa,
        0x90, 0x97, 0x34, 0x50,
        0x69, 0x6c, 0xcf, 0xfa,
        0xf2, 0xf4, 0x57, 0x33,
        0x0b, 0x0f, 0xac, 0x99,
        0xee, 0x06, 0xda, 0x7b,
        0x87, 0x6a, 0x15, 0x81,
        0x75, 0x9e, 0x42, 0xb2,
        0x7e, 0x91, 0xee, 0x2b,
        0x7f, 0x2e, 0x2b, 0x88,
        0xf8, 0x44, 0x3e, 0x09,
        0x8d, 0xda, 0x7c, 0xbb,
        0xf3, 0x4b, 0x92, 0x90,
        0xec, 0x61, 0x4b, 0x85,
        0x14, 0x25, 0x75, 0x8c,
        0x99, 0xff, 0x09, 0x37,
        0x6a, 0xb4, 0x9b, 0xa7,
        0x21, 0x75, 0x17, 0x87,
        0x35, 0x50, 0x62, 0x0b,
        0xac, 0xaf, 0x6b, 0x3c,
        0xc6, 0x1b, 0xf0, 0x9b,
        0x0e, 0xf9, 0x03, 0x33,
        0x3b, 0xa9, 0x61, 0x38,
        0x97, 0x06, 0x0a, 0x04,
        0x51, 0x1d, 0xfa, 0x9f,
        0xb1, 0xd4, 0xd8, 0xe2,
        0x8a, 0x7d, 0xb9, 0xda,
        0x1d, 0x7b, 0xb3, 0xde,
        0x4c, 0x66, 0x49, 0x41,
        0xb4, 0xef, 0x5b, 0xcb,
        0x3e, 0x92, 0xe2, 0x11,
        0x23, 0xe9, 0x51, 0xcf,
        0x6f, 0x8f, 0x18, 0x8e
    };

    memset(key, 0, 16);
    keyExpansion(key, roundKeys, 128);

    for (int i = 0; i < 176; i++)
    {
        if (roundKeys[i] != check_round_key_1[i])
        {
            printf("Error at index %d\n", i);
            printf("Expected: %x\n", check_round_key_1[i]);
            printf("Got: %x\n", roundKeys[i]);
            return 1;
        }
    }

    u_int8_t key_data[16] = {
        0x12, 0x34, 0x56, 0x78,
        0x9a, 0xbc, 0xde, 0xf0,
        0x12, 0x34, 0x56, 0x78,
        0x9a, 0xbc, 0xde, 0xf0
    };
    memcpy(key, key_data, 16);

    u_int8_t check_round_key_2[176] = {
        0x12, 0x34, 0x56, 0x78,
        0x9a, 0xbc, 0xde, 0xf0,
        0x12, 0x34, 0x56, 0x78,
        0x9a, 0xbc, 0xde, 0xf0,
        0x76, 0x29, 0xda, 0xc0,
        0xec, 0x95, 0x04, 0x30,
        0xfe, 0xa1, 0x52, 0x48,
        0x64, 0x1d, 0x8c, 0xb8,
        0xd0, 0x4d, 0xb6, 0x83,
        0x3c, 0xd8, 0xb2, 0xb3,
        0xc2, 0x79, 0xe0, 0xfb,
        0xa6, 0x64, 0x6c, 0x43,
        0x97, 0x1d, 0xac, 0xa7,
        0xab, 0xc5, 0x1e, 0x14,
        0x69, 0xbc, 0xfe, 0xef,
        0xcf, 0xd8, 0x92, 0xac,
        0xfe, 0x52, 0x3d, 0x2d,
        0x55, 0x97, 0x23, 0x39,
        0x3c, 0x2b, 0xdd, 0xd6,
        0xf3, 0xf3, 0x4f, 0x7a,
        0xe3, 0xd6, 0xe7, 0x20,
        0xb6, 0x41, 0xc4, 0x19,
        0x8a, 0x6a, 0x19, 0xcf,
        0x79, 0x99, 0x56, 0xb5,
        0x2d, 0x67, 0x32, 0x96,
        0x9b, 0x26, 0xf6, 0x8f,
        0x11, 0x4c, 0xef, 0x40,
        0x68, 0xd5, 0xb9, 0xf5,
        0x6e, 0x31, 0xd4, 0xd3,
        0xf5, 0x17, 0x22, 0x5c,
        0xe4, 0x5b, 0xcd, 0x1c,
        0x8c, 0x8e, 0x74, 0xe9,
        0xf7, 0xa3, 0xca, 0xb7,
        0x02, 0xb4, 0xe8, 0xeb,
        0xe6, 0xef, 0x25, 0xf7,
        0x6a, 0x61, 0x51, 0x1e,
        0x03, 0x72, 0xb8, 0xb5,
        0x01, 0xc6, 0x50, 0x5e,
        0xe7, 0x29, 0x75, 0xa9,
        0x8d, 0x48, 0x24, 0xb7,
        0x67, 0x44, 0x11, 0xe8,
        0x66, 0x82, 0x41, 0xb6,
        0x81, 0xab, 0x34, 0x1f,
        0x0c, 0xe3, 0x10, 0xa8
    };
    
    keyExpansion(key, roundKeys, 128);

    for (int i = 0; i < 176; i++)
    {
        if (roundKeys[i] != check_round_key_2[i])
        {
            printf("Error at index %d\n", i);
            printf("Expected: %x\n", check_round_key_2[i]);
            printf("Got: %x\n", roundKeys[i]);
            return 1;
        }
    }

    return 0;
}