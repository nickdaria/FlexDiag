#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct {
    const uint8_t security_level;   ///< User-controlled security level to read/execute: 0 disabled, 1 default/custom check implemented, 0xFF highest
    const uint16_t id;              ///< User-controlled ID to identify the object
    const char* name;               ///< Pointer to a string in program memory (NULL for none)
} FlexLookupBase;