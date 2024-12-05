# HTTP2SPIFFS
[中文](./README.md)

ESP32 File Upload and Management System

## Project Introduction

This project is based on the ESP32 development board and utilizes the SPIFFS file system to implement a simple file upload and management server. Users can upload, download, view, and delete files stored in the `/your-folder` directory through a web interface.

## Features

- **File Upload**: Upload files to ESP32's SPIFFS file system via the web interface.
- **File List Viewing**: Real-time display of the current stored file list, including file names and sizes.
- **File Deletion**: Supports deleting specified files through the web interface.
- **Web Hosting**: Provides a simple web interface that users can access and manage files through a browser.

## Tech Stack

- **Development Board**: ESP32
- **Programming Language**: C++
- **File System**: SPIFFS
- **Web Technologies**: HTML, CSS, JavaScript
- **Server Framework**: ESPAsyncWebServer

## Installation

### Prerequisites

- Install [Arduino IDE](https://www.arduino.cc/en/software) or another IDE that supports ESP32 development.
- Configure the ESP32 development environment. Refer to the [ESP32 Arduino Stack Installation Guide](https://github.com/espressif/arduino-esp32#installation-instructions).

### Library Dependencies

Ensure the following Arduino libraries are installed:

- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [SPIFFS](https://github.com/esp8266/Arduino/tree/master/libraries/SPIFFS)

### Installation Steps

1. Clone this project to your local directory.
2. Open the `example/main.cpp` file.
3. Modify `rootPath` (default `/www`) and the port number (default `8888`) as needed.
4. Upload the project to the ESP32 development board.

## Usage Instructions

1. Connect the ESP32 development board to the computer and upload the project code.
2. Open the serial monitor to view the IP address assigned to the ESP32.
3. Access the ESP32's IP address in a browser, such as `http://192.168.1.100:8888`.
4. Use the web interface to upload, view, or delete files.

## License
[MIT](./LICENSE)。

## Author
- **BG5ESN aka xifengzui** © 2024