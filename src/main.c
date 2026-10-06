/*
 * main.c
 * ------
 * Entry point for the TCP Three-Way Handshake Simulator.
 *
 * Responsibilities:
 *   - Display the main menu
 *   - Read and validate user input
 *   - Dispatch to the appropriate scenario function
 *
 * Phase 1: Stub — menu prints but all scenario calls go to stubs.
 * Full menu logic will be finalized in Commit 3.
 */

#include <stdio.h>
#include <stdlib.h>
#include "handshake.h"

/* ── Print the main menu ────────────────────────────────────────────────────── */
static void print_menu(void)
{
    printf("\n");
    printf("========================================\n");
    printf("       TCP HANDSHAKE SIMULATOR          \n");
    printf("========================================\n");
    printf("  1. Successful Handshake               \n");
    printf("  2. Invalid ACK Simulation             \n");
    printf("  3. Packet Loss Simulation             \n");
    printf("  4. Timeout and Retry Simulation       \n");
    printf("  5. Exit                               \n");
    printf("========================================\n");
    printf("  Enter choice: ");
}

/* ── Entry point ────────────────────────────────────────────────────────────── */
int main(void)
{
    int choice = 0;

    printf("\n  TCP Three-Way Handshake Simulator\n");
    printf("  Phase 1 — Project Skeleton (stub)\n");

    while (1) {
        print_menu();

        /* TODO (Commit 3): Add robust input handling */
        if (scanf("%d", &choice) != 1) {
            /* Clear bad input */
            while (getchar() != '\n');
            printf("  Invalid input. Please enter a number (1-5).\n");
            continue;
        }

        switch (choice) {
            case 1: run_successful_handshake();  break;
            case 2: run_invalid_ack_scenario();  break;
            case 3: run_packet_loss_scenario();  break;
            case 4: run_timeout_scenario();      break;
            case 5:
                printf("\n  Exiting simulator. Goodbye!\n\n");
                return EXIT_SUCCESS;
            default:
                printf("  Invalid choice. Please enter 1-5.\n");
        }
    }

    return EXIT_SUCCESS;
}
