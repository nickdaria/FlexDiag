#pragma once

#include <stdint.h>
#include <stddef.h>
#include "FlexValueLookupEntry.h"

typedef struct {
    FlexValueLookupEntry* value_arr;    ///< Table of value lookup objects
    size_t arr_len;               ///< Length of the value table
} FlexValueLookupTable;


void fd_init_value_table(FlexValueLookupEntry* value_arr, const size_t arr_len);