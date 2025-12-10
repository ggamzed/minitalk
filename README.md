# minitalk

A simple communication program using UNIX signals to transmit strings between client and server processes.

## Installation

```bash
git clone https://github.com/yourusername/minitalk.git
cd minitalk
make
```

## Usage

### Start the server
```bash
./server
```
The server will display its PID (Process ID).

### Send messages from client
```bash
./client [server_pid] [message]

# Examples
./client 12345 "Hello World!"
./client 12345 "This is a test message"
./client 12345 "Special chars: áéíóú 🚀"
```

## Features

- **Signal-based communication** using SIGUSR1 and SIGUSR2
- **Binary transmission** of characters bit by bit
- **Unicode support** including special characters and emojis
- **Acknowledgment system** with bidirectional confirmation
- **Multiple client support** with proper message queuing
- **Error handling** for invalid PIDs and transmission failures

## How It Works

1. **Server startup**: Displays PID and waits for signals
2. **Client transmission**: Converts message to binary and sends via signals
3. **Bit-by-bit transfer**: Each character sent as 8 signals (SIGUSR1=0, SIGUSR2=1)
4. **Acknowledgment**: Server confirms each received character
5. **Completion**: Client receives confirmation when message is fully transmitted

## Technical Implementation

- **Signal handling**: Uses `sigaction()` for reliable signal management
- **Binary encoding**: Characters converted to bit sequences
- **Synchronization**: Handshake protocol prevents signal loss
- **Process communication**: Server PID enables targeted messaging

## Signal Protocol

| Signal | Meaning |
|--------|---------|
| `SIGUSR1` | Binary bit 0 |
| `SIGUSR2` | Binary bit 1 |
| **Server → Client** | Character received confirmation |
| **Server → Client** | Message completion acknowledgment |

## Example Output

```bash
# Terminal 1: Server
$ ./server
Server PID: 12345
Waiting for messages...
Received: Hello World!
Message completed from client 67890

# Terminal 2: Client
$ ./client 12345 "Hello World!"
Sending message to server 12345...
Message sent successfully!
```

## Bonus Features

- **Acknowledgment system**: Bidirectional signal confirmation
- **Unicode support**: Extended character sets and emojis
- **Multiple clients**: Server handles concurrent connections
- **Robust error handling**: Invalid PID and signal failure detection

## Requirements

- GCC compiler
- Unix-like system (Linux, macOS)
- Standard C library with signal handling (`signal.h`, `unistd.h`)

## Common Issues

- **Permission denied**: Check if PID exists and is accessible
- **No response**: Verify server is running with correct PID
- **Signal loss**: Built-in acknowledgment system prevents this
- **Special characters**: Use UTF-8 compatible terminal

## About

This project is part of 42 School curriculum, focusing on UNIX signal handling and inter-process communication.