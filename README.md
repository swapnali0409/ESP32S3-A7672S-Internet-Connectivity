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

## 📡 Step 5 — Check Cellular Packet Attachment

The modem's packet-domain attachment was checked using:

AT+CGATT?

Response:

+CGATT: 1


OK

The value:

1

means the modem is attached to the packet data service.

So:

+CGATT: 1

indicates that packet data attachment is active.

## 🌐 Step 6 — Check PDP Context Activation

The active PDP contexts were checked using:

AT+CGACT?

The response obtained was:

+CGACT: 1,1
+CGACT: 8,1
+CGACT: 9,0


OK

The important context was:

+CGACT: 1,1

This means PDP context ID 1 was active.

The modem also reported:

+CGACT: 8,1

while:

+CGACT: 9,0

indicated that context 9 was not active.

## 🌍 Step 7 — Check Cellular IP Address

The assigned PDP addresses were checked using:

AT+CGPADDR

Response:

+CGPADDR: 1,10.201.27.246
+CGPADDR: 8,10.240.227.70,254.128.0.0.0.0.0.0.0.0.0.0.241.73.26.12


OK

The important IPv4 address for PDP context 1 was:

10.201.27.246

This confirmed that the cellular network had assigned an IP address to the modem's data context.

## 📶 Step 8 — Check PDP/APN Configuration

The PDP context configuration was checked using:

AT+CGDCONT?

The modem returned:

+CGDCONT: 1,"IP","www","10.201.27.246",0,0,,,,
+CGDCONT: 8,"IPV4V6","IMS","10.240.227.70,254.128.0.0.0.0.0.0.0.0.0.0.241.73.26.12",0,0,0,2,1,1
+CGDCONT: 9,"IP","JIONET"


OK

The main Internet PDP context was:

+CGDCONT: 1,"IP","www","10.201.27.246",...

Therefore, the APN configured for PDP context 1 was:

www

Another context was:

+CGDCONT: 9,"IP","JIONET"

which was not active during the test.

## 🌐 Step 9 — Check DNS Configuration

DNS configuration was checked using:

AT+CDNSCFG?

The modem returned:

Primary IPv4 DNS: 114.114.114.114,Secondary IPv4 DNS: 8.8.8.8


Primary IPv6 DNS: ::,Secondary IPv6 DNS: ::


OK

The configured IPv4 DNS servers were:

Primary DNS:
114.114.114.114


Secondary DNS:
8.8.8.8

The IPv6 DNS fields were not configured:

Primary IPv6 DNS: ::
Secondary IPv6 DNS: ::

## ⚠️ AT+CGNAPN Result

The command:

AT+CGNAPN

was also tested.

The modem returned:

ERROR

This command was therefore not used for determining the working APN.

Instead, the existing PDP configuration was inspected using:

AT+CGDCONT?

which showed the active Internet context and APN.

## 📡 Step 10 — Check Network Operator

The currently selected network operator was checked using:

AT+COPS?

Response:

+COPS: 0,2,"405864",7


OK

This confirms that the modem was registered with a cellular operator/network.

The response contains:

405864

as the operator/network identifier reported by the modem.

The final field:

7

indicates the access technology reported by the modem.

## 🔌 Step 11 — Check USB/Dial Mode

The modem's dial mode was checked using:

AT+DIALMODE?

Response:

+DIALMODE: 1


OK

The modem was then changed to:

AT+DIALMODE=0

Response:

OK

This configuration was part of preparing the modem for the USB/network interface operation.

## 🌐 Step 12 — USB Network Mode

The modem also exposes a USB networking interface.

The configuration was checked using:

AT$MYCONFIG="usbnetmode"

Response:

$MYCONFIG: "usbnetmode",0,1


OK

This configuration is important when using the A7672S as a USB network interface.

The USB/network configuration was used together with the Remote NDIS interface detected by Windows.

## 🖥️ Step 13 — Windows Detects the Modem Network Interface

After connecting the A7672S to Windows using USB, Windows detected a network adapter named:

Remote NDIS based Internet Sharing Device

PowerShell was used to check the network adapters:

Get-NetAdapter | Format-Table Name,InterfaceDescription,Status,LinkSpeed

The relevant result was:

Name       InterfaceDescription                           Status LinkSpeed
----       --------------------                           ------ ---------
Wi-Fi      Realtek RTL8852BE WiFi 6 802.11ax PCIe Adapter Up     1.2 Gbps
Ethernet 3 Remote NDIS based Internet Sharing Device      Up     10 Mbps
Ethernet 2 VirtualBox Host-Only Ethernet Adapter          Up     1 Gbps

The important interface was:

Ethernet 3
Remote NDIS based Internet Sharing Device

This confirmed that Windows recognized the A7672S USB networking interface.

## 🧾 Step 14 — Check Windows IP Configuration

The Windows network configuration was checked using:

ipconfig

The Remote NDIS interface was:

Ethernet adapter Ethernet 3:


   IPv4 Address. . . . . . . . . . . : 192.168.0.100
   Subnet Mask . . . . . . . . . . . : 255.255.255.0
   Default Gateway . . . . . . . . . : 192.168.0.1

This is important because it shows that Windows received a local IP configuration from the USB networking interface.

The relevant network was:

IP Address:
192.168.0.100


Subnet Mask:
255.255.255.0


Gateway:
192.168.0.1

## 🧭 Step 15 — Verify the Local Gateway

The first connectivity test was:

ping 192.168.0.1

The result was successful:

Pinging 192.168.0.1 with 32 bytes of data:
Reply from 192.168.0.1: bytes=32 time<1ms TTL=128
Reply from 192.168.0.1: bytes=32 time<1ms TTL=128
Reply from 192.168.0.1: bytes=32 time<1ms TTL=128
Reply from 192.168.0.1: bytes=32 time<1ms TTL=128

Statistics:

Packets: Sent = 4, Received = 4, Lost = 0 (0% loss)

This confirmed connectivity between Windows and the local network gateway.

## 🌎 Step 16 — Test Internet Connectivity

The next test was:

ping 8.8.8.8

The result was:

Pinging 8.8.8.8 with 32 bytes of data:
Reply from 8.8.8.8: bytes=32 time=58ms TTL=112
Reply from 8.8.8.8: bytes=32 time=61ms TTL=112
Reply from 8.8.8.8: bytes=32 time=59ms TTL=112
Reply from 8.8.8.8: bytes=32 time=61ms TTL=112

Statistics:

Packets: Sent = 4
Received = 4
Lost = 0 (0% loss)


Minimum = 58ms
Maximum = 61ms
Average = 59ms

This successfully confirmed Internet connectivity.

## 🔎 Step 17 — Test DNS Resolution

To verify both Internet access and DNS resolution, the following command was used:

ping google.com

Windows resolved the hostname to:

142.250.146.139

The response was:

Pinging google.com [142.250.146.139] with 32 bytes of data:
Reply from 142.250.146.139: bytes=32 time=63ms TTL=109
Reply from 142.250.146.139: bytes=32 time=63ms TTL=109
Reply from 142.250.146.139: bytes=32 time=63ms TTL=109
Reply from 142.250.146.139: bytes=32 time=65ms TTL=109

Statistics:

Packets: Sent = 4
Received = 4
Lost = 0 (0% loss)


Minimum = 63ms
Maximum = 65ms
Average = 63ms

This verified that:

Internet connectivity was available.
DNS resolution was working.
The hostname google.com could be resolved to an IP address.
The destination was reachable.

## 🛣️ Step 18 — Trace the Internet Route

The route to Google's public DNS server was checked using:

tracert -d 8.8.8.8

The final successful trace was:

Tracing route to 8.8.8.8 over a maximum of 30 hops


  1     *        *        *     Request timed out.
  2     *        *        *     Request timed out.
  3    18 ms     4 ms     4 ms  27.107.37.149
  4     9 ms     *        *     203.199.133.233
  5    19 ms     8 ms     8 ms  172.23.78.238
  6     7 ms     7 ms     7 ms  115.113.165.98
  7     7 ms    11 ms     8 ms  172.253.69.227
  8     9 ms    12 ms     9 ms  142.250.227.71
  9    11 ms    11 ms    14 ms  8.8.8.8


Trace complete.

The important result is:

9    11 ms    11 ms    14 ms  8.8.8.8

The trace reached the destination successfully.

Some intermediate routers did not respond to traceroute packets. This is normal because many routers/firewalls do not respond to traceroute probes.

The important point is that the final destination was reached.

## 🧭 Windows Routing

Windows routing was inspected using:

route print

At one point, the routing table contained two default routes:

0.0.0.0          0.0.0.0       10.10.10.1      10.10.13.70
0.0.0.0          0.0.0.0      192.168.0.1    192.168.0.100

These corresponded to different network interfaces.

The Wi-Fi interface used:

10.10.13.70

with gateway:

10.10.10.1

The Remote NDIS interface used:

192.168.0.100

with gateway:

192.168.0.1

Windows uses route metrics to decide which route should normally be preferred when multiple default routes are present.

⚙️ Changing Network Interface Metric

The Remote NDIS interface was identified as interface index:

53

The following command was used from an Administrator Command Prompt:

netsh interface ipv4 set interface 53 metric=10

The reason for changing the metric was to give the desired interface a higher routing preference.

When Windows displayed:

The requested operation requires elevation.

the Command Prompt had to be opened as Administrator.

## 👨‍💻 How to Open Command Prompt as Administrator

On Windows:

Press the Windows key.
Type:
cmd
Right-click Command Prompt.
Select:
Run as administrator
If Windows asks for permission, select Yes.

The window should normally show:

C:\Windows\System32>

Then administrator-only networking commands can be executed.

## 🔍 Useful Windows Commands
Display IP configuration
ipconfig

More detailed:

ipconfig /all
Display network adapters
Get-NetAdapter | Format-Table Name,InterfaceDescription,Status,LinkSpeed
Display routing table
route print
Test local gateway
ping 192.168.0.1
Test Internet without DNS
ping 8.8.8.8
Test Internet with DNS
ping google.com
Trace route to the Internet
tracert -d 8.8.8.8

## 📋 Important A7672S AT Command Reference

The following commands were important during this project.

AT Command	Purpose
AT	Check basic modem communication
AT+CGMM	Read modem model
AT+CGMR	Read firmware version
AT+CPIN?	Check SIM status
AT+CGATT?	Check packet-domain attachment
AT+CGACT?	Check PDP context activation
AT+CGPADDR	Display PDP context IP addresses
AT+CGDCONT?	Display PDP/APN configuration
AT+CDNSCFG?	Display DNS configuration
AT+CGNAPN	Request automatic APN information
AT+COPS?	Check current network/operator
AT+DIALMODE?	Check dial mode
AT+DIALMODE=0	Set dial mode
AT$MYCONFIG="usbnetmode"	Check USB network mode

## 📚 Important Command Outputs
Modem identification
AT+CGMM

A7672S-LASC
OK

Firmware
AT+CGMR

+CGMR: A131B01A7672M

OK
SIM status
AT+CPIN?

+CPIN: READY

OK
Packet attachment
AT+CGATT?

+CGATT: 1

OK
PDP activation
AT+CGACT?


+CGACT: 1,1
+CGACT: 8,1
+CGACT: 9,0


OK
PDP IP address
AT+CGPADDR


+CGPADDR: 1,10.201.27.246
+CGPADDR: 8,10.240.227.70,254.128.0.0.0.0.0.0.0.0.0.0.241.73.26.12


OK
PDP/APN configuration
AT+CGDCONT?


+CGDCONT: 1,"IP","www","10.201.27.246",0,0,,,,
+CGDCONT: 8,"IPV4V6","IMS","10.240.227.70,254.128.0.0.0.0.0.0.0.0.0.0.241.73.26.12",0,0,0,2,1,1
+CGDCONT: 9,"IP","JIONET"


OK
DNS configuration
AT+CDNSCFG?


Primary IPv4 DNS: 114.114.114.114,Secondary IPv4 DNS: 8.8.8.8

Primary IPv6 DNS: ::,Secondary IPv6 DNS: ::

OK
Network operator
AT+COPS?

+COPS: 0,2,"405864",7

OK
USB network configuration
AT$MYCONFIG="usbnetmode"

$MYCONFIG: "usbnetmode",0,1

OK
Dial mode
AT+DIALMODE?

+DIALMODE: 1

OK

Changed using:

AT+DIALMODE=0

Response:

OK

## 🔄 Overall Data Flow

The completed setup can be represented as:
                 ┌─────────────────────┐
                 │      SIM Card       │
                 │   Mobile Data Plan  │
                 └──────────┬──────────┘
                            │
                            │ Cellular / LTE
                            ▼
                 ┌─────────────────────┐
                 │     SIMCom A7672S   │
                 │      LTE Modem      │
                 └──────────┬──────────┘
                            │
                            │ USB Network
                            ▼
                 ┌─────────────────────┐
                 │       Windows       │
                 │ Remote NDIS Adapter │
                 └──────────┬──────────┘
                            │
                            │ IP Routing
                            ▼
                       Internet
                            │
             ┌──────────────┴──────────────┐
             │                             │
             ▼                             ▼
        8.8.8.8                       google.com




## 🧠 What Each Layer Does
SIM Card

Provides cellular network authentication and mobile data service.

SIM → Cellular Network
A7672S

The A7672S handles:

Cellular registration
Packet attachment
PDP context
APN
Cellular IP address
DNS
LTE data communication

The modem is controlled using AT commands.

ESP32-S3

The ESP32-S3 acts as the controller that communicates with the A7672S.

It can send commands such as:

AT
AT+CPIN?
AT+CGATT?
AT+CGACT?
AT+CGPADDR
AT+CGDCONT?
AT+COPS?
AT+DIALMODE?
USB/NDIS

The A7672S can expose a USB networking interface to Windows.

Windows recognizes this interface as:

Remote NDIS based Internet Sharing Device

The interface can then obtain an IP configuration such as:

192.168.0.100

with gateway:

192.168.0.1
Windows

Windows uses the network interface to send IP packets toward the cellular modem.

Once the routing is configured correctly, applications on Windows can use the cellular Internet connection.

## ✅ Verification Checklist

The following checks were successfully performed during the project:

 ESP32-S3 detected
 A7672S detected
 AT communication working
 A7672S model verified
 Firmware version verified
 SIM card detected
 SIM status reported as READY
 Packet attachment confirmed
 PDP context confirmed active
 Cellular IP address obtained
 APN configuration inspected
 DNS configuration inspected
 Network operator detected
 USB network mode inspected
 Dial mode configured
 Windows detected Remote NDIS adapter
 Windows received 192.168.0.100
 Local gateway reachable
 8.8.8.8 reachable
 google.com reachable
 DNS resolution working
 Internet route verified using tracert
 
## 🧪 Final Internet Connectivity Test

The final test consisted of:

ping 192.168.0.1

Result:

0% packet loss

Then:

ping 8.8.8.8

Result:

0% packet loss

Then:

ping google.com

Result:

0% packet loss

This confirmed that the system was able to reach the Internet and resolve domain names.

## 📝 Important Notes
1. Use a USB data cable

The USB cable must support data communication.

A charging-only cable will not work for USB networking.

2. SIM card must have data service

The modem can communicate with the ESP32-S3 even when the SIM has no active data service.

However, Internet connectivity requires:

Valid SIM
Network registration
Mobile data service
Correct APN
Active PDP context
3. +CGATT: 1 is important

When checking:

AT+CGATT?

the desired result is:

+CGATT: 1

This indicates packet-domain attachment.

4. PDP context must be active

For example:

+CGACT: 1,1

means PDP context 1 is active.

5. A cellular IP address should be assigned

Using:

AT+CGPADDR

the modem should report an IP address.

For example, during this project:

10.201.27.246

was assigned to PDP context 1.

6. DNS and Internet connectivity are different checks

A successful:

ping 8.8.8.8

tests IP connectivity.

A successful:

ping google.com

also tests hostname resolution/DNS.

Both tests are useful.

## 🛠️ Troubleshooting Guide
Problem: AT does not return OK

Check:

USB/serial connection
Correct COM port
Baud rate
TX/RX connections
Power supply
Modem power state
Problem: +CPIN: NOT READY

Check:

SIM card insertion
SIM card condition
SIM PIN requirement
SIM compatibility
Problem: +CGATT: 0

The modem is not attached to packet data.

Check:

AT+COPS?
AT+CSQ
AT+CGATT?

Also check cellular coverage and whether the SIM has an active data plan.

Problem: No IP address from AT+CGPADDR

Check:

AT+CGATT?
AT+CGACT?
AT+CGDCONT?

The PDP context needs to be correctly configured and activated.

Problem: Windows does not show Remote NDIS

Check:

USB data cable
A7672S USB connection
Windows Device Manager
A7672S USB networking configuration
Modem USB mode
Required drivers

Then check:

Get-NetAdapter
Problem: ping 192.168.0.1 works but Internet does not

Check:

route print

Look for a default route:

0.0.0.0    0.0.0.0

Also verify that the correct network interface has the preferred route.

Problem: ping 8.8.8.8 works but ping google.com fails

This usually indicates a DNS problem.

Check:

AT+CDNSCFG?

and Windows DNS configuration.

## 📊 Final Status

The A7672S cellular data connection was successfully validated.

The following chain was confirmed:

SIM Card
    ↓
LTE Network
    ↓
SIMCom A7672S
    ↓
USB / Remote NDIS
    ↓
Windows
    ↓
IP Gateway
    ↓
Internet
    ↓
8.8.8.8 / Google

The final tests showed:

Local Gateway       → SUCCESS
8.8.8.8             → SUCCESS
google.com          → SUCCESS
DNS Resolution      → SUCCESS
Traceroute          → SUCCESS

Therefore, the project successfully demonstrated cellular Internet connectivity using the SIMCom A7672S LTE modem and ESP32-S3-based control/configuration.

## 🚀 Future Development

This project establishes the basic cellular Internet connectivity required for future IoT development.

Possible future extensions include:

Direct Internet communication from the ESP32-S3
HTTP/HTTPS requests
MQTT communication
Sending sensor data over cellular networks
Remote device monitoring
Cloud connectivity
ESP-NOW communication between ESP32 devices
Multi-node IoT networking
Cellular gateway development

These features are outside the scope of the current project and can be developed as separate stages.

## 👤 Project Summary

This project was developed to understand the complete process of bringing a SIMCom A7672S LTE modem online and verifying cellular Internet connectivity.

The most important lesson from the project is that Internet connectivity is not just about connecting the modem to a SIM card. The complete chain must work:

SIM
 ↓
Network Registration
 ↓
Packet Attachment
 ↓
PDP Context
 ↓
APN
 ↓
IP Address
 ↓
DNS
 ↓
USB/NDIS
 ↓
Windows Routing
 ↓
Internet

By checking each layer independently with AT commands and Windows networking tools, the connection can be diagnosed systematically instead of treating the modem as a black box.

## 📌 Key AT Command Quick Reference
AT
AT+CGMM
AT+CGMR
AT+CPIN?
AT+CGATT?
AT+CGACT?
AT+CGPADDR
AT+CGDCONT?
AT+CDNSCFG?
AT+CGNAPN
AT+COPS?
AT+DIALMODE?
AT+DIALMODE=0
AT$MYCONFIG="usbnetmode"

## 📌 Key Windows Commands Quick Reference
ipconfig
ipconfig /all
route print
ping 192.168.0.1
ping 8.8.8.8
ping google.com
tracert -d 8.8.8.8

PowerShell:

Get-NetAdapter | Format-Table Name,InterfaceDescription,Status,LinkSpeed

Administrator networking command:

netsh interface ipv4 set interface 53 metric=10

## ⭐ Result

ESP32-S3 + SIMCom A7672S → Cellular Network → USB/Remote NDIS → Windows → Internet

Internet connectivity successfully verified using gateway ping, public IP ping, DNS resolution, and traceroute.












