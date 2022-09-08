#ifndef _HAS2_WIFI_
#define _HAS2_WIFI_

#include "Arduino.h"
#include "device_type.h"
#include <WiFi.h>
#include <HTTPClient.h>  // wifi 관련라이브러리
#include <ArduinoJson.h> // wifi 관련라이브러리

extern HTTPClient http;

//서버랑 같은 ip 연결
const char ssid[] = "KT_GiGA_6C64";   // wifi 이름
const char password[] = "ed46zx1198"; // wifi 비밀번호

class HAS2_Wifi
{
private:
    String HOST_NAME;
    String PHP_FILE_NAME;
    String server;
    String device_type;
    String device_name;
    String my_mac;

    void HttpRequest(String string_request);
    void ReceiveMine(String mac_add);

public:
    HAS2_Wifi();
    HAS2_Wifi(String php);
    void Setup(String type);
    void Receive(String device_name);
    void Send(String device_name, String column, String value);
    void Loop();
};

#endif