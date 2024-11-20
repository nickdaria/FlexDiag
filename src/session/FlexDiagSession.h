#pragma once

#include <stdint.h>
#include <stddef.h>
#include "FlexDiagResponse.h"
#include "../lookup/FlexLookupBase.h"
#include "../lookup/FlexCommandLookup.h"

typedef struct {
    uint8_t security_level;             //  User-controlled security level: 0 default, 0xFF highest
    FlexDiagCommand* command_table;   //  Table of command lookup objects
    size_t command_table_len;           //  Length of the command table
    FlexDiagResponse response;          //  Response object
} FlexDiagSession;

/**
 * @brief Initialize the FlexDiagSession object with a specified response buffer.
 * 
 * @param session Pointer to session object to initialize
 * @param response_buf Pointer to response buffer
 * @param response_buf_len Size of response buffer
 */
void fd_init_session(FlexDiagSession* session, uint8_t* response_buf, const size_t response_buf_len);

/**
 * @brief Initialize the FlexDiagSession object and allocate a response buffer
 * 
 * @param session Pointer to session object to initialize
 * @param response_buf_len Size of response buffer to allocate
 * @return true Successfully allocated resources and initialized session
 * @return false Failed to allocate resources
 */
bool fd_init_session_alloc(FlexDiagSession* session, const size_t response_buf_len);