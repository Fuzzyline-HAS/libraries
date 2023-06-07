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

extern String my_topic;

class HAS2_MQTT
{
    private: 
    String mac_address;         // ESP32의 맥주소
    friend class HTTPUpdate;    
    void connect();
    bool OTA;

    public:
    void Setup(MQTT_CALLBACK_SIGNATURE, const char* sever = "172.30.1.44");
    void Setup(char* new_ssid, char* new_password, MQTT_CALLBACK_SIGNATURE, const char* sever = "172.30.1.44");
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