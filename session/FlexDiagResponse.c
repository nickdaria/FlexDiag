#include "FlexDiagResponse.h"

void fd_response_reset(FlexDiagResponse* response) {
    response->send_response = true;
    response->error_code = 0x11;
    response->len = 0;
}