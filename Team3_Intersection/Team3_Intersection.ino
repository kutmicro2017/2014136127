//상하 핀 세팅
#define RED_UD_PIN     10
#define YELLOW_UD_PIN  9
#define GREEN_UD_PIN   8
//좌우 핀 세팅
#define RED_LR_PIN     6
#define YELLOW_LR_PIN  5
#define GREEN_LR_PIN   4
//loop에서 쓰일 기호상수
#define DRIVABLE_DURATION           3000
#define LED_YELLOW_BLINK_DURATION   5000
#define BLINK_TIME                  10

//기능 : duration 동안 pin을 킵니다
void LEDTurnOnInTime(const int pin, const int duration);
//기능 : duration동안 pin을 blinkTime번 점멸시킵니다
void LEDBlink(const int pin, const int duration, const int blinkTime);

void setup()
{
  //상하 핀 모드 설정
  pinMode(RED_UD_PIN, OUTPUT);
  pinMode(YELLOW_UD_PIN, OUTPUT);
  pinMode(GREEN_UD_PIN, OUTPUT);
  //좌우 핀 모드 설정
  pinMode(RED_LR_PIN, OUTPUT);
  pinMode(YELLOW_LR_PIN, OUTPUT);
  pinMode(GREEN_LR_PIN, OUTPUT);
}

void loop()
{
  //좌우 주행 가능
  digitalWrite(RED_UD_PIN, HIGH);
  LEDTurnOnInTime(GREEN_LR_PIN, DRIVABLE_DURATION);
  LEDBlink(YELLOW_LR_PIN, LED_YELLOW_BLINK_DURATION, BLINK_TIME);
  digitalWrite(RED_UD_PIN, LOW);
  //상하 주행 가능
  digitalWrite(GREEN_UD_PIN, HIGH);
  digitalWrite(RED_LR_PIN, HIGH);
  delay(DRIVABLE_DURATION);
  digitalWrite(GREEN_UD_PIN, LOW);
  LEDBlink(YELLOW_UD_PIN, LED_YELLOW_BLINK_DURATION, BLINK_TIME);
  digitalWrite(RED_LR_PIN, LOW);
  /*
  LEDTurnOnInTime(RED_UD_PIN, LED_RED_DURATION);
  LEDBlink(YELLOW_UD_PIN, LED_YELLOW_BLINK_DURATION, BLINK_TIME); 
  LEDTurnOnInTime(GREEN_UD_PIN, LED_GREEN_DURATION);
  */
}

void LEDTurnOnInTime(const int pin, const int duration)
{
  digitalWrite(pin, HIGH);
  delay(duration);
  digitalWrite(pin, LOW);  
}

void LEDBlink(const int pin, const int duration, const int blinkTime)
{
  const int delayTime = duration / (blinkTime + blinkTime);
  
  for (int i = 0; i < blinkTime; ++i)
  {
    digitalWrite(pin, HIGH);
    delay(delayTime);
    digitalWrite(pin, LOW);
    delay(delayTime);
  }
}

