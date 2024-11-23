#include "FlexDiagSession.h"
#include <stdlib.h>

/*
    Helpers
*/
FlexDiagCommand* fd_lookup_command_by_id(FlexDiagSession* session, const uint8_t service_id) {
    for (size_t i = 0; i < session->command_table_len; i++) {
        if (session->command_table[i].base.id == service_id) {
            return &session->command_table[i];
        }
    }

    return NULL;
}

/*
    Process Data
*/
bool fd_session_process_by_id(FlexDiagSession* session, const uint8_t service_id, const uint8_t* data, const size_t len) {
    //  Reset response
    fd_response_reset(&session->response);
    session->response.service_id = service_id;

    //  Lookup command
    FlexDiagCommand* command = fd_lookup_command_by_id(session, service_id);
    if (command == NULL) {
        //  Return not found
        return true;
    }

    //  Process command
    if (command->callback_rx != NULL) {
        command->callback_rx(session, data, len);
    }

    return session->response.send_response;
}


bool fd_session_process_by_name(FlexDiagSession* session, const char* name, const uint8_t* data, const size_t len);


/*
    Process Partial
*/
bool fd_session_process_partial_by_id(FlexDiagSession* session, const uint8_t service_id, const uint8_t* data, const size_t len);


bool fd_session_process_partial_by_name(FlexDiagSession* session, const char* name, const uint8_t* data, const size_t len);

/*
    Init
*/
void fd_init_session(FlexDiagSession* session, FlexDiagCommand* command_table, const size_t command_table_len, uint8_t* response_buf, const size_t response_buf_len) {
    //  Default security level
    session->active_security_level = 1;

    //  Set command table
    session->command_table = command_table;
    session->command_table_len = command_table_len;

    //  Set response buffer
    session->response.data = response_buf;
    session->response.len_max = response_buf_len;
    session->response.len = 0;

    //  Reset response
    fd_response_reset(&session->response);
}


bool fd_init_session_alloc(FlexDiagSession* session, FlexDiagCommand* command_table, const size_t command_table_len, const size_t response_buf_len) {
    //  Allocate response buffer
    uint8_t* response_buf = (uint8_t*)malloc(response_buf_len);
    if (response_buf == NULL) {
        return false;
    }

    //  Initialize session
    fd_init_session(session, command_table, command_table_len, response_buf, response_buf_len);
    return true;
}