#pragma once

#include <stdint.h>
#include <stddef.h>
#include "FlexDiagResponse.h"
#include "../lookup/FlexLookupBase.h"
#include "../lookup/FlexCommandLookup.h"

typedef struct {
    uint8_t active_security_level;      //  User-controlled security level: 0 default, 0xFF highest
    FlexDiagCommand* command_table;     //  Table of command lookup objects
    size_t command_table_len;           //  Length of the command table
    FlexDiagResponse response;          //  Response object
} FlexDiagSession;

/**
 * @brief Process a full message by service ID (first byte)
 * 
 * @param session Pointer to session object
 * @param service_id Service ID of the message (initial byte)
 * @param data Pointer to recieved data excluding service id
 * @param len Length of recieved data excluding service id
 * @return true Response was requested
 * @return false No response was requested
 */
bool fd_session_process_by_id(FlexDiagSession* session, const uint8_t service_id, const uint8_t* data, const size_t len);

/**
 * @brief Process a full message by service name.
 * 
 * @param session Pointer to session object
 * @param name Exact name of the service (case-insensitive)
 * @param data Pointer to recieved data excluding service id
 * @param len Length of recieved data excluding service id
 * @return true Response was requested
 * @return false No response was requested
 */
bool fd_session_process_by_name(FlexDiagSession* session, const char* name, const uint8_t* data, const size_t len);

/**
 * @brief Process a partial message fragment by service name. Partial messages are technically optional, but you will have to recieve entire CAN ISO-TP messages before responding with a denial condition.
 * 
 * @param session Pointer to session object
 * @param service_id Service ID of the message (initial byte)
 * @param data Pointer to recieved data
 * @param len Length of recieved data
 * @return true Response was requested
 * @return false No response was requested
 */
bool fd_session_process_partial_by_id(FlexDiagSession* session, const uint8_t service_id, const uint8_t* data, const size_t len);

/**
 * @brief Process a partial message fragment by service name Partial messages are technically optional, but you will have to recieve entire CAN ISO-TP messages before responding with a denial condition.
 * 
 * @param session Pointer to session object
 * @param name Exact name of the service (case-insensitive)
 * @param data Pointer to recieved data
 * @param len Length of recieved data
 * @return true Response was requested
 * @return false No response was requested
 */
bool fd_session_process_partial_by_name(FlexDiagSession* session, const char* name, const uint8_t* data, const size_t len);

/**
 * @brief Initialize the FlexDiagSession object with a specified response buffer.
 * 
 * @param session Pointer to session object to initialize
 * @param response_buf Pointer to response buffer
 * @param response_buf_len Size of response buffer
 */
void fd_init_session(FlexDiagSession* session, FlexDiagCommand* command_table, const size_t command_table_len, uint8_t* response_buf, const size_t response_buf_len);

/**
 * @brief Initialize the FlexDiagSession object and allocate a response buffer
 * 
 * @param session Pointer to session object to initialize
 * @param response_buf_len Size of response buffer to allocate
 * @return true Successfully allocated resources and initialized session
 * @return false Failed to allocate resources
 */
bool fd_init_session_alloc(FlexDiagSession* session, FlexDiagCommand* command_table, const size_t command_table_len, const size_t response_buf_len);

/**
 * @brief Deinitialize the FlexDiagSession object and free allocated resources
 * 
 * @param session Pointer to session object to deinitialize
 */
void fd_deinit_session(FlexDiagSession* session);