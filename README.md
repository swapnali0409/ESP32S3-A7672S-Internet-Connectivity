# ESP32-S3 + SIMCom A7672S LTE Internet Connectivity

## 📌 Project Overview

This project demonstrates how to connect an **ESP32-S3 development board** to the Internet using a **SIMCom A7672S LTE modem**.

The main objective of this project was to understand how the A7672S modem can establish a cellular data connection and how that connection can be exposed to a Windows computer through the modem's **USB/Remote NDIS network interface**.

Instead of using the computer's Wi-Fi connection, the goal was to verify that Internet traffic could be routed through the **SIM card → A7672S LTE modem → USB/NDIS → Windows** path.

The project involved:

- Communicating with the A7672S using AT commands
- Checking the modem model and firmware
- Verifying SIM card status
- Checking cellular network registration
- Checking packet attachment
- Checking active PDP contexts
- Checking the assigned cellular IP address
- Checking the configured APN
- Checking DNS configuration
- Configuring the modem's USB networking mode
- Changing the modem dial mode
- Connecting the modem to Windows through USB
- Identifying the Remote NDIS network adapter
- Checking Windows IP configuration
- Checking Windows routing
- Testing connectivity to the local gateway
- Testing Internet connectivity using `8.8.8.8`
- Testing DNS resolution using `google.com`
- Using `tracert` to verify the Internet path

The final tests successfully demonstrated Internet connectivity from Windows through the network interface associated with the A7672S setup.

---

# 🎯 Project Objective

The primary objective was to establish a working cellular Internet connection using:

**ESP32-S3 + SIMCom A7672S + SIM card**

The basic communication path is:

```text
                    Cellular Network
                          │
                          │ LTE
                          ▼
                    ┌───────────┐
                    │  A7672S   │
                    │ LTE Modem │
                    └─────┬─────┘
                          │
                    USB / NDIS
                          │
                          ▼
                    ┌───────────┐
                    │  Windows  │
                    │     PC    │
                    └───────────┘
                          │
                          ▼
                       Internet

---
🧰 Hardware Used
1. ESP32-S3

The ESP32-S3 development board is used as the microcontroller platform.

The ESP32-S3 communicates with the A7672S modem and provides the serial interface used to send AT commands.

Example development environment used during testing:

Board: ESP32S3 Dev Module
Serial Port: COM3
---
