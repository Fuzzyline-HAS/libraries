#include <SPI.h>
#include <Esp.h>

#include <Arduino.h>

#include <Nextion.h>

HardwareSerial MySerial2(2);

NexAudio wav0 = NexAudio(0, 3, "wav0");
NexNumber n0 = NexNumber(0, 4, "n0");

uint32_t num = 0;

void setup()
{
    Serial.begin(115200);
    nexInit();
    MySerial2.begin(9600,SERIAL_8N1, 39, 33);
    dbSerialPrintln("setup done");
}

void loop()
{
    n0.setValue(++num);
    wav0.setEn(1);
    Serial.println("Hello World!");

    delay(3000);
}


