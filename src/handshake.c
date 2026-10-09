/*
 * handshake.c
 * -----------
 * Implementation of the four TCP handshake simulation scenarios.
 *
 * Scenarios:
 *   1. run_successful_handshake()   — normal, happy-path handshake
 *   2. run_invalid_ack_scenario()   — wrong acknowledgment number
 *   3. run_packet_loss_scenario()   — a message is dropped
 *   4. run_timeout_scenario()       — packet lost, retry up to MAX_RETRIES
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

/* Scenario 2: Sends an incorrect ACK number. Handshake fails. */
void run_invalid_ack_scenario(void)
{
    printf("\n----------------------------------------\n");
    printf("   Scenario 2: Invalid ACK Simulation   \n");
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

    /* Step 3: Client receives SYN-ACK and sends ACK with invalid ACK number */
    printf("\n[Step 3] Client receives SYN-ACK and sends ACK to Server\n");
    int invalid_ack = 9999;
    TCPMessage ack = create_ack(syn_ack.ack, invalid_ack);
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
}

/* Scenario 3: A packet is lost mid-handshake. Handshake cannot complete. */
void run_packet_loss_scenario(void)
{
    printf("\n----------------------------------------\n");
    printf("   Scenario 3: Packet Loss Simulation   \n");
    printf("----------------------------------------\n");
    printf("  Select packet to drop:\n");
    printf("  1. Drop SYN packet\n");
    printf("  2. Drop SYN-ACK packet\n");
    printf("  Enter choice: ");

    int sub_choice = 0;
    int res = scanf("%d", &sub_choice);
    if (res != 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        printf("  Invalid input. Please enter 1 or 2.\n");
        return;
    }

    if (sub_choice != 1 && sub_choice != 2) {
        printf("  Invalid choice. Please enter 1 or 2.\n");
        return;
    }

    /* Initialize endpoints */
    TCPEndpoint client = {"Client", CLOSED, 1000};
    TCPEndpoint server = {"Server", LISTEN, 5000};

    printf("\n[Initial State]\n");
    print_state(client.name, client.state);
    print_state(server.name, server.state);

    if (sub_choice == 1) {
        /* Step 1: Client sends SYN */
        printf("\n[Step 1] Client sends SYN to Server\n");
        TCPMessage syn = create_syn(client.isn);
        printf("  Message sent : ");
        print_message(&syn);
        client.state = SYN_SENT;
        print_state(client.name, client.state);

        /* Packet is lost in transit */
        printf("\n[PACKET LOST] SYN was not delivered.\n");
        printf("Handshake cannot continue.\n");
    } else {
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

        /* Packet is lost in transit */
        printf("\n[PACKET LOST] SYN-ACK was not delivered.\n");
        printf("Handshake cannot continue.\n");
    }
}

/* Scenario 4: Packet lost; sender retries up to MAX_RETRIES times. */
void run_timeout_scenario(void)
{
    printf("\n----------------------------------------\n");
    printf(" Scenario 4: Timeout & Retry Simulation \n");
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

    printf("\n");
    for (int attempt = 1; attempt <= MAX_RETRIES; attempt++) {
        printf("Attempt %d: Waiting for response... TIMEOUT\n", attempt);
        if (attempt < MAX_RETRIES) {
            printf("Retrying...\n");
        }
    }
    printf("Handshake failed after %d attempts.\n", MAX_RETRIES);
}
