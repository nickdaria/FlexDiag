#pragma once

#include <stdint.h>
#include <stddef.h>
#include "FlexLookupBase.h"

// Forward declaration of FlexDiagSession
typedef struct FlexDiagSession FlexDiagSession;

//  Callback for completed data rx
typedef void (*FlexFunctionCallback)(
    FlexDiagSession* session,
    uint8_t* param_data,
    const size_t param_len
);

typedef struct {
    FlexLookupBase base;                    //  Base lookup object
    FlexFunctionCallback function_callback; //  Callback for function execution
} FlexFunctionLookupEntry;

/**
 * @brief Initialize a function lookup entry with a callback.
 * 
 * @param entry Pointer to entry to initialize
 * @param callback Desired callback
 */
void fd_init_function_entry(FlexFunctionLookupEntry* entry, const uint16_t id, const char* name, const size_t name_len, FlexFunctionCallback callback);