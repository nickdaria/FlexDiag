#pragma once

#include <stdint.h>
#include <stddef.h>
#include "FlexFunctionLookupEntry.h"

typedef struct {
    FlexFunctionLookupEntry* func_arr;      ///< Table of value lookup objects
    size_t arr_len;                         ///< Length of the value table
} FlexFunctionLookupTable;


void fd_init_function_table(FlexFunctionLookupEntry* func_arr, const size_t arr_len);