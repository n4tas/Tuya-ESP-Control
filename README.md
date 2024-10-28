# Tuya-ESP-Control

This project provides a UBUS module for controlling ESP microcontrollers through a Teltonika RUTX router, with full integration for the Tuya IoT platform. It allows for secure device interaction with Tuya cloud servers and facilitates easy handling of Tuya's IoT protocol on OpenWRT or compatible systems. Core features include device communication, data transmission, and receiving actions from the Tuya cloud, making it ideal for IoT and remote device management scenarios.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Configuration](#configuration)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [License](#license)

---

## Features

- **Tuya IoT Cloud Integration:** Connects to Tuya cloud to control ESP devices from the cloud securely.
- **UBUS Communication:** Interacts with UBUS to enable command execution and data exchange with ESP devices.
- **Signal Handling:** Manages signals like `SIGINT`, `SIGTERM`, and more for graceful shutdown and session control.
- **Device Actions:** Supports device-specific commands (`on`, `off`, `get`) to control connected ESP devices.

---

## Installation

### Prerequisites

- **Router Compatibility**: Teltonika RUTX router or an OpenWRT-compatible system
- **Libraries**: `libjson-c`, `libtuya`, `libubus`, `libubox`, `libblobmsg-json`, `libserialport`
- **Development Environment**: Ensure OpenWRT build tools are installed.

### Building from Source

1. Clone this repository:
   ```bash
   git clone https://github.com/n4tas/tuya-esp-control
   cd tuya-esp-control
   ```

2. Build the project:
   ```bash
   make package/tuya-esp-control/
   ```

3. Install the UBUS module to your system:
   ```bash
   make install
   ```

---

## Configuration

Before running the project, set the required arguments for your device:

```shell
tuya_esp -D <DEVICE_ID> -P <PRODUCT_ID> -S <DEVICE_SECRET>
```

### Command Line Options

| Option         | Flag | Description                   |
|----------------|------|-------------------------------|
| Device Secret  | `-S` | Set the Tuya device secret.   |
| Product ID     | `-P` | Set the Tuya product ID.      |
| Device ID      | `-D` | Set the Tuya device ID.       |
| Daemon Mode    | `-d` | Run as a daemon (optional).   |

---

## Usage

### Start the Tuya ESP Controller

To start the module:
```bash
tuya_esp -D <DEVICE_ID> -P <PRODUCT_ID> -S <DEVICE_SECRET>
```

### Supported UBUS Commands

- **on**: Turns on an ESP device.
- **off**: Turns off an ESP device.
- **get**: Retrieves device status.

Example:
```bash
ubus call esp on '{"port": "<PORT>", "pin": <PIN_NUMBER>}'
```

---

## Project Structure

- **tuya.h**: Header for Tuya MQTT functions and callback handlers.
- **ubus.h**: Manages UBUS interactions with the ESP device.
- **utilities.h**: Utility functions for parsing arguments and handling signals.

---

## Dependencies

- **libjson-c**: JSON manipulation library.
- **libtuya**: Tuya IoT platform integration.
- **libubus**: UBUS communication library for inter-process communication.
- **libubox**: Core library for OpenWRT.
- **libblobmsg-json**: JSON support for UBUS.
- **libserialport**: Serial communication with ESP devices.

---

## License

This project is licensed under the MIT License.