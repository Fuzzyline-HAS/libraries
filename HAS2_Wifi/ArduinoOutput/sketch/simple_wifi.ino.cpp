#include <Arduino.h>
#line 1 "C:\\Users\\teamh\\OneDrive\\문서\\Arduino\\libraries\\HAS2_Wifi\\examples\\simple_wifi\\simple_wifi.ino"
#include "HAS2_Wifi.h"

HAS2_Wifi has2wifi;

#line 5 "C:\\Users\\teamh\\OneDrive\\문서\\Arduino\\libraries\\HAS2_Wifi\\examples\\simple_wifi\\simple_wifi.ino"
void setup();
#line 11 "C:\\Users\\teamh\\OneDrive\\문서\\Arduino\\libraries\\HAS2_Wifi\\examples\\simple_wifi\\simple_wifi.ino"
void loop();
#line 5 "C:\\Users\\teamh\\OneDrive\\문서\\Arduino\\libraries\\HAS2_Wifi\\examples\\simple_wifi\\simple_wifi.ino"
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
