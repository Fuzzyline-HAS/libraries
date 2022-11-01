# 1 "c:\\Users\\admin\\Documents\\Arduino\\libraries\\HAS2_Wifi\\examples\\simple_wifi\\simple_wifi.ino"
# 2 "c:\\Users\\admin\\Documents\\Arduino\\libraries\\HAS2_Wifi\\examples\\simple_wifi\\simple_wifi.ino" 2

HAS2_Wifi has2wifi;

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
