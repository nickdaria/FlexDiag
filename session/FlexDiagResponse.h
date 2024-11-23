#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    bool send_response;     //  Flag to send a response
    uint8_t service_id;     //  Service ID of the response
    uint8_t error_code;     //  0 indicates success; non-zero is an error code & cancels active Rx action
    uint8_t* data;          //  Pointer to the response data buffer
    size_t len_max;         //  Length of the response data buffer
    size_t len;             //  Desired length of the response data
} FlexDiagResponse;

/**
 * @brief Reset response object for a new transaction
 * 
 * @param response Pointer to response object
 */
void fd_response_reset(FlexDiagResponse* response);