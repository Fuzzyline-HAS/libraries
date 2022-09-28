# 1 "c:\\Users\\Fuzzy line Studio\\Documents\\Arduino\\libraries\\HAS2_Wifi\\examples\\simple_wifi\\simple_wifi.ino"
# 2 "c:\\Users\\Fuzzy line Studio\\Documents\\Arduino\\libraries\\HAS2_Wifi\\examples\\simple_wifi\\simple_wifi.ino" 2

HAS2_Wifi has2wifi;

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
