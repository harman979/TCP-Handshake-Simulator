/*
 * tcp_state.h
 * -----------
 * Declares the TCPState enum representing all connection states
 * used in the TCP three-way handshake simulation.
 *
 * States modelled:
 *   CLOSED       — no connection active
 *   LISTEN       — server waiting for incoming SYN
 *   SYN_SENT     — client has sent SYN, awaiting SYN-ACK
 *   SYN_RECEIVED — server received SYN, sent SYN-ACK, awaiting ACK
 *   ESTABLISHED  — handshake complete, connection open
 */

#ifndef TCP_STATE_H
#define TCP_STATE_H

/* ── TCP connection states ─────────────────────────────────────────────────── */
typedef enum {
    CLOSED,
    LISTEN,
    SYN_SENT,
    SYN_RECEIVED,
    ESTABLISHED
} TCPState;

/* ── Function declarations ─────────────────────────────────────────────────── */

/* Returns a human-readable string for a given TCPState. */
const char *state_to_string(TCPState state);

/* Prints the current state of a named endpoint (e.g. "Client" or "Server"). */
void print_state(const char *endpoint_name, TCPState state);

#endif /* TCP_STATE_H */
