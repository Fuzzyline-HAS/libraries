#include "HAS2_Wifi.h"

void JsonParsing(String json_s);

HAS2_Wifi has2wifi;

iotglove my;
iotglove tag;

void setup()
{
    Serial.begin(115200);
    has2wifi.Setup("iotglove");
}

void loop()
{
    has2wifi.Loop();
    delay(2000);
}