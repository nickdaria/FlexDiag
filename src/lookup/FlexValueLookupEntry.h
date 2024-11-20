#pragma once

#include <stdint.h>
#include <stddef.h>
#include "FlexLookupBase.h"

typedef struct {
    FlexLookupBase base;                    //  Base lookup object
    uint8_t security_level_write;           //  Security level required to write to the pointer
    uint8_t* data;                          //  Pointer to the data
    const size_t len;                       //  Length of the data
} FlexValueLookupEntry;

/**
 * @brief Initilalize the struct values for a variable lookup table entry
 * 
 * @param entry Pointer to the entry to initialize
 * @param id Desired lookup ID
 * @param name Desired name
 * @param name_len Length of name
 * @param data Pointer to data
 * @param len Length of data
 */
void fd_init_value_entry(FlexValueLookupEntry* entry, const uint16_t id, const char* name, const size_t name_len, uint8_t* data, const size_t len);