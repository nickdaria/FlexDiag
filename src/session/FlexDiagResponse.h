#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    uint8_t error_code;     // 0 indicates success; non-zero is an error code
    uint8_t* data;          // Pointer to the response data buffer
    size_t len;             // Length of the response data
} FlexDiagResponse;

/**
 * @brief 
 * 
 * @param response Pointer to struct to initialize
 * @param data_buffer Pointer to structs data buffer
 * @param max_len Length of data buffer
 */
void fd_init_response(FlexDiagResponse* response, uint8_t* data_buffer, const uint8_t len);


/**
 * @brief 
 * 
 * @param response Pointer to struct to initialize
 * @param len Length of the response data buffer
 * @return Initialization and allocation success
 */
bool fd_init_response_alloc(FlexDiagResponse* response, const size_t len);