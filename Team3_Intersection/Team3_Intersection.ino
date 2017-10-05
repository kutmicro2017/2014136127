//상하 출력 핀 세팅
#define RED_UD_PIN     23
#define YELLOW_UD_PIN  25
#define GREEN_UD_PIN   27
//좌우 출력 핀 세팅
#define RED_LR_PIN     35
#define YELLOW_LR_PIN  37
#define GREEN_LR_PIN   39
//입력 핀 세팅
#define WALKER_UD_BUTTON 20
#define WALKER_LR_BUTTON 21
//기타 기호상수
#define DRIVABLE_DURATION           20000   //주행 가능 시간, 녹색등 유지시간(20sec)
#define LED_YELLOW_BLINK_DURATION   5000    //경고등 점멸 시간(5sec)
#define BLINK_TIME                  5       //점멸 횟수
#define TRAFFIC_LIGHT_IDLE_TIME     3000    //입력 받았을 시 대기 시간(3sec)

//기능 : 주행할 수 있게 신호를 조정합니다.
void Drive(const int red, const int green, const int yellow, const int otherRed);
//기능 : duration 동안 pin을 킵니다
void TurnOnLEDWithinTime(const int pin, const int duration);
//기능 : duration동안 pin을 blinkTime번 점멸시킵니다
void BlinkLED(const int pin, const int duration, const int blinkTime);
//기능 : 보행자가 건널 수 있게 신호등을 조정합니다.
void AdjustTrafficLight();
//기능 : AdjustTrafficLight() 보조 함수
void doAdjust(const int red, const int green, const int yellow);
//기능 : duration동안 보행자 버튼으로부터 신호를 받습니다.
void Polling(const int duration);


void setup()
{
  //상하 출력 핀 모드 설정
  pinMode(RED_UD_PIN, OUTPUT);
  pinMode(YELLOW_UD_PIN, OUTPUT);
  pinMode(GREEN_UD_PIN, OUTPUT);
  //좌우 출력 핀 모드 설정
  pinMode(RED_LR_PIN, OUTPUT);
  pinMode(YELLOW_LR_PIN, OUTPUT);
  pinMode(GREEN_LR_PIN, OUTPUT);
  //입력 핀 모드 설정
  pinMode(WALKER_UD_BUTTON, INPUT_PULLUP);
  pinMode(WALKER_LR_BUTTON, INPUT_PULLUP);
}

void loop()
{
  //상하 주행
  Drive(RED_UD_PIN, GREEN_UD_PIN, YELLOW_UD_PIN, RED_LR_PIN);
  //좌우 주행
  Drive(RED_LR_PIN, GREEN_LR_PIN, YELLOW_LR_PIN, RED_UD_PIN);
}

void TurnOnLEDWithinTime(const int pin, const int duration)
{
  digitalWrite(pin, HIGH);
  Polling(duration);
  digitalWrite(pin, LOW);  
}

void BlinkLED(const int pin, const int duration, const int blinkTime)
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

void AdjustTrafficLight()
{
  if (digitalRead(WALKER_UD_BUTTON) == LOW && digitalRead(GREEN_UD_PIN) == HIGH)
  {
    doAdjust(RED_UD_PIN, GREEN_UD_PIN, YELLOW_UD_PIN);
  }
  else if (digitalRead(WALKER_LR_BUTTON) == LOW && digitalRead(GREEN_LR_PIN) == HIGH)
  {
    doAdjust(RED_LR_PIN, GREEN_LR_PIN, YELLOW_LR_PIN);
  }
}

void doAdjust(const int red, const int green, const int yellow)
{
  delay(TRAFFIC_LIGHT_IDLE_TIME);
  digitalWrite(green, LOW);
  BlinkLED(yellow, LED_YELLOW_BLINK_DURATION, BLINK_TIME);
  digitalWrite(red, HIGH);
}

void Polling(const int duration)
{
  int durationTime = duration / 1000;

  for (int i = 0; i < 1000; ++i)
  {
    AdjustTrafficLight();
    delay(durationTime);
  }
}

void Drive(const int red, const int green, const int yellow, const int otherRed)
{
  digitalWrite(otherRed, HIGH);
  TurnOnLEDWithinTime(green, DRIVABLE_DURATION);
  //보행자 신호가 들어오지 않았을 때
  if (digitalRead(red) == LOW)
  {
    BlinkLED(yellow, LED_YELLOW_BLINK_DURATION, BLINK_TIME);
  }
  digitalWrite(otherRed, LOW);
}

