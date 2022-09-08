#include <Arduino.h>
#line 1 "c:\\Users\\Fuzzy line Studio\\Documents\\Arduino\\libraries\\HAS2_Wifi\\examples\\simple_wifi\\simple_wifi.ino"
#include "HAS2_Wifi.h"

void JsonParsing(String json_s);

HAS2_Wifi has2wifi;

iotglove my;
iotglove tag;

#line 10 "c:\\Users\\Fuzzy line Studio\\Documents\\Arduino\\libraries\\HAS2_Wifi\\examples\\simple_wifi\\simple_wifi.ino"
void setup();
#line 16 "c:\\Users\\Fuzzy line Studio\\Documents\\Arduino\\libraries\\HAS2_Wifi\\examples\\simple_wifi\\simple_wifi.ino"
void loop();
#line 10 "c:\\Users\\Fuzzy line Studio\\Documents\\Arduino\\libraries\\HAS2_Wifi\\examples\\simple_wifi\\simple_wifi.ino"
void setup()
{
    Serial.begin(115200);
    JsonParsing(has2wifi.Setup("iotglove"));
}

void loop()
{
    JsonParsing(has2wifi.Loop());
    delay(2000);
}

void JsonParsing(String json_s)
{
    StaticJsonDocument<500> doc;

    auto error = deserializeJson(doc, json_s);

    if (error)
    {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
    }
    String device_name = (const char*)doc["DeviceName"];
    if(device_name == has2wifi.device_name){
        my.device_name = (const char *)doc["DeviceName"];
        my.role = (const char *)doc["Role"];
        my.life_chip = doc["LifeChip"];
        my.taken_chip = doc["TakenChip"];
        my.max_life_chip = doc["MaxLifeChip"];
        my.battery_pack = doc["BatteryPack"];
        my.max_battery_pack = doc["MaxBatteryPack"];
        my.shift_machine = doc["ShiftMachine"];
    }
    else if((device_name != has2wifi.device_name) && (device_name != NULL)){
        tag.device_name = (const char *)doc["DeviceName"];
    }
    else if(device_name == has2wifi.my_mac){
        my.shift_machine = doc["ShiftMachine"];
        Serial.println(my.shift_machine);
    }
}
