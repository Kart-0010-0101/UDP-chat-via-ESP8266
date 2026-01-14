
# ESP8266 UDP Chat (Minimal)

A minimal, bidirectional text communication system between two ESP8266 boards using UDP over Wi-Fi.

This project demonstrates the basics of packet-based communication:
- sending text
- receiving text
- acknowledging delivery (ACK)

The same firmware runs on both ESPs.

---

## Features

- Two-way text chat (like a very basic WhatsApp)
- UDP-based communication
- Serial Monitor / PuTTY as the user interface
- Message acknowledgment (ACK)
- Minimal code, easy to understand
- No external servers or cloud required

---

## Hardware Required

- 2 × ESP8266 (NodeMCU / ESP-12 recommended)
- Wi-Fi router
- USB cables

---

## Software Required

- Arduino IDE
- ESP8266 board package
- Serial Monitor or PuTTY (115200 baud)

---

## How It Works

Each ESP:
1. Connects to the same Wi-Fi network
2. Listens on a UDP port
3. Sends messages typed via serial
4. Receives messages and replies with an ACK

### Message Format

<ID>|MSG|<NODE>:<TEXT>

makefile
Copy code

Example:
3|MSG|A:Hello

shell
Copy code

### Acknowledgment Format

<ID>|ACK|OK

---

## Setup Instructions

### 1. Edit Wi-Fi Credentials

```c
#define WIFI_SSID     "YOUR_WIFI"
#define WIFI_PASSWORD "YOUR_PASSWORD"
```

2. Set Node ID and Peer IP

On ESP A:
```c
#define NODE_ID 'A'
#define PEER_IP "ESP_B_IP"
```

On ESP B:
```c
#define NODE_ID 'B'
#define PEER_IP "ESP_A_IP"
```

Each ESP prints its IP address on boot.

3. Upload the Same Sketch to Both ESPs

Board: NodeMCU 1.0 (ESP-12E)
Baud rate: 115200

4. Open Serial Terminals

Arduino Serial Monitor or PuTTY
Baud: 115200
Line ending: Newline (or CR/LF)

Type a message and press Enter to send.

Example Output
Sender:
```c
[SENT] hello
[DELIVERED]
```

Receiver:
```c
[RECEIVED] A:hello
```

## Limitations

No retries on packet loss
No encryption
No automatic peer discovery
Hardcoded peer IPs

These were intentionally omitted to keep the code minimal and educational.

## Purpose

This project is meant to:

teach basic networking concepts
demonstrate UDP communication
show how acknowledgments work
provide a clean foundation for further extensions

## Possible Extensions

Message retry on missing ACK
Duplicate message filtering
Peer discovery
Encryption
Multi-node support
