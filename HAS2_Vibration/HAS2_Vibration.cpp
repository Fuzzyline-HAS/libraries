#include "HAS2_Vibration.h"
#include "Arduino.h"

/**
 * @brief                   진동모터 클래스 생성자
 * 
 * @param motor_pin         진동모터 핀번호
 * @param motor_number      [ESP32 전용] 진동모터 PWM 채널 번호 (1 ~ 9 임의로 선택)
 */
VibrationMotor::VibrationMotor(int motor_pin,int motor_number)
:   vibration_motor_pin(motor_pin),
    vibration_motor_number(motor_number),
    repeat(0),
    tempo_complete(false)
{
}

void VibrationMotor::Setup()
{
    ledcSetup(vibration_motor_number, freq, resolution);
    ledcAttachPin(vibration_motor_pin, vibration_motor_number);
    ledcWrite(vibration_motor_number, 0);
}

/**
 * @brief 진동모터의 세기를 1 ~ 5 사이로 정의
 * 
 * @param intensity 정수 1 ~ 5 를 인자로 받는다.
 * @return int 
 */
int VibrationMotor::Intensity(int intensity)
{
  switch(intensity){
      case 0 :
        return 0;
        break; 
      case 1 :
        return vibration_mode1;
        break;
      case 2 :
        return vibration_mode2;
        break;
      case 3 :
        return vibration_mode3;
        break;
      case 4 :
        return vibration_mode4;
        break;
      case 5 :
        return vibration_mode5;
        break;
      default :
        break;
    }
}

/**
 * @brief 정해진 패턴을 통해 진동모터 동작
 * 
 * @param vibration_pattern 헤더파일에 정의된 패턴 (vibration_pattern_1 ~ vibration_pattern_4)
 * @param tempo 진동세기 변경 간 딜레이 조절 [defalte = 0]
 */
void VibrationMotor::Control(const byte* vibration_pattern, int tempo)
{
  uint8_t pattern_index = ARRAYINDEX(vibration_pattern);
  Serial.println(pattern_index);
  // if(!tempo_complete){ delay(40*tempo); } // 진동이 진동모터 1,2,3순으로 올라가는 느낌을 주기 위해
  if(repeat < 12 - 1){repeat++;} else{repeat = 0;} // 진동 패턴 인덱스를 한칸씩 증가 시킴
  Serial.print("repeat : "); Serial.println(repeat);
  Serial.print("repeat[] : "); Serial.println(vibration_pattern[repeat]);
  ledcWrite(vibration_motor_number, Intensity(vibration_pattern[repeat]));
  delay(30);
}

void VibrationMotor::On()
{
  tempo_complete = false;
  static int i = 10;
  i = i + 40;
  ledcWrite(vibration_motor_number, i);
  delay(1500);
  if(i > 240) {i = 10;}
}

void VibrationMotor::Off()
{
  tempo_complete = false;
  ledcWrite(vibration_motor_number, 0);
}

