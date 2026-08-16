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

```
##  🧰 Hardware Used
1. ESP32-S3

The ESP32-S3 development board is used as the microcontroller platform.

The ESP32-S3 communicates with the A7672S modem and provides the serial interface used to send AT commands.

Example development environment used during testing:

Board: ESP32S3 Dev Module
Serial Port: COM3

## SIMCom A7672S

The cellular modem used in this project is:

SIMCom A7672S-LASC

The modem supports LTE cellular connectivity and provides Internet access through the inserted SIM card.

The modem was identified using:

AT+CGMM

The response was:

A7672S-LASC

##  SIM Card

A working SIM card with cellular data service is required.

The SIM card must:

Be inserted correctly into the A7672S board
Be active
Have cellular network coverage
Have a working mobile-data pla

## USB Data Cable

A proper USB data cable is required.

A charging-only USB cable will not provide the required communication/network interface.

## 💻 Software Used

The project was tested using:

Windows
Arduino IDE
ESP32-S3 board support
Serial Monitor
Windows Command Prompt
PowerShell
Windows network utilities

Important Windows commands used during testing include:

ipconfig
route print
ping
tracert
powershell
netsh

## 🔌 Communication With the A7672S

The A7672S is controlled using standard AT commands.

The ESP32-S3 sends commands to the modem through a serial interface.

For example:

AT

The modem should respond:

OK

This is the simplest way to confirm that the ESP32-S3 and A7672S are communicating correctly.

## 🧪 Step 1 — Check Basic Communication

The first command used was:

AT

Expected response:

OK

This confirms that the modem is responding to AT commands.

If OK is received, communication with the modem is working.

## 🔍 Step 2 — Check Modem Model

The modem model was checked using:

AT+CGMM

Response:

A7672S-LASC

This confirmed that the connected modem is an A7672S-LASC.

## 🔧 Step 3 — Check Firmware Version

The firmware revision was checked using:

AT+CGMR

Response obtained during testing:

+CGMR: A131B01A7672M6

Therefore, the firmware reported by the modem was:

A131B01A7672M6

## 📱 Step 4 — Check SIM Card Status

The SIM card status was checked using:

AT+CPIN?

Response:

+CPIN: READY


OK

The important part is:

+CPIN: READY

This means the SIM card was detected and ready for use.










