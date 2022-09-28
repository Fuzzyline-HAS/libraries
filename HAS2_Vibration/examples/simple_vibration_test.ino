#include <HAS2_Vibration.h>

VibrationMotor motor1(14, 1);

void setup(){
    Serial.begin(115200);
    motor1.Set();
}

void loop(){
    motor1.Control(vibration_pattern_4);
}