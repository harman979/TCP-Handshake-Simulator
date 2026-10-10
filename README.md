# TCP Three-Way Handshake Simulator

A modular, educational command-line simulator written in **100% Pure C (C11)** that demonstrates how the **TCP Three-Way Handshake** establishes a connection, how sequence and acknowledgment numbers work, how endpoints transition between TCP states, and what happens during network failures.

---

## Problem Statement

The Transmission Control Protocol (TCP) is the backbone of reliable communication on the internet. Before any data is exchanged between two hosts, TCP must first establish a connection through a process called the **three-way handshake**. Understanding this process is fundamental to networking, operating systems, and systems programming.

Most students learn about the TCP handshake from static textbook diagrams, but rarely see it working step-by-step in code. This project bridges that gap by providing a clean, command-line **simulator in C** that demonstrates exactly how a TCP connection is established — including what happens when things go wrong.

---

## Objectives

This simulator demonstrates:

- The three messages involved in TCP connection establishment: **SYN**, **SYN-ACK**, and **ACK**
- How **sequence numbers** and **acknowledgment numbers** are generated, incremented, and validated
- The **TCP state machine** — how client and server move through their respective states
- Realistic **failure scenarios**: invalid acknowledgment numbers, dropped packets, and retry timeouts

> *Note: This is an educational simulator designed for conceptual clarity, not a real OS kernel TCP/IP stack.*

---

## How the TCP Handshake Works

### Handshake Flow Diagram

```text
       CLIENT (Active Opener)                       SERVER (Passive Opener)
               |                                              |
        State: CLOSED                                  State: LISTEN
               |                                              |
               | -------- [1] SYN (Seq = 1000) -------------> |
        State: SYN_SENT                                       |
               |                                       State: SYN_RECEIVED
               |                                              |
               | <--- [2] SYN-ACK (Seq = 5000, Ack = 1001) -- |
               |                                              |
        State: ESTABLISHED                                    |
               |                                              |
               | -------- [3] ACK (Seq = 1001, Ack = 5001) -> |
               |                                              |
               |                                       State: ESTABLISHED
               |                                              |
       Connection Open!                                Connection Open!
```

### Sequence & Acknowledgment Rules

1. **Step 1 — Client sends SYN:**
   - The Client picks an Initial Sequence Number (`ISN = 1000`).
   - Packet sent: `[SYN] Seq = 1000`.
   - Client state moves: `CLOSED` -> `SYN_SENT`.

2. **Step 2 — Server sends SYN-ACK:**
   - The Server receives the SYN, picks its own Sequence Number (`ISN = 5000`), and acknowledges the Client's SYN by calculating `Ack = Client ISN + 1 = 1001`.
   - Packet sent: `[SYN-ACK] Seq = 5000, Ack = 1001`.
   - Server state moves: `LISTEN` -> `SYN_RECEIVED`.

3. **Step 3 — Client sends ACK:**
   - The Client validates the SYN-ACK, moves to `ESTABLISHED`, and acknowledges the Server by calculating `Ack = Server ISN + 1 = 5001`.
   - Packet sent: `[ACK] Seq = 1001, Ack = 5001`.
   - The Server validates that the incoming ACK matches `Server ISN + 1`, and moves to `ESTABLISHED`.

---

### State Transitions Summary

- **Client:** `CLOSED` -> `SYN_SENT` -> `ESTABLISHED`
- **Server:** `LISTEN` -> `SYN_RECEIVED` -> `ESTABLISHED`

---

## Simulation Scenarios

The simulator features an interactive menu with 4 scenarios:

1. **Successful Handshake:**
   The standard 3-way handshake. All packets are delivered and both client and server reach `ESTABLISHED`.

2. **Invalid ACK Simulation:**
   The client deliberately returns an incorrect acknowledgment number (`9999` instead of `5001`). The server detects the mismatch and rejects the connection.

3. **Packet Loss Simulation:**
   Allows testing what happens when a packet is dropped in transit:
   - Drop SYN packet (handshake stops at step 1)
   - Drop SYN-ACK packet (handshake stops at step 2)

4. **Timeout & Retransmission Simulation:**
   Simulates network timeout when no reply is received. The sender retransmits up to `MAX_RETRIES` (3 times) before terminating the attempt.

---

## Project Structure

```text
TCP-Handshake-Simulator/
├── src/
│   ├── tcp_state.h       # TCPState enum and state printing prototypes
│   ├── tcp_state.c       # State-to-string conversion and formatting
│   ├── message.h         # TCPMessage struct and message constructors
│   ├── message.c         # SYN, SYN-ACK, and ACK packet creation
│   ├── handshake.h       # TCPEndpoint struct and scenario declarations
│   ├── handshake.c       # Implementation of all 4 handshake scenarios
│   └── main.c            # Interactive CLI menu and user input handler
├── tests/
│   ├── test_cases.md     # Test case specifications and expected outputs
│   └── test_unit.c       # Pure C unit and state transition test suite
├── Makefile              # Cross-platform build script
├── LICENSE               # MIT License
└── README.md             # Project documentation
```

---

## Prerequisites

To compile and run this project, all you need is a C compiler:

- **GCC Compiler** with C11 support (`gcc --version`)
- *(Optional)* **Make** (`make` on Linux/Mac or `mingw32-make` on Windows)

No external libraries, Python, or packages are needed.

---

## How to Build and Run

### Option 1: Using GCC directly (Recommended & Simplest)

In your terminal (Command Prompt, PowerShell, or Linux/macOS bash):

```bash
gcc -Wall -Wextra -std=c11 -Isrc src/main.c src/handshake.c src/message.c src/tcp_state.c -o tcp_sim
```

Then run the compiled executable:

- On Windows:
  ```powershell
  .\tcp_sim.exe
  ```
- On Linux / macOS / WSL:
  ```bash
  ./tcp_sim
  ```

---

### Option 2: Using Make

- **On Windows (PowerShell / CMD):**
  ```powershell
  mingw32-make        # Compile the simulator
  mingw32-make run    # Run the simulator
  mingw32-make clean  # Remove compiled files
  ```

- **On Linux / WSL / macOS:**
  ```bash
  make                # Compile the simulator
  make run            # Run the simulator
  make clean          # Remove compiled files
  ```

---

## Running the C Test Suite

A standalone test runner written in pure C is provided in `tests/test_unit.c` to automatically verify state transitions, packet constructors, sequence arithmetic, and retry limits.

### Run with GCC directly:

```bash
gcc -Wall -Wextra -std=c11 -Isrc src/tcp_state.c src/message.c tests/test_unit.c -o test_unit
```

- On Windows:
  ```powershell
  .\test_unit.exe
  ```
- On Linux / macOS / WSL:
  ```bash
  ./test_unit
  ```

### Or run using Make:

```bash
mingw32-make test   # Windows
make test           # Linux / macOS
```

Expected output:
```text
==================================================
   TCP HANDSHAKE SIMULATOR - C TEST SUITE         
==================================================

Running test_state_to_string               ... [PASSED]
Running test_message_type_to_string        ... [PASSED]
Running test_create_syn                    ... [PASSED]
Running test_create_syn_ack                ... [PASSED]
Running test_create_ack                    ... [PASSED]
Running test_handshake_state_machine       ... [PASSED]
Running test_invalid_ack_detection         ... [PASSED]
Running test_retry_limits                  ... [PASSED]

--------------------------------------------------
Results: 8/8 tests passed successfully.
==================================================
```

---

## Test Cases Reference

For the full list of manual scenarios and expected outputs, refer to `tests/test_cases.md`.

---

## License

This project is licensed under the MIT License. See `LICENSE` for details.
