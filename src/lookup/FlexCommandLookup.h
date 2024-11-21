#pragma once

#include <stdint.h>
#include <stddef.h>
#include "FlexLookupBase.h"

// Forward declaration of FlexDiagSession
typedef struct FlexDiagSession FlexDiagSession;

//  Callback for completed data rx
typedef void (*FlexDataCallback)(
    FlexDiagSession* session,
    uint8_t* data,
    const size_t len
);

//  Callback for frames by type
typedef void (*FlexPartialDataCallback)(
    FlexDiagSession* session,
    uint8_t frame_type,
    uint8_t* msg_data,
    const size_t msg_len,
    const size_t msg_idx
);

//  Command entry object
typedef struct {
    FlexLookupBase base;                        //  Base lookup object
    FlexDataCallback callback_rx;               //  Callback for completed data
    FlexDataCallback callback_partial_rx;       //  Callback for partial data, can be used to deny data based on initial request
    FlexPartialDataCallback callback_can_frame; //  Optional callback for partial data, useful for denying actions on first CAN frame
} FlexDiagCommand;