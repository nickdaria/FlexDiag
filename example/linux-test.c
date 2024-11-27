#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "../FlexDiag.h"

FlexDiagSession session;

void cmd_echo(FlexDiagSession* session, const uint8_t* data, const size_t len) {
    for(size_t i = 0; i < len; i++) {
        session->response.data[i] = data[i];
        session->response.len++;
    }

    //  Mark okay
    session->response.error_code = 0;
}

void cmd_backwards(FlexDiagSession* session, const uint8_t* data, const size_t len) {
    for (size_t i = len; i > 0; i--) {
        session->response.data[session->response.len] = data[i - 1];
        session->response.len++;
    }

    //  Mark okay
    session->response.error_code = 0;
}

FlexDiagCommand commandTable[] = {
    {
        .base = {
            .name = "echo",
            .id = 0x01,
            .security_level = 0x01
        },
        .callback_rx = cmd_echo,
        .callback_partial_rx = NULL
    },
    {
        .base = {
            .name = "backwards",
            .id = 0x02,
            .security_level = 0x01
        },
        .callback_rx = cmd_backwards,
        .callback_partial_rx = NULL
    }
};
const size_t commandTableSize = sizeof(commandTable) / sizeof(FlexDiagCommand);

void printHexArr(const uint8_t* data, const size_t len) {
    for(size_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

void processMessage(const uint8_t* data, const size_t len) {
    //  Print message
    printf("\tMessage: ");
    printHexArr(data, len);

    //  Process message
    if(fd_session_process_by_id(&session, data[0], data + 1, len - 1)) {
        printf("\tResponse? %b, Serv ID: %02X, Err Code: %02X\n", session.response.send_response, session.response.service_id, session.response.error_code);
        printf("\tData: ");
        printHexArr(session.response.data, session.response.len);
    } else {
        printf("\tNo response requested\n");
    }
}

size_t getUserInputHex(uint8_t* buf, const size_t len) {
    char input[len*2];
    printf("Enter hex data (up to %zu bytes): ", len);

    if (!fgets(input, sizeof(input), stdin)) {
        return 0;
    }

    size_t inputLen = strcspn(input, "\n");
    input[inputLen] = '\0';

    // Validate that the input length is even and within bounds
    if (inputLen % 2 != 0 || inputLen / 2 > len) {
        return 0;
    }

    size_t byteCount = 0;
    for (size_t i = 0; i < inputLen; i += 2) {
        if (!isxdigit(input[i]) || !isxdigit(input[i + 1])) {
            return 0;
        }

        // Convert two hex characters to a byte
        unsigned int byte;
        sscanf(&input[i], "%2x", &byte);
        buf[byteCount++] = (uint8_t)byte;
    }

    return byteCount;
}

int main() {
    printf("FlexDiag v%d.%d.%d Test\n", FLEXDIAG_VERSION_MAJOR, FLEXDIAG_VERSION_MINOR, FLEXDIAG_VERSION_PATCH);

    //  Initialize session
    fd_init_session_alloc(&session, commandTable, commandTableSize, 256);

    //  Loop
    while(true) {
        const size_t buf_len = 256;
        uint8_t buf[buf_len];

        //  Get user input
        size_t input_len = getUserInputHex(buf, buf_len);
        if(input_len == 0) {
            break;
        }

        //  Process message
        processMessage(buf, input_len);
    }

    //  Dealloc
    fd_deinit_session(&session);

    return 0;
}