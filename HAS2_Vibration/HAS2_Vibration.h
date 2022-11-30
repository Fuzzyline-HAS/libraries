#ifndef HAS2_VIBRATION_H
#define HAS2_VIBRATION_H

#include "Arduino.h"

#define ARRAYINDEX(X) sizeof(X) / sizeof(byte)

#define vibration_mode0   0
#define vibration_mode1   50
#define vibration_mode2   100
#define vibration_mode3   150
#define vibration_mode4   200
#define vibration_mode5   250

const int freq = 5000;
const int resolution = 8;

const byte vibration_pattern_1[] = {1,0,0,1,5,2,0,0,0,1,2,1,0,0,0,0,0,0};   // BPM 83
const byte vibration_pattern_2[] = {1,0,1,5,3,0,0,1,2,1,0,0};               // BPM 125
const byte vibration_pattern_3[] = {5,5,5,5,5,5,5};
const byte vibration_pattern_4[] = {1,2,1,0,0,1,5,2,1,0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // BPM 56

class VibrationMotor{
  private :
    int vibration_motor_pin;
    int vibration_motor_number;
    int repeat;
    bool tempo_complete;

    int Intensity(int intensity);
    
  public :
    VibrationMotor(int motor_pin,int motor_number);
    void Setup();
    void Control(const byte vibration_pattern[], int tempo = 0); 
    void On();
    void Off();
};



#endif // HAS2_VIBRATION_H
