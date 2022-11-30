#include <HAS2_Vibration.h>

#define VIBRATION_MOTOR_PIN1 4
#define VIBRATION_MOTOR_PIN2 32
#define VIBRATION_MOTOR_PIN3 22

// VibrationMotor motor1(VIBRATION_MOTOR_PIN1, 1);
//VibrationMotor motor2(VIBRATION_MOTOR_PIN2, 2);
VibrationMotor motor3(VIBRATION_MOTOR_PIN3, 3);

void setup(){
    Serial.begin(115200);
    pinMode(VIBRATION_MOTOR_PIN1,OUTPUT);
    pinMode(VIBRATION_MOTOR_PIN2,OUTPUT);
    // motor2.Setup();
    motor3.Setup();
}

void loop(){
    digitalWrite(VIBRATION_MOTOR_PIN1,LOW);
    digitalWrite(VIBRATION_MOTOR_PIN2,HIGH);
    motor3.Control(vibration_pattern_2);
    // motor3.On();
}