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
    Serial.print("Message arrived[");
    Serial.print(topic);
    Serial.print("] : ");
    for (int i = 0; i < length; i++)
    {
        input_data += (char)payload[i];
    }
    Serial.println(input_data);

    has2_mqtt.SaveByTopic(topic, input_data);
    // ==================== 여기까지 기본틀 복사해서 사용 ============================
    // 원하는 데이터를 가지고 오고 싶을때 사용
    // 기본이 String이여서 int 형으로 사용하고 싶으면 toInt() 함수 사용
    Serial.println(has2_mqtt.GetData(glove8, "BP").toInt());

    // 태그 완료시 (07.19일 기준 : 모든 장치 시나리오 상황 시 [상황완료 = tag]로 보내는것으로 합의)
    has2_mqtt.Situation("tag", "G1P1");
}

void setup()
{
    Serial.begin(115200);
    has2_mqtt.Setup("tp-link", "Code3824@", callback);
    String output = "";
}

void loop()
{
    has2_mqtt.ReadSubscirbe();
}