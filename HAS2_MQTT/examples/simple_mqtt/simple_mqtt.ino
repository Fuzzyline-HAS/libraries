/**
 * @file simple_mqtt.ino
 * @author Kim YuBin (dbqks56231106@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <HAS2_MQTT.h>

HAS2_MQTT has2_mqtt;

/**
 * @brief 장치에 맞게 각자 코드에 만들어야 하는 함수 / 기본틀이니 그대로 복사해서 자신의 코드에 붙여넣기 해서 사용하면 됌
 * 
 * @param topic 콜백함수 자료형 맞추기
 * @param payload 콜백함수 자료형 맞추기
 * @param length 콜백함수 자료형 맞추기
 */
void callback(char *topic, byte *payload, unsigned int length)
{
    // 함수 설명은 라이브러리 참고
    String input_data = "";
    // Message arrived[topic] : 
    Serial.print("Message arrived[");Serial.print(topic);Serial.print("] : ");
    for (int i = 0; i < length; i++)
    {
        input_data += (char)payload[i];
    }
    Serial.println(input_data);
    has2_mqtt.JsonParsing(input_data);
}

void setup()
{
    Serial.begin(115200);
    has2_mqtt.Setup("KT_GiGA_6C64","ed46zx1198", callback);
}

void loop()
{
    has2_mqtt.ReadSubscirbe();
}