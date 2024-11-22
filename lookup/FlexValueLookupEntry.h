#pragma once

#include <stdint.h>
#include <stddef.h>
#include "FlexLookupBase.h"

typedef struct {
    const FlexLookupBase base;                    //  Base lookup object
    const uint8_t security_level_write;           //  Security level required to write to the pointer
    uint8_t* data;                          //  Pointer to the data
    const size_t len;                       //  Length of the data
} FlexValueLookupEntry;