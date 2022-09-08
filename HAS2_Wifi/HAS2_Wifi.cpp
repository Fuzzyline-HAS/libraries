#include "HAS2_Wifi.h"
#include "Arduino.h"

HAS2_Wifi::HAS2_Wifi()
: HOST_NAME("http://172.30.1.59"),
  PHP_FILE_NAME("/base.php"),
  server(HOST_NAME + PHP_FILE_NAME)
{
}

HAS2_Wifi::HAS2_Wifi(String php) 
: HOST_NAME("http://172.30.1.59"),
  PHP_FILE_NAME(php),
  server(HOST_NAME + PHP_FILE_NAME)
{
}

/**
 * @brief Wifi 연결 및 초기설정
 *
 * @param type 장치의 종류 => itembox, iotglove 등 *소문자*로 작성
 */
void HAS2_Wifi::Setup(String type)
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

  device_type = type;
  ReceiveMine(my_mac);
}

void HAS2_Wifi::Receive(String device_name)
{
  String string_request = server + "?request=" + "Receive" + "&key=" + device_name;
  HttpRequest(string_request);
}

void HAS2_Wifi::Send(String device_name, String column, String value)
{
  String string_request = server + "?request=" + "Send" + "&key=" + device_name + "&column=" + column + "&value=" + value;
  HttpRequest(string_request);
}

void HAS2_Wifi::ReceiveMine(String mac_add)
{
  String string_request = server + "?request=" + "ReceiveMine" + "&table=" + device_type + "&MAC=" + my_mac;
  HttpRequest(string_request);
}

void HAS2_Wifi::Loop()
{
  String string_request = server + "?request=" + "Loop" + "&table=" + device_type + "&mac=" + my_mac;
  HttpRequest(string_request);
}

void HAS2_Wifi::HttpRequest(String string_request)
{

  http.begin(string_request); //요청을 PHP로 전송

  int httpcode = http.GET();

  if (httpcode > 0){
    if (httpcode == HTTP_CODE_OK){
      String payload = http.getString();
      Serial.println(payload);
    }
    else{
      Serial.printf("HTTP GET... code: %d\n", httpcode);
    }
  }
  else{
    Serial.printf("HTTP GET... failed, error: %s\n", http.errorToString(httpcode).c_str());
  }
  http.end();
}

HTTPClient http;