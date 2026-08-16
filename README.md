# ESP32S3-A7672S-Internet-Connectivity
Internet connectivity using ESP32-S3 and SIMCom A7672S LTE modem, with AT-command configuration, PDP activation, USB/NDIS networking, DNS verification, routing tests, and Internet connectivity validation.


A practical project exploring how to use the **SIMCom A7672S 4G/LTE modem with an ESP32-S3** to provide cellular Internet connectivity.

The project started with direct UART communication between the ESP32-S3 and the A7672S. It was then extended to establish cellular network connectivity and expose the modem's Internet connection to a Windows PC through **USB/RNDIS**.

The long-term goal is to turn the ESP32-S3 + A7672S combination into a cellular gateway for an ESP-NOW-based network of multiple ESP32-S3 devices, with MQTT used for cloud communication.

> **Current status:** The A7672S cellular Internet connection has been successfully established and tested from Windows through the USB/RNDIS interface. ESP-NOW mesh networking and MQTT integration are planned for the next phase.

---

## Project Overview

The main hardware used in this project is:

- ESP32-S3 development board
- SIMCom A7672S 4G/LTE modem
- SIM card with an active cellular data connection
- USB connection between the modem board and the computer
- Windows PC for testing and debugging

The project is being developed in stages.

The first stage focuses on understanding and validating the A7672S modem and its cellular Internet connection.

The next stage will introduce multiple ESP32-S3 boards communicating using ESP-NOW, followed by MQTT communication through the ESP32-S3 that has the A7672S modem.

---

# Current Architecture

The current working setup is:

```text
                 Cellular Network
                       │
                       │ 4G/LTE
                       ▼
                ┌──────────────┐
                │   A7672S     │
                │  4G Modem    │
                └──────┬───────┘
                       │
                       │ USB / RNDIS
                       ▼
                ┌──────────────┐
                │   Windows    │
                │      PC      │
                └──────────────┘
                       │
                       ▼
                   Internet

Hardware
ESP32-S3

The ESP32-S3 is used as the main microcontroller for controlling and communicating with the A7672S.

The initial UART configuration used in the project is:

ESP32-S3 GPIO18  →  A7672S TX
ESP32-S3 GPIO17  →  A7672S RX

The UART configuration used during the initial testing was:

Baud rate: 115200
Data bits: 8
Parity: None
Stop bits: 1
