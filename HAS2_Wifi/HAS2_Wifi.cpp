/**
 * @file HAS2_Wifi.cpp
 * @author 김유빈
 * @brief
 * @version 1.0
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "HAS2_Wifi.h"
#include "Arduino.h"

/**
 * @brief HAS2_Wifi 기본생성자
 *
 */
HAS2_Wifi::HAS2_Wifi()
    : HOST_NAME("http://172.30.1.44"),
      PHP_FILE_NAME("/has2.php"),
      server(HOST_NAME + PHP_FILE_NAME)
{
}

/**
 * @brief HAS2_Wifi PHP 변경 생성자
 *
 * @param php 원하는 PHP 파일 입력["/test.php"]형식
 */
HAS2_Wifi::HAS2_Wifi(String php)
    : HOST_NAME("http://172.30.1.44"),
      PHP_FILE_NAME(php),
      server(HOST_NAME + PHP_FILE_NAME)
{
}

/**
 * @brief HAS2_Wifi PHP 변경 생성자
 *
 * @param host 로컬호스트 주소 입력["http://172.30.1.59"]형식
 * @param php 원하는 PHP 파일 입력["/test.php"]형식
 */
HAS2_Wifi::HAS2_Wifi(String host, String php)
    : HOST_NAME(host),
      PHP_FILE_NAME(php),
      server(HOST_NAME + PHP_FILE_NAME)
{
}

/**
 * @brief Wifi 연결 및 초기설정
 *
 */
void HAS2_Wifi::Setup()
{
  WiFi.begin(ssid, password);
  Serial.println("Connecting....");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WiFi connected");
  }
  else
  {
    Serial.println("WiFi not connected");
  }
  delay(1000);

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  my_mac = WiFi.macAddress();
  Serial.print("MY MAC=");
  Serial.println(my_mac);

  ReceiveMine();

  Serial.print("DeviceName : ");
  Serial.println((const char *)my["device_name"]);
}

/**
 * @brief 다른 장치의 데이터를 읽음
 *
 * @param device_name 다른 장치의 이름
 */
void HAS2_Wifi::Receive(String device_name)
{
  String string_request = server + "?request=" + "Receive" + "&table=" + "device" + "&key=" + device_name;
  HttpRequest("Receive", string_request);
}

/**
 * @brief [메인 프로그램 전용] mp3재생 장치의 데이터를 읽음
 *
 * @param device_name 장치의 이름
 * @param value mp3 재생 순서
 */
void HAS2_Wifi::ReceiveMP3(String device_name, int value)
{
  String string_request = server + "?request=" + "ReceiveMP3" + "&table=" + "device" + "&key=" + device_name + "&value=" + value;
  HttpRequest("Receive", string_request);
}

/**
 * @brief 원하는 장치의 데이터를 수정
 *
 * @param device_name 데이터 변경을 당하는 장치의 이름
 * @param column 변경할 데이터의 컬럼
 * @param value 변경할 데이터의 값
 */
void HAS2_Wifi::Send(String device_name, String column, String value)
{
  String string_request = server + "?request=" + "Send" + "&table=" + "device" + "&key=" + device_name + "&column=" + column + "&value=" + value;
  HttpRequest("Send", string_request);
}

/**
 * @brief 자신의 데이터를 읽음
 *
 */
void HAS2_Wifi::ReceiveMine()
{
  String string_request = server + "?request=" + "ReceiveMine" + "&table=" + "device" + "&mac=" + my_mac;
  HttpRequest("ReceiveMine", string_request);
}

void HAS2_Wifi::Loop()
{
  String string_request = server + "?request=" + "Loop" + "&table=" + "device" + "&mac=" + my_mac;
  HttpRequest("Loop", string_request);
  if ((int)shift_machine["shift_machine"] >= 1)
  {
    ReceiveMine();
  }
}
/**
 * @brief 반복적으로 ShfitMachin의 데이터를 읽음
 *
 */
void HAS2_Wifi::Loop(void(*Func)(void))
{
  String string_request = server + "?request=" + "Loop" + "&table=" + "device" + "&mac=" + my_mac;
  HttpRequest("Loop", string_request);
  if ((int)shift_machine["shift_machine"] >= 1)
  {
    ReceiveMine();
    Func();
  }
}

/**
 * @brief [private] Http 통신
 *
 * @param request 원하는 명령
 * @param string_request Http에게 보내는 형식 문자열
 */
void HAS2_Wifi::HttpRequest(String request, String string_request)
{

  http.begin(string_request); //요청을 PHP로 전송

  int httpcode = http.GET();

  if (httpcode > 0)
  {
    if (httpcode == HTTP_CODE_OK)
    {
      String payload = http.getString();
      if(request != "Loop")Serial.println(payload);
      if (request != "Send")
        JsonParsing(request, payload);
    }
    else
    {
      Serial.printf("HTTP GET... code: %d\n", httpcode);
    }
  }
  else
  {
    Serial.printf("HTTP GET... failed, error: %s\n", http.errorToString(httpcode).c_str());
  }
  http.end();
}

/**
 * @brief [private] Json 디코딩하여 원하는 데이터를 읽어옴
 *
 * @param request 원하는 명령
 * @param json String 형식의 json 파일
 */
void HAS2_Wifi::JsonParsing(String request, String json)
{
  if(request == "Loop"){
    auto error = deserializeJson(shift_machine, json);
    if (error) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(error.c_str());
    }
  }
  else if(request == "ReceiveMine"){
    auto error = deserializeJson(my, json);
    if (error) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(error.c_str());
    }
  }
  else if(request == "Receive"){
    auto error = deserializeJson(tag, json);
    if (error) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(error.c_str());
    }
  }
}

HTTPClient http;
StaticJsonDocument<100> shift_machine;
StaticJsonDocument<1000> my;
StaticJsonDocument<1000> tag;
StaticJsonDocument<500> skill;