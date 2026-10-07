/*
 * tcp_state.c
 * -----------
 * Implementation of TCP state utilities.
 * Provides state-to-string conversion and state display helpers.
 */

#include "tcp_state.h"
#include <stdio.h>

const char *state_to_string(TCPState state)
{
    switch (state) {
        case CLOSED:       return "CLOSED";
        case LISTEN:       return "LISTEN";
        case SYN_SENT:     return "SYN_SENT";
        case SYN_RECEIVED: return "SYN_RECEIVED";
        case ESTABLISHED:  return "ESTABLISHED";
        default:           return "UNKNOWN";
    }
}

void print_state(const char *endpoint_name, TCPState state)
{
    if (endpoint_name == NULL) {
        endpoint_name = "Endpoint";
    }
    printf("%s State : %s\n", endpoint_name, state_to_string(state));
}

