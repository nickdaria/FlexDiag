# FlexDiag
FlexDiag is a modular C library for implementing automotive-style diagnostic/control sessions without dynamic memory allocation across a variety of communication protocols. It provides the framework for developers to implement variable lookup tables, function calls, security level authorization, and communication encoding **once**, and then simply set up as many concurrent diagnostic sessions as they want across multiple communication protocols.

## Core Goals
- Allow multiple concurrent sessions fully independent of one another
- Per-session user-managed security level that can be used to only permit certain actions when a minimum security level is met. Security level can also be left at 0 to always allow.
- Variable lookup tables for developers to easily map internal variables of any size by ID/name with bidirectional read & write
- Function tables for developers to map functions by ID/name so they can be called (with parameters)
- Provide default responses for not found & security access denied
- Integrate seamlessly with FlexISOTP library for CAN+UDS sessions
- Provide basic default implementations of UDS, HTTP, BLE, and Serial

## Expectations
- This library is not designed for extra high-bandwidth use. While BLE, HTTP, and Serial will certainly have more throughput, this is basically intended to be an enumerable version of UDS that works on more than just CAN.

## Example Use Case
- Supporting standard UDS diagnostics as well as more modern BLE/Wi-fi connections.
- A module that supports a tester diagnostic session as well as a private diagnostic session with the infotainment system for configuration changes
- Sharing common calls between BLE and Wi-fi for simplicity, with extended high-throughput features available only over Wi-fi.
- Device that uses the same communiation format when connected via Serial & BLE

# Structure
<img src="resources/flexdiag_structure.png" width="650rem"/>