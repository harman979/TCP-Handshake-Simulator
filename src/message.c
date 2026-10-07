/*
 * message.c
 * ---------
 * Implementation of TCP message creation and display utilities.
 */

#include "message.h"
#include <stdio.h>

const char *message_type_to_string(MessageType type)
{
    switch (type) {
        case MSG_SYN:     return "SYN";
        case MSG_SYN_ACK: return "SYN-ACK";
        case MSG_ACK:     return "ACK";
        default:          return "UNKNOWN";
    }
}

TCPMessage create_syn(int seq)
{
    TCPMessage msg = {MSG_SYN, seq, 0};
    return msg;
}

TCPMessage create_syn_ack(int seq, int ack)
{
    TCPMessage msg = {MSG_SYN_ACK, seq, ack};
    return msg;
}

TCPMessage create_ack(int seq, int ack)
{
    TCPMessage msg = {MSG_ACK, seq, ack};
    return msg;
}

void print_message(const TCPMessage *msg)
{
    if (msg == NULL) {
        return;
    }
    if (msg->type == MSG_SYN) {
        printf("[%s] Seq=%d\n", message_type_to_string(msg->type), msg->seq);
    } else {
        printf("[%s] Seq=%d, Ack=%d\n", message_type_to_string(msg->type), msg->seq, msg->ack);
    }
}

