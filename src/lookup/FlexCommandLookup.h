#pragma once

#include <stdint.h>
#include <stddef.h>
#include "FlexLookupBase.h"

struct FlexDiagSession;

//  Callback for completed data rx
typedef void (*FlexDataCallback)(
    struct FlexDiagSession* session,
    uint8_t* data,
    const size_t len
);

//  Callback for frames by type
typedef void (*FlexPartialDataCallback)(
    struct FlexDiagSession* session,
    const size_t msg_idx,
    uint8_t* msg_data,
    const size_t msg_len
);

//  Command entry object
typedef struct {
    const FlexLookupBase base;                        //  Base lookup object
    const FlexDataCallback callback_rx;               //  Callback for completed data
    const FlexDataCallback callback_partial_rx;       //  Optional callback for partial data, can be used to deny data based on initial request
} FlexDiagCommand;