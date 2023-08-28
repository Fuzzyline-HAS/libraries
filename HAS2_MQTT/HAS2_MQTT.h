/**
 * @file HAS2_MQTT.h
 * @author 김유빈
 * @brief
 * @date 2023-05-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _HAS2_MQTT_
#define _HAS2_MQTT_

#include "Arduino.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPUpdate.h>
#include <ArduinoJson.h>

// extern StaticJsonDocument<200> data[9];
extern String data[9];

// EX) G?P1의 배터리팩 개수 : glove1["BP"]의 형태로 값을 가져오면 됌
#define my_data     data[0]
#define glove1      data[1]
#define glove2      data[2]     
#define glove3      data[3]
#define glove4      data[4]
#define glove5      data[5]
#define glove6      data[6]
#define glove7      data[7]
#define glove8      data[8]

class HAS2_MQTT
{
    private: 
    String mac_address;         // ESP32의 맥주소
    friend class HTTPUpdate;    
    void connect();
    bool OTA;
    bool wifi_connected; 

    public:
    void Setup(MQTT_CALLBACK_SIGNATURE, const char* sever = "172.30.1.44");
    void Setup(char* new_ssid, char* new_password, MQTT_CALLBACK_SIGNATURE, const char* sever = "172.30.1.44");
    void Send(String device_name, String column, String data);
    void Situation(String situation, String tag_device_name);
    void SaveByTopic(const char* topic, String& input_data);
    String GetData(String device_name, String key);
    // void JsonParsing(const char* topic, String& input_data);
    void Publish(String topic, String msg);
    void AddSubscirbe(String topic);
    void ReadSubscirbe();
    void FirmwareUpdate(String device_type, String ip_address = "172.30.1.44");
    static void update_started();
    static void update_finished();
    static void update_progress(int cur, int total);
    static void update_error(int err);
};

#endif