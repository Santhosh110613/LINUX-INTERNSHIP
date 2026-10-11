# LINUX-INTERNSHIP
Binder Driver Access Latency and Throughput Measurement
Project Overview
This project measures Binder driver access latency and throughput on an Android Emulator using C programming.

Objectives
Verify Binder device accessibility.
Retrieve the Binder protocol version.
Measure repeated Binder device open-and-close operations.
Calculate average operation latency and throughput.
Technologies Used
C Programming
Ubuntu Linux
Android Emulator
Android Debug Bridge (ADB)
Android Native Development Kit (NDK)
Test Programs
binder_test.c: Checks Binder device accessibility.
binder_version.c: Retrieves the Binder protocol version.
latency_test.c: Measures average device access latency.
throughput_test.c: Measures device access operations per second.
Note
The current tests measure Binder device access operations, not actual Binder IPC transaction latency or throughput.
