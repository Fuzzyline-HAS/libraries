#include <Arduino.h>
#line 1 "c:\\Users\\Fuzzy line Studio\\Documents\\Arduino\\libraries\\HAS2_Wifi\\examples\\simple_wifi\\simple_wifi.ino"
#include "HAS2_Wifi.h"

HAS2_Wifi has2wifi;

#line 5 "c:\\Users\\Fuzzy line Studio\\Documents\\Arduino\\libraries\\HAS2_Wifi\\examples\\simple_wifi\\simple_wifi.ino"
void setup();
#line 11 "c:\\Users\\Fuzzy line Studio\\Documents\\Arduino\\libraries\\HAS2_Wifi\\examples\\simple_wifi\\simple_wifi.ino"
void loop();
#line 5 "c:\\Users\\Fuzzy line Studio\\Documents\\Arduino\\libraries\\HAS2_Wifi\\examples\\simple_wifi\\simple_wifi.ino"
void setup()
{
    Serial.begin(115200);
    has2wifi.Setup("iotglove");
}

void loop()
{
    has2wifi.Loop();
    Serial.print("DeviceName : "); Serial.println((const char*)my["DeviceName"]);
    Serial.print("LifeChip : "); Serial.println((int)my["LifeChip"]);
    Serial.println();
    delay(2000);
}
