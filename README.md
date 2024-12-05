# HTTP2SPIFFS

[ENGLISH](./README_en.md)

ESP32 文件上传与管理系统

## 项目简介

本项目基于 ESP32 开发板，利用 SPIFFS 文件系统实现了一个简单的文件上传与管理服务器。用户可以通过网页界面上传、下载、查看和删除存储在 `/your-folder` 目录下的文件。

## 功能

- **文件上传**：通过网页界面上传文件到 ESP32 的 SPIFFS 文件系统。
- **文件列表查看**：实时显示当前存储的文件列表，包括文件名和大小。
- **文件删除**：支持通过网页界面删除指定文件。
- **网页托管**：提供一个简单的网页界面，用户可以通过浏览器访问并管理文件。

## 技术栈

- **开发板**：ESP32
- **编程语言**：C++
- **文件系统**：SPIFFS
- **网页技术**：HTML, CSS, JavaScript
- **服务器框架**：ESPAsyncWebServer

## 安装

### 前提条件

- 安装 [Arduino IDE](https://www.arduino.cc/en/software) 或其他支持 ESP32 开发的 IDE。
- 配置 ESP32 开发环境。参考 [ESP32 Arduino 栈安装指南](https://github.com/espressif/arduino-esp32#installation-instructions)。

### 库依赖

确保安装以下 Arduino 库：

- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [SPIFFS](https://github.com/esp8266/Arduino/tree/master/libraries/SPIFFS)

### 安装步骤

1. 克隆本项目到本地目录。
2. 打开 `example/main.cpp` 文件。
3. 根据需要修改 `rootPath`（默认 `/www`）和端口号（默认 `8888`）。
4. 将项目上传到 ESP32 开发板。

## 使用说明

1. 连接 ESP32 开发板到电脑，并上传项目代码。
2. 打开串口监视器，查看 ESP32 分配的 IP 地址。
3. 在浏览器中访问 ESP32 的 IP 地址，如 `http://192.168.1.100:8888`。
4. 使用网页界面上传、查看或删除文件。

## 许可

本项目采用 [MIT 许可证](./LICENSE)。

## 作者

- **BG5ESN aka xifengzui** © 2024