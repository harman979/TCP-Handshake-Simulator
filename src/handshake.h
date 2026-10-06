/*
 * handshake.h
 * -----------
 * Declares the TCPEndpoint struct and the four scenario functions
 * that drive the TCP three-way handshake simulation.
 *
 * Scenarios:
 *   1. run_successful_handshake()   — normal, happy-path handshake
 *   2. run_invalid_ack_scenario()   — wrong acknowledgment number
 *   3. run_packet_loss_scenario()   — a message is dropped
 *   4. run_timeout_scenario()       — packet lost, retry up to MAX_RETRIES
 */

#ifndef HANDSHAKE_H
#define HANDSHAKE_H

#include "tcp_state.h"

/* Maximum number of retransmission retries before giving up. */
#define MAX_RETRIES 3

/* ── Endpoint struct ────────────────────────────────────────────────────────── */
/*
 * Represents one side of the TCP connection (client or server).
 * Holds the endpoint's name, current state, and its ISN.
 */
typedef struct {
    const char *name;   /* "Client" or "Server"          */
    TCPState    state;  /* Current TCP state              */
    int         isn;    /* Initial Sequence Number        */
} TCPEndpoint;

/* ── Scenario function declarations ────────────────────────────────────────── */

/* Scenario 1: Normal three-way handshake. Both sides reach ESTABLISHED. */
void run_successful_handshake(void);

/* Scenario 2: Sends an incorrect ACK number. Handshake fails. */
void run_invalid_ack_scenario(void);

/* Scenario 3: A packet is lost mid-handshake. Handshake cannot complete. */
void run_packet_loss_scenario(void);

/* Scenario 4: Packet lost; sender retries up to MAX_RETRIES times. */
void run_timeout_scenario(void);

#endif /* HANDSHAKE_H */
