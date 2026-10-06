/*
 * message.h
 * ---------
 * Declares the TCPMessage struct and MessageType enum used to
 * represent the three messages in the TCP three-way handshake:
 *   SYN, SYN-ACK, ACK
 *
 * Only the fields relevant to connection establishment are modelled.
 * This is NOT a full TCP header implementation.
 */

#ifndef MESSAGE_H
#define MESSAGE_H

/* ── Message types ─────────────────────────────────────────────────────────── */
typedef enum {
    MSG_SYN,
    MSG_SYN_ACK,
    MSG_ACK
} MessageType;

/* ── Simulated TCP message ─────────────────────────────────────────────────── */
typedef struct {
    MessageType type;   /* SYN, SYN-ACK, or ACK                   */
    int seq;            /* Sequence number                         */
    int ack;            /* Acknowledgment number (0 if not used)   */
} TCPMessage;

/* ── Function declarations ─────────────────────────────────────────────────── */

/* Returns the string name of a message type (e.g. "SYN-ACK"). */
const char *message_type_to_string(MessageType type);

/* Creates a SYN message with the given sequence number. */
TCPMessage create_syn(int seq);

/* Creates a SYN-ACK message. */
TCPMessage create_syn_ack(int seq, int ack);

/* Creates an ACK message. */
TCPMessage create_ack(int seq, int ack);

/* Prints a formatted representation of a TCPMessage. */
void print_message(const TCPMessage *msg);

#endif /* MESSAGE_H */
