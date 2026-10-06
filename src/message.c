/*
 * message.c
 * ---------
 * Implementation of TCP message creation and display utilities.
 *
 * Phase 1: Stub — implementation will be added in Commit 2.
 */

#include "message.h"
#include <stdio.h>

/* TODO (Commit 2): Implement message_type_to_string() */
const char *message_type_to_string(MessageType type)
{
    (void)type;
    return "NOT_YET_IMPLEMENTED";
}

/* TODO (Commit 2): Implement create_syn() */
TCPMessage create_syn(int seq)
{
    TCPMessage msg = {MSG_SYN, seq, 0};
    return msg;
}

/* TODO (Commit 2): Implement create_syn_ack() */
TCPMessage create_syn_ack(int seq, int ack)
{
    TCPMessage msg = {MSG_SYN_ACK, seq, ack};
    return msg;
}

/* TODO (Commit 2): Implement create_ack() */
TCPMessage create_ack(int seq, int ack)
{
    TCPMessage msg = {MSG_ACK, seq, ack};
    return msg;
}

/* TODO (Commit 2): Implement print_message() */
void print_message(const TCPMessage *msg)
{
    (void)msg;
}
