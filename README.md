# TCP Three-Way Handshake Simulator

---

## Problem Statement

The Transmission Control Protocol (TCP) is the backbone of reliable communication on the internet. Before any data is exchanged between two hosts, TCP must first **establish a connection** through a process called the **three-way handshake**. Understanding this process is fundamental to networking, operating systems, and systems programming.

Most students learn about the TCP handshake from diagrams and textbooks, but never see it working step-by-step in code. This project bridges that gap by building a small, clear, command-line **simulator in C** that demonstrates exactly how a TCP connection is established — including what happens when things go wrong.

---

## Objective

This simulator is intended to teach:

- The three messages involved in TCP connection establishment: **SYN**, **SYN-ACK**, **ACK**
- How **sequence numbers** and **acknowledgment numbers** work and why they change
- The **TCP state machine** — how both client and server move through states
- What happens during **failure scenarios**: invalid acknowledgment, packet loss, timeout, and retry

This is a **learning-focused simulation**, not a real TCP/IP stack implementation.

---

