#include <HAS2_Vibration.h>

#define VIBRATION_MOTOR_PIN1 14
#define VIBRATION_MOTOR_PIN2 12
#define VIBRATION_MOTOR_PIN3 13

VibrationMotor motor1(VIBRATION_MOTOR_PIN1, 1);
VibrationMotor motor2(VIBRATION_MOTOR_PIN2, 2);
// VibrationMotor motor3(VIBRATION_MOTOR_PIN3, 3);

void setup(){
    Serial.begin(115200);
    motor1.Setup();
    motor2.Setup();
    pinMode(VIBRATION_MOTOR_PIN3, OUTPUT);
}

void loop(){
    motor1.On();
    motor2.On();
    digitalWrite(VIBRATION_MOTOR_PIN3, HIGH);
    // motor1.Control(vibration_pattern_3);
    // motor2.Control(vibration_pattern_3);
    // motor3.Control(vibration_pattern_3);
}