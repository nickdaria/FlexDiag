#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t security_level;         ///< User-controlled security level to read/execute: 0 default, 0xFF highest
    uint16_t id;                    ///< User-controlled ID to identify the object
    const size_t name_len;                ///< Length of the user-controlled name (0 for null-terminated)
    const char* name;               ///< Pointer to a string in program memory (NULL for none)
} FlexLookupBase;

/**
 * @brief Initializes a FlexLookupBase object with an explicit name length.
 *
 * This function sets up a FlexLookupBase structure, linking it to a name stored
 * in program memory. The name is not copied; the pointer is directly assigned.
 *
 * @param lookup Pointer to the FlexLookupBase structure to initialize.
 * @param id User-controlled ID for the object.
 * @param name Pointer to the name string (stored in program memory).
 * @param name_len Length of the name string
 */
void fd_init_lookup_base(FlexLookupBase* lookup, const uint16_t id, const char* name, const size_t name_len);