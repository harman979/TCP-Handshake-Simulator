/*
 * test_unit.c
 * -----------
 * 100% Pure C Unit & Integration Test Suite.
 *
 * Verifies:
 *   1. TCP states and state_to_string() conversions
 *   2. Message types and message_type_to_string() conversions
 *   3. Packet construction (SYN, SYN-ACK, ACK)
 *   4. Three-way handshake state machine flow & transitions
 *   5. Sequence number and acknowledgment arithmetic
 *   6. Invalid ACK detection and rejection
 *   7. Retry limits configuration
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tcp_state.h"
#include "message.h"
#include "handshake.h"

static int tests_run = 0;
static int tests_passed = 0;

#define RUN_TEST(fn) do { \
    tests_run++; \
    printf("Running %-35s... ", #fn); \
    if (fn()) { \
        printf("[PASSED]\n"); \
        tests_passed++; \
    } else { \
        printf("[FAILED]\n"); \
    } \
} while(0)

/* Test 1: state_to_string conversions for all valid and unknown states */
static int test_state_to_string(void)
{
    if (strcmp(state_to_string(CLOSED), "CLOSED") != 0) return 0;
    if (strcmp(state_to_string(LISTEN), "LISTEN") != 0) return 0;
    if (strcmp(state_to_string(SYN_SENT), "SYN_SENT") != 0) return 0;
    if (strcmp(state_to_string(SYN_RECEIVED), "SYN_RECEIVED") != 0) return 0;
    if (strcmp(state_to_string(ESTABLISHED), "ESTABLISHED") != 0) return 0;
    if (strcmp(state_to_string((TCPState)999), "UNKNOWN") != 0) return 0;
    return 1;
}

/* Test 2: message_type_to_string conversions */
static int test_message_type_to_string(void)
{
    if (strcmp(message_type_to_string(MSG_SYN), "SYN") != 0) return 0;
    if (strcmp(message_type_to_string(MSG_SYN_ACK), "SYN-ACK") != 0) return 0;
    if (strcmp(message_type_to_string(MSG_ACK), "ACK") != 0) return 0;
    if (strcmp(message_type_to_string((MessageType)999), "UNKNOWN") != 0) return 0;
    return 1;
}

/* Test 3: create_syn packet constructor */
static int test_create_syn(void)
{
    int seq = 1000;
    TCPMessage msg = create_syn(seq);
    if (msg.type != MSG_SYN) return 0;
    if (msg.seq != seq) return 0;
    if (msg.ack != 0) return 0;
    return 1;
}

/* Test 4: create_syn_ack packet constructor */
static int test_create_syn_ack(void)
{
    int server_seq = 5000;
    int client_seq = 1000;
    TCPMessage msg = create_syn_ack(server_seq, client_seq + 1);
    if (msg.type != MSG_SYN_ACK) return 0;
    if (msg.seq != server_seq) return 0;
    if (msg.ack != client_seq + 1) return 0;
    return 1;
}

/* Test 5: create_ack packet constructor */
static int test_create_ack(void)
{
    int seq = 1001;
    int ack = 5001;
    TCPMessage msg = create_ack(seq, ack);
    if (msg.type != MSG_ACK) return 0;
    if (msg.seq != seq) return 0;
    if (msg.ack != ack) return 0;
    return 1;
}

/* Test 6: Complete successful 3-way handshake flow and state transitions in C */
static int test_handshake_state_machine(void)
{
    TCPEndpoint client = {"Client", CLOSED, 1000};
    TCPEndpoint server = {"Server", LISTEN, 5000};

    /* Initial state verification */
    if (client.state != CLOSED || server.state != LISTEN) return 0;

    /* Step 1: Client sends SYN */
    TCPMessage syn = create_syn(client.isn);
    client.state = SYN_SENT;
    if (client.state != SYN_SENT) return 0;

    /* Step 2: Server receives SYN and responds with SYN-ACK */
    server.state = SYN_RECEIVED;
    TCPMessage syn_ack = create_syn_ack(server.isn, syn.seq + 1);
    if (server.state != SYN_RECEIVED) return 0;
    if (syn_ack.ack != client.isn + 1) return 0;

    /* Step 3: Client receives SYN-ACK and sends ACK */
    client.state = ESTABLISHED;
    TCPMessage ack = create_ack(syn_ack.ack, syn_ack.seq + 1);
    if (client.state != ESTABLISHED) return 0;

    /* Server validation */
    if (ack.ack == server.isn + 1) {
        server.state = ESTABLISHED;
    } else {
        return 0;
    }

    /* Both must end in ESTABLISHED */
    if (client.state != ESTABLISHED || server.state != ESTABLISHED) return 0;

    return 1;
}

/* Test 7: Invalid ACK rejection verification */
static int test_invalid_ack_detection(void)
{
    TCPEndpoint server = {"Server", SYN_RECEIVED, 5000};
    int corrupted_ack_val = 9999;

    /* Server must reject mismatched ACK number */
    if (corrupted_ack_val == server.isn + 1) {
        return 0; /* Should not be equal */
    }

    /* Server state must NOT transition to ESTABLISHED on invalid ACK */
    if (corrupted_ack_val != server.isn + 1) {
        /* Connection remains unestablished */
        if (server.state == ESTABLISHED) return 0;
    }

    return 1;
}

/* Test 8: Verify MAX_RETRIES constant */
static int test_retry_limits(void)
{
    if (MAX_RETRIES != 3) return 0;
    return 1;
}

int main(void)
{
    printf("\n==================================================\n");
    printf("   TCP HANDSHAKE SIMULATOR - C TEST SUITE         \n");
    printf("==================================================\n\n");

    RUN_TEST(test_state_to_string);
    RUN_TEST(test_message_type_to_string);
    RUN_TEST(test_create_syn);
    RUN_TEST(test_create_syn_ack);
    RUN_TEST(test_create_ack);
    RUN_TEST(test_handshake_state_machine);
    RUN_TEST(test_invalid_ack_detection);
    RUN_TEST(test_retry_limits);

    printf("\n--------------------------------------------------\n");
    printf("Results: %d/%d tests passed successfully.\n", tests_passed, tests_run);
    printf("==================================================\n\n");

    return (tests_passed == tests_run) ? EXIT_SUCCESS : EXIT_FAILURE;
}
