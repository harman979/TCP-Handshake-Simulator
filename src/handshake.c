/*
 * handshake.c
 * -----------
 * Implementation of the four TCP handshake simulation scenarios.
 *
 * Scenarios:
 *   1. run_successful_handshake()   — normal, happy-path handshake
 *   2. run_invalid_ack_scenario()   — wrong acknowledgment number (Commit 4)
 *   3. run_packet_loss_scenario()   — a message is dropped (Commit 4)
 *   4. run_timeout_scenario()       — packet lost, retry up to MAX_RETRIES (Commit 4)
 */

#include "handshake.h"
#include "message.h"
#include "tcp_state.h"
#include <stdio.h>

/* Scenario 1: Normal three-way handshake. Both sides reach ESTABLISHED. */
void run_successful_handshake(void)
{
    printf("\n----------------------------------------\n");
    printf("   Scenario 1: Successful Handshake     \n");
    printf("----------------------------------------\n");

    /* Initialize endpoints */
    TCPEndpoint client = {"Client", CLOSED, 1000};
    TCPEndpoint server = {"Server", LISTEN, 5000};

    printf("\n[Initial State]\n");
    print_state(client.name, client.state);
    print_state(server.name, server.state);

    /* Step 1: Client sends SYN */
    printf("\n[Step 1] Client sends SYN to Server\n");
    TCPMessage syn = create_syn(client.isn);
    printf("  Message sent : ");
    print_message(&syn);
    client.state = SYN_SENT;
    print_state(client.name, client.state);

    /* Step 2: Server receives SYN and responds with SYN-ACK */
    printf("\n[Step 2] Server receives SYN and responds with SYN-ACK\n");
    server.state = SYN_RECEIVED;
    TCPMessage syn_ack = create_syn_ack(server.isn, syn.seq + 1);
    printf("  Message sent : ");
    print_message(&syn_ack);
    print_state(server.name, server.state);

    /* Step 3: Client receives SYN-ACK and sends ACK */
    printf("\n[Step 3] Client receives SYN-ACK and sends ACK to Server\n");
    client.state = ESTABLISHED;
    TCPMessage ack = create_ack(syn_ack.ack, syn_ack.seq + 1);
    printf("  Message sent : ");
    print_message(&ack);
    print_state(client.name, client.state);

    /* Server receives and validates ACK */
    printf("\n[Server Verification]\n");
    if (ack.ack == server.isn + 1) {
        printf("ACK validation successful.\n");
        server.state = ESTABLISHED;
    } else {
        printf("ERROR: Invalid acknowledgment number.\n");
        printf("Expected ACK : %d\n", server.isn + 1);
        printf("Received ACK : %d\n", ack.ack);
        printf("Handshake failed.\n");
        return;
    }

    /* Handshake completed successfully */
    printf("\n[Final State]\n");
    print_state(client.name, client.state);
    print_state(server.name, server.state);
    printf("Connection Established Successfully!\n");
}

/* TODO (Commit 4): Implement run_invalid_ack_scenario() */
void run_invalid_ack_scenario(void)
{
    printf("  [Commit 4] Invalid ACK scenario — not yet implemented.\n");
}

/* TODO (Commit 4): Implement run_packet_loss_scenario() */
void run_packet_loss_scenario(void)
{
    printf("  [Commit 4] Packet loss scenario — not yet implemented.\n");
}

/* TODO (Commit 4): Implement run_timeout_scenario() */
void run_timeout_scenario(void)
{
    printf("  [Commit 4] Timeout and retry scenario — not yet implemented.\n");
}
