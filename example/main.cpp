#include "Http2spiffs.h"

//by view the site you can upload and download files from the /www directory
//base on the SPIFFS file system
void setup() {
  // Start the server
  http2Spiffs.begin("/www");// these will be the root path of the server, you can change it to any path you want
}


void loop()
{
    http2Spiffs.handle();
}