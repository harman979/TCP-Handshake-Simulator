# Test Cases — TCP Three-Way Handshake Simulator

This document lists all manual test cases and their expected outputs.
Test cases will be verified at each commit phase.

---

## Test 1 — Normal Successful Handshake

**Scenario:** Menu option 1

**Expected behaviour:**
- Client starts in `CLOSED`, Server starts in `LISTEN`
- Client sends SYN with a valid ISN
- Server responds with SYN-ACK (ACK = client ISN + 1)
- Client sends ACK (ACK = server ISN + 1)
- Both client and server end in `ESTABLISHED`

**Expected final output:**
```
Client State : ESTABLISHED
Server State : ESTABLISHED
Connection Established Successfully!
```

---

## Test 2 — Invalid ACK Number

**Scenario:** Menu option 2

**Expected behaviour:**
- Handshake begins normally
- A deliberately incorrect ACK number is used
- Validation fails and an error is reported
- Neither side reaches `ESTABLISHED`

**Expected final output:**
```
ERROR: Invalid acknowledgment number.
Expected ACK : <correct value>
Received ACK : <wrong value>
Handshake failed.
```

---

## Test 3 — Packet Loss (SYN lost)

**Scenario:** Menu option 3, SYN dropped

**Expected behaviour:**
- Client sends SYN
- SYN is marked as lost
- Handshake cannot continue

**Expected final output:**
```
[PACKET LOST] SYN was not delivered.
Handshake cannot continue.
```

---

## Test 4 — Packet Loss (SYN-ACK lost)

**Scenario:** Menu option 3, SYN-ACK dropped

**Expected behaviour:**
- SYN delivered successfully
- SYN-ACK is marked as lost
- Handshake cannot continue

**Expected final output:**
```
[PACKET LOST] SYN-ACK was not delivered.
Handshake cannot continue.
```

---

## Test 5 — Timeout and Retry — Max Retries Exceeded

**Scenario:** Menu option 4

**Expected behaviour:**
- Packet is lost on every attempt
- Simulator retries up to MAX_RETRIES = 3 times
- After 3 failed attempts, handshake is aborted

**Expected final output:**
```
Attempt 1: Waiting for response... TIMEOUT
Retrying...
Attempt 2: Waiting for response... TIMEOUT
Retrying...
Attempt 3: Waiting for response... TIMEOUT
Handshake failed after 3 attempts.
```

---

## Test 6 — ACK Number Validation (Correct)

**Scenario:** Part of Test 1

**Expected behaviour:**
- Server validates client ACK == server ISN + 1
- Validation passes

**Expected output:**
```
ACK validation successful.
```

---

## Test 7 — Invalid Menu Input

**Scenario:** User enters a non-numeric or out-of-range value

**Expected behaviour:**
- Program does not crash
- Error message shown
- Menu is displayed again

**Expected output:**
```
Invalid input. Please enter a number (1-5).
```
