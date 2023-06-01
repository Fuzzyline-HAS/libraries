#include <HAS2_MQTT.h>

HAS2_MQTT has2_mqtt;

bool OTA = false;

/**
 * @brief 장치에 맞게 각자 코드에 만들어야 하는 함수 / callback 함수여서 topic, payload, length 적어놓기만 하면 됌
 * 
 * @param topic 콜백함수 자료형 맞추기
 * @param payload 콜백함수 자료형 맞추기
 * @param length 콜백함수 자료형 맞추기
 */
void callback(char* topic, byte* payload, unsigned int length) 
{
    static bool start = false;
    if(!start){
        start = true;
        has2_mqtt.Publish(my_topic, "start");
        return ;
    }
    String input_data = "";
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] : ");
    for (int i = 0; i < length; i++) {
        input_data += (char)payload[i];
    }
    Serial.println(input_data);

    if(input_data == "OTA"){
        has2_mqtt.FirmwareUpdate("iotglove");
        OTA = true;
    }
}

void setup()
{
    Serial.begin(115200);
    has2_mqtt.Setup("KT_GiGA_6C64","ed46zx1198", callback);
}

void loop()
{
    if(!OTA){
        has2_mqtt.ReadSubscirbe();
    }
}