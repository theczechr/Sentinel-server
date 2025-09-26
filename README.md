<p align="center">
  <img src="drogon.png" alt="Sentinel Logo" height="100" />
</p>

<h2 align="center">Sentinel Server</h2>

<p align="center">
  Privacy and security-focused messaging application featuring end-to-end encryption.
  <br />
  <em>Built with WebSockets, Drogon HTTP web framework, and SQL database for secure communication.</em>
</p>

<p align="center">
  <a href="#features">Features</a> •
  <a href="#installation">Installation</a> •
  <a href="#building">Building</a> •
  <a href="#usage">Usage</a> •
  <a href="#e2e-encryption">E2E Encryption</a> •
  <a href="#testing">Testing</a> •
  <a href="#architecture">Architecture</a> •
  <a href="#contributing">Contributing</a>
</p>

---

## About

Sentinel is a proof-of-concept, privacy and security-focused messaging application co-created as a demonstration of secure communication protocols. It features end-to-end encryption and utilizes WebSockets, the Drogon HTTP web framework, and an SQL database to provide a secure and efficient communication platform. After completing the text-based user interface and proof of concept, the project was open-sourced for the community to learn from and build upon.

## Features

- **End-To-End Encryption**: All messages are encrypted between clients for maximum privacy
- **WebSocket Support**: Real-time, bidirectional communication for instant messaging
- **Drogon Framework**: High-performance C++ HTTP application framework
- **SQL Database**: Reliable data persistence with database integration
- **Text-Based UI**: Clean, minimal interface for terminal-based communication
- **Privacy-Focused**: Built with security and user privacy as primary concerns

## Installation

### Prerequisites

- C++ compiler with C++17 support
- CMake (3.10 or higher)
- vcpkg package manager (recommended)
- Drogon framework

### Clone the Repository

```bash
git clone --recursive https://github.com/theczechr/Sentinel-server.git
cd Sentinel-server
```

### Install Dependencies

#### Using vcpkg (Windows)

```bash
vcpkg install drogon:x64-windows openssl
```

#### Using vcpkg (Linux/macOS)

```bash
vcpkg install drogon openssl
```

## Building

### Using CMake

```bash
mkdir build
cd build
cmake ..
make
```

### Windows (Visual Studio)

1. Open the project in Visual Studio
2. Configure CMake with vcpkg toolchain
3. Build the solution


## E2E Encryption

The server is designed as a dumb relay. It does not decrypt messages. Clients are responsible for encrypting/decrypting.

- **Register**: `/register?username=<u>&pub_key_fprint=<f>&recovery_phrase=<r>[&public_key=<base64>]`
- **Publish/rotate key**: `/publishPubKey?pub_key_fprint=<f>&public_key=<base64>&signed_payload=<base64>&signature=<base64>`
  - Server validates that `pub_key_fprint` equals `SHA-256(public_key)` in lowercase hex and verifies the Ed25519 `signature` over `signed_payload`.
  - `signed_payload` format: `pub_key_fprint|timestamp` (as UTF-8), Base64-encoded; max age 5 minutes.
  - Rate limit: 5 publish attempts per minute per `ip|pub_key_fprint`.
- **Discover peer key**: `/getPubKey?pub_key_fprint=<peer_fingerprint>` returns the peer’s public key string (empty if unknown).
- **Send messages**: Encrypt on the client, then send the opaque ciphertext to `/sendtxt?room_name=<room>`. The server relays without inspecting or logging message contents.
- **Message size limit**: Text frames larger than 64KB are dropped by the server.
- **Public key persistence**: Published keys are stored on disk in a simple file-backed store (`keys.db`). Replace with a production database for real deployments.

## Testing

Build tests alongside the project:

```bash
mkdir build && cd build
cmake ..
make SentinelTests
./tests/SentinelTests  # or run per-test binaries if split
```


## License

This project is open source and available under the [MIT License](LICENSE).

## Acknowledgments

- Built with [Drogon](https://github.com/drogonframework/drogon) - A C++14/17-based HTTP application framework
- Inspired by the need for privacy-focused communication tools

---

<p align="center">
  Made with ❤️ for secure communication
</p>