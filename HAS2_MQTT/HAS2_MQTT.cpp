/**
 * @file HAS2_MQTT.cpp
 * @author 김유빈
 * @brief
 * @date 2023-05-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <HAS2_MQTT.h>

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

String my_topic; // 자신의 mac 주소 기반 topic

/**
 * @brief Wifi, MQTT 서버 연결
 *
 * @param MQTT_CALLBACK_SIGNATURE #define으로 형태를 지정한 callback 함수포인터
 * @param sever 연결 해야하는 mosqitto broker의 서버 주소 [default : 172.30.1.44]
 */
void HAS2_MQTT::Setup(MQTT_CALLBACK_SIGNATURE, const char *sever)
{
    int wifiConnectCnt = 0;
    WiFi.begin("tp-link", "Code3824@");

    mac_address = WiFi.macAddress();
    Serial.print("MY MAC = ");
    Serial.println(mac_address);

    Serial.println("Connecting....");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
        if (wifiConnectCnt++ > 25)
        {
            Serial.println("Restart ESP");
            ESP.restart();
            wifi_connected = false;
        }
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WiFi connected");
        wifi_connected = true;
    }
    else
    {
        Serial.println("WiFi not connected");
    }

    delay(1000);

    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    my_topic = mac_address.substring(12);
    Serial.print("MY TOPIC = ");
    Serial.println(my_topic);

    if (wifi_connected)
    {
        client.setServer(sever, 1883);
        client.setCallback(callback);
        connect();
    }
}

/**
 * @brief Wifi, MQTT 서버 연결
 *
 * @param new_ssid  Wifi SSID
 * @param new_password  Wifi Password
 * @param MQTT_CALLBACK_SIGNATURE #define으로 형태를 지정한 callback 함수포인터
 * @param sever 연결 해야하는 mosquitto broker의 서버 주소 [default : 172.30.1.44]
 */
void HAS2_MQTT::Setup(char *new_ssid, char *new_password, MQTT_CALLBACK_SIGNATURE, const char *sever)
{
    int wifiConnectCnt = 0;
    WiFi.begin(new_ssid, new_password);

    mac_address = WiFi.macAddress();
    Serial.print("MY MAC = ");
    Serial.println(mac_address);

    Serial.println("Connecting....");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
        if (wifiConnectCnt++ > 25)
        {
            Serial.println("Restart ESP");
            ESP.restart();
            wifi_connected = false;
        }
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WiFi connected");
        wifi_connected = true;
    }
    else
    {
        Serial.println("WiFi not connected");
    }

    delay(1000);

    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    my_topic = mac_address.substring(12);
    Serial.print("MY TOPIC = ");
    Serial.println(my_topic);

    if (wifi_connected)
    {
        client.setServer(sever, 1883);
        client.setCallback(callback);
        connect();
    }
}
/**
 * @brief [private] mosquitto broker와 연결
 *
 */
void HAS2_MQTT::connect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        int loop_num = 0;
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP32_";
        clientId += my_topic;
        // Attempt to connect
        if (client.connect(clientId.c_str()))
        {
            Serial.println("connected");
            AddSubscirbe("ALL");
            AddSubscirbe("GLOVE");
            AddSubscirbe(my_topic);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 2 seconds");
            if(loop_num++ > 2) {
                Serial.println("Restart ESP");
                ESP.restart();
            }
            delay(2000);
        }
    }
}

/**
 * @brief 변경하고 싶은 데이터를 JSON 형태로 변경해 OS로 전달
 *
 * @param device_name   데이터를 변경할 장치의 이름
 * @param column        데이터를 변경할 컬럼명
 * @param data          변경할 데이터 정보
 */
void HAS2_MQTT::Send(String device_name, String column, String data)
{
    char json_buffer[50] = "";
    StaticJsonDocument<200> root;
    root["MAC"] = my_topic;
    root["DN"] = device_name;
    root[column] = data;

    serializeJson(root, json_buffer);
    Serial.print("Send[OS] : "); Serial.println(json_buffer);
    client.publish("OS", json_buffer);
}

/**
 * @brief 인식된 상황을 JSON 형태로 변경해 OS로 전달
 *
 * @param situation 인식된 상황, 일단 "tag"로 고정
 * @param tag_device_name 태그한 디바이스 이름
 */
void HAS2_MQTT::Situation(String situation, String tag_device_name)
{
    char json_buffer[50] = "";
    StaticJsonDocument<100> root;

    root["MAC"] = my_topic; 
    root["SIT"] = situation;
    root["DN"] = tag_device_name;
    serializeJson(root, json_buffer);
    Serial.print("Send[OS] : "); Serial.println(json_buffer);
    client.publish("OS", json_buffer);
}

/**
 * @brief Topic에 맞게 #define 된 data[]에 input_data 저장
 * 
 * @param topic 전송한 Topic 이름
 * @param input_data 수신한 데이터
 */
void HAS2_MQTT::SaveByTopic(const char* topic, String& input_data)
{
    StaticJsonDocument<1000> doc;
    deserializeJson(doc, input_data);
    if (strcmp(topic,"GLOVE") == 0){
        if (((const char *)doc["DN"])[0] == 'G' && ((const char *)doc["DN"])[2] == 'P'){
            int data_num = ((const char *)doc["DN"])[3] - '0';
            data[data_num] = input_data;
        }
    }
    else{
        data[0] = input_data;
    }
}

/**
 * @brief String을 JSON 형식으로 parsing 하여 원하는 자신의 데이터, 글러브의 데이터 를 가져옴 
 * 
 * @param device_name 장치 이름
 * @param key 원하는 데이터의 column명
 * @return String 해당 KEY의 VALUE를 반환
 */
String HAS2_MQTT::GetData(String device_name, String key)
{
    StaticJsonDocument<200> doc;
    
    if (device_name[0] == 'G' && device_name[2] == 'P'){
        int data_num = device_name[3] - '0';
        device_name = data[data_num];
    }
    else{
        device_name = data[0];
    }

    deserializeJson(doc, device_name);

    if((String)(const char*)doc[key] != NULL){
        String parsing_data = (String)(const char*)doc[key];
        // Serial.print("Get Data : "); Serial.println(parsing_data);
        return parsing_data;
    }
    else{
        //TODO OS로 해당 key의 value 요청하는 코드 필요
        return "-1";
    }    
}

/**
 * @brief 원하는 토픽에 메세지 전송
 *
 * @param topic 보내야 할 토픽
 * @param msg 메세지
 */
void HAS2_MQTT::Publish(String topic, String msg)
{
    Serial.print("Publish : ");
    Serial.print(topic);
    Serial.print(" / msg : ");
    Serial.println(msg);
    client.publish(topic.c_str(), msg.c_str());
}

/**
 * @brief 메세지를 읽기 위해 구독해야할 토픽 / 토픽 추가는 항상 connect 이후에 이루어져야 한다.
 *
 * @param topic 구독해야 할 토픽
 */
void HAS2_MQTT::AddSubscirbe(String topic)
{
    Serial.print("Add Topic : ");
    Serial.println(topic);
    client.subscribe(topic.c_str(), 1);
}

/**
 * @brief 구독한 토픽에서 메세지 읽기
 *
 */
void HAS2_MQTT::ReadSubscirbe()
{
    if (!OTA && wifi_connected)
    {
        if (!client.connected())
        {
            connect();
        }
        client.loop();
    }
}

/**
 * @brief OTA
 *
 * @param device_type 장치의 종류
 * @param ip_address .bin 파일 들어있는 Apache 서버의 주소
 */
void HAS2_MQTT::FirmwareUpdate(String device_type, String ip_address)
{
    WiFiClient client;

    OTA = true;

    httpUpdate.onStart(update_started);
    httpUpdate.onEnd(update_finished);
    httpUpdate.onProgress(update_progress);
    httpUpdate.onError(update_error);

    String bin_file_name = "/" + device_type + ".bin";
    Serial.println(bin_file_name);
    t_httpUpdate_return ret = httpUpdate.update(client, ip_address, 80, bin_file_name);

    switch (ret)
    {
    case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
        break;

    case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        break;

    case HTTP_UPDATE_OK:
        Serial.println("HTTP_UPDATE_OK");
        break;
    }
}

void HAS2_MQTT::update_started()
{
    Serial.println("CALLBACK:  HTTP update process started");
}

void HAS2_MQTT::update_finished()
{
    Serial.println("CALLBACK:  HTTP update process finished");
}

void HAS2_MQTT::update_progress(int cur, int total)
{
    Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", cur, total);
}

void HAS2_MQTT::update_error(int err)
{
    Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
}

String data[9];
