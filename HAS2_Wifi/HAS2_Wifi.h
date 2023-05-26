/**
 * @file HAS2_Wifi.h
 * @author 김유빈
 * @brief
 * @version 1.0
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _HAS2_WIFI_
#define _HAS2_WIFI_

#include "Arduino.h"
#include <WiFi.h>
#include <HTTPClient.h>  // wifi 관련 라이브러리
#include <ArduinoJson.h> // wifi 관련 라이브러리
#include <HTTPUpdate.h>  // OTA 관련 라이브러리

void update_started();
void update_finished();
void update_progress(int cur, int total);
void update_error(int err);

// 전역변수를 main 파일에서 사용할 수 있게 extern 선언
extern HTTPClient http;
extern StaticJsonDocument<100> shift_machine;
extern StaticJsonDocument<1000> my;
extern StaticJsonDocument<1000> tag;
extern StaticJsonDocument<500> skill;

typedef struct SSID
{
    const char *name;
} SSID;

// 서버랑 같은 ip 연결
const char ssid[] = "tp-link";       // wifi 이름
const char password[] = "Code3824@"; // wifi 비밀번호

/**
 * @brief HAS2 전용 Wifi 라이브러리
 *
 */
class HAS2_Wifi
{
private:
    String HOST_NAME;
    String PHP_FILE_NAME;
    String server;
    String device_name;
    String my_mac;

    friend class HTTPUpdate;

    void HttpRequest(String request, String string_request);
    void JsonParsing(String request, String json);

public:
    HAS2_Wifi();
    // HAS2_Wifi(String php);
    HAS2_Wifi(String host, String php = "/has2.php");

    void Setup();
    void Setup(char *new_ssid, char *new_password);
    void Setup(String theme);
    void Receive(String device_name);
    void ReceiveMP3(String device_name, int value);
    void ReceiveMine();
    void Send(String device_name, String column, String value);
    void Situation(String affected_device_name, String situation);
    void Loop();
    void Loop(void (*Func)(void));
    void FirmwareUpdate(String device_type, String ip_address = "172.30.1.44");
};

#endif