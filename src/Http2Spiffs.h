#ifndef __HTTP2SPIFFS_H__
#define __HTTP2SPIFFS_H__
/*
Author:BG5ESN AKA xifengzui
Date:2024.12.05
Version:1.0
license:MIT

*/
#include <Arduino.h>
#include <SPIFFS.h> 
#include <ESPAsyncWebServer.h> 
#include "Http2Spiffs.h"

#define HTTP2SPIFFS_PORT 8888 // http2Spiffs的端口号,用于上传文件至SPIFFS下的/www目录,提供联网上传、下载功能
class Http2Spiffs
{
public:
    void begin(const char *rootPath);  // 启动http2Spiffs的服务
    void handle(); // 处理http2Spiffs的请求
private:
    AsyncWebServer *server;
    const char *rootPath;
};
extern Http2Spiffs http2Spiffs;
#endif