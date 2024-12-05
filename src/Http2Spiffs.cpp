#include "Http2Spiffs.h"

// 上传文件的网页
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>ESP32 文件上传</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      background-color: #f0f0f0;
      margin: 0;
      padding: 20px;
    }
    h1 {
      color: #333;
    }
    form {
      background: #fff;
      padding: 20px;
      border-radius: 5px;
      box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
      margin-bottom: 20px;
      display: flex;
      flex-direction: column;
      align-items: flex-start;
    }
    input[type="file"] {
      margin-bottom: 10px;
      padding: 10px;
      border: 1px solid #ccc;
      border-radius: 5px;
      display: block;
    }
    input[type="button"] {
      background-color: #4CAF50;
      color: white;
      border: none;
      padding: 10px 20px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 16px;
      margin: 4px 2px;
      cursor: pointer;
      border-radius: 5px;
    }
    button {
      background-color: #008CBA;
      color: white;
      border: none;
      padding: 10px 20px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 16px;
      margin: 4px 2px;
      cursor: pointer;
      border-radius: 5px;
    }
    ul {
      list-style-type: none;
      padding: 0;
    }
    li {
      background: #fff;
      padding: 10px;
      margin-bottom: 10px;
      border-radius: 5px;
      box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
      display: flex;
      justify-content: space-between;
      align-items: center;
    }
  </style>
</head>
<body>
  <h1>文件选择</h1>
  <form id="uploadForm" enctype="multipart/form-data">
    <input type="file" name="file" id="fileInput">
    <input type="button" value="上传" onclick="uploadFile()">
  </form>
  <h1>文件列表</h1>
  <button onclick="listFiles()">刷新</button>
  <ul id="fileList"></ul>
  <script>
    function uploadFile() {
      const formData = new FormData();
      const fileInput = document.getElementById('fileInput');
      formData.append('file', fileInput.files[0]);

      fetch('/upload', {
        method: 'POST',
        body: formData
      })
      .then(response => response.text())
      .then(result => {
        alert(result);
        listFiles();
      })
      .catch(error => {
        console.error('Error:', error);
      });
    }

    function listFiles() {
      fetch('/list')
        .then(response => response.json())
        .then(files => {
          const fileList = document.getElementById('fileList');
          fileList.innerHTML = '';
          files.forEach(file => {
            const li = document.createElement('li');
            li.textContent = `${file.name} (${file.size} bytes) `;
            const deleteButton = document.createElement('button');
            deleteButton.textContent = '删除';
            deleteButton.onclick = () => deleteFile(file.name);
            li.appendChild(deleteButton);
            fileList.appendChild(li);
          });
        });
    }

    function deleteFile(filename) {
      fetch(`/delete?filename=${filename}`, { method: 'GET' })
        .then(response => response.text())
        .then(result => {
          alert(result);
          listFiles();
        });
    }

    document.addEventListener('DOMContentLoaded', listFiles);
  </script>
</body>
</html>
)rawliteral";

void Http2Spiffs::begin(const char *rootPath)
{
  if (server != NULL)
  {
    log_e("Http2Spiffs has been initialized");
    return;
  }
  if(SPIFFS.begin(true))
  {
    return;
  }
  this->rootPath = rootPath;
  server = new AsyncWebServer(HTTP2SPIFFS_PORT);
  log_i("Http2Spiffs begin at port %d", HTTP2SPIFFS_PORT);
  // 上传文件
  server->on("/upload", HTTP_POST, [](AsyncWebServerRequest *request)
             {
               log_d(" /upload, method:%s", request->method() == HTTP_GET ? "GET" : "POST");
               request->send(200); // 200 OK
             },
             [this](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
             {
                    filename = "/" + filename;
                    filename = this->rootPath + filename;
                    
                    if (!index) {
                        // 如果文件已经存在，删除它
                        if (SPIFFS.exists(filename)) {
                            SPIFFS.remove(filename);
                        }
                        log_d("UploadStart: %s\n", filename.c_str());
                        if (!SPIFFS.open(filename, FILE_WRITE)){
                            return request->send(500, "text/plain", "Failed to open file for writing");
                        }}

                    File file = SPIFFS.open(filename, FILE_APPEND);// FILE_APPEND表示追加写入
                    
                    if (file){
                        if (file.write(data, len) != len) 
                        {
                            return request->send(500, "text/plain", "Failed to write file");
                        }
                        file.close();
                    }
                    
                    if (final){
                        log_d("UploadEnd: %s\n", filename.c_str());
                        request->send(200, "text/plain", "File Uploade d");
                    } });

  // 展示文件目录
  server->on("/list", HTTP_GET, [this](AsyncWebServerRequest *request)
             {
    String output = "[";
    File root = SPIFFS.open(this->rootPath);
    if (!root || !root.isDirectory()) {
        request->send(500, "text/plain", "Failed to open directory");
        log_d("Failed to open directory: /");
        return;
    }

    File file = root.openNextFile();
    while (file) {
        if (output != "[")
            output += ',';
        output += "{\"name\":\"";
        String filename = String(file.name());
        if (filename.startsWith("/")) {
          filename = filename.substring(1);
        }
        output += filename;
        output += "\",\"size\":";
        output += file.size();
        output += "}";
        file.close();
        file = root.openNextFile();
    }
    root.close();
    output += "]";
    request->send(200, "application/json", output);
    log_d("list:%s", output.c_str()); });

  // 删除文件
  // 删除文件
  server->on("/delete", HTTP_GET, [this](AsyncWebServerRequest *request)
             {
    if (request->hasParam("filename")) {
        String filename = "/" + request->getParam("filename")->value();
        filename = this->rootPath + filename;
        // 删除文件
        if (SPIFFS.remove(filename)) {
            request->send(200, "text/plain", "File deleted");
            log_d("File deleted: %s", filename.c_str());
        } else {
            request->send(500, "text/plain", "Failed to delete file");
            log_d("Failed to delete file: %s", filename.c_str());
        }
    } else {
        request->send(400, "text/plain", "Filename not provided");
        log_d("Filename not provided");
    } });

  // 提供网页
  server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
             { request->send_P(200, "text/html", index_html); });

  server->begin();
}

void Http2Spiffs::handle()
{
  // TODO : 无操作
}

Http2Spiffs http2Spiffs;