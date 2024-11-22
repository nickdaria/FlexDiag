#pragma once

#include <stdint.h>
#include <stddef.h>
#include "FlexLookupBase.h"

struct FlexDiagSession;

//  Callback for completed data rx
typedef void (*FlexFunctionCallback)(
    FlexDiagSession* session,
    uint8_t* param_data,
    const size_t param_len
);

typedef struct {
    const FlexLookupBase base;                    //  Base lookup object
    const FlexFunctionCallback function_callback; //  Callback for function execution
} FlexFunctionLookupEntry;