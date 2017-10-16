//상하 출력 핀 세팅
#define RED_UD_PIN     48
#define YELLOW_UD_PIN  46
#define GREEN_UD_PIN   44

//좌우 출력 핀 세팅
#define RED_LR_PIN     49
#define YELLOW_LR_PIN  47
#define GREEN_LR_PIN   45

//입력 핀 세팅
#define WALKER_UD_BUTTON 43
//#define WALKER_LR_BUTTON 42

//상단 신호 출력용 매트릭스 핀 번호 배열
int gUpperPinRow[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
int gUpperPinCol[] = { 10, 11, 12, 13, 14, 15, 16, 17 };
//하단 신호 출력용 매트릭스 핀 번호 배열
int gLowerPinRow[] = { 22, 24, 26, 28, 30, 32, 34, 36 };
int gLowerPinCol[] = { 23, 25, 27, 29, 31, 33, 35, 37 };

//기타 기호상수
#define DRIVABLE_DURATION           10000                                   //주행 가능 시간, 녹색등 유지시간(20sec)
#define LED_YELLOW_BLINK_DURATION   5000                                    //경고등 점멸 시간(5sec)
#define BLINK_TIME                  LED_YELLOW_BLINK_DURATION / 1000        //점멸 횟수
#define TRAFFIC_LIGHT_IDLE_TIME     3000    //입력 받았을 시 대기 시간(3sec)
#define ARRAY_LENGTH                8
#define STOP_TIME                   15

//DotMatrix 타이머 출력을 위한 변수
int gNumbers[10][8][4] =
{
  // ZERO
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  // ONE
  {
    { 0, 0, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 1, 1, 1, 1 }
  },
  // TWO
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 1, 0 },
    { 0, 1, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 1 }
  },
  // THREE
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  // FOUR
  {
    { 0, 0, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 0, 1, 0 },
    { 1, 1, 1, 1 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 0 }
  },
  // FIVE
  {
    { 1, 1, 1, 1 },
    { 1, 0, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 1, 1, 1, 1 }
  },
  // SIX
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 0 },
    { 1, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  // SEVEN
  {
    { 1, 1, 1, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 1, 0 },
    { 0, 1, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 1, 0, 0 }
  },
  // EIGHT
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 },
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  },
  // NINE
  {
    { 0, 1, 1, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 1 },
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 1, 0 }
  }
};
//DotMatrix 보행자 그림 출력을 위한 변수
int gWalkerSigns[2][8][8] =
{
  // RED : CANNOT CROSS
  {
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 0, 0 },
    { 0, 1, 0, 1, 1, 0, 1, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 }
  },
  // GREEN : CAN CROSS
  {
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 1, 1, 1, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 1, 0 },
    { 0, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 }
  }
};

/*
//기능 : duration 동안 pin을 킵니다
void TurnOnLEDWithinTime(int pin, int duration);
//기능 : duration동안 pin을 blinkTime번 점멸시킵니다
void BlinkLED(int pin, int duration, int blinkTime);
//기능 : 보행자가 건널 수 있게 신호등을 조정합니다.
void AdjustTrafficLight();
*/
//기능 : AdjustTrafficLight() 보조 함수
void doAdjustTrafficLight(int red, int green, int yellow);
/*
//기능 : duration동안 보행자 버튼으로부터 신호를 받습니다.
void Polling(const int duration);
*/

//기능 : 상단의 DotMatrix 신호를 지웁니다.
void ClearUpper();
//기능 : 하단의 DotMatrix 신호를 지웁니다.
void ClearLower();
//기능 : former, later순으로 DotMatrix에 숫자를 출력합니다.
void DisplayNumber(int former[][4], int later[][4]);
//기능 : 상단 DotMatrix에 정지 신호를 출력합니다.
void DisplayStopSign();
//기능 : 하단 DotMatrix에 보행 신호를 출력합니다.
void DisplayWalkSign();
//기능 : duration 동안 타이머를 출력합니다.
void DisplayTimer(int duration);
//기능 : duration 동안 타이머를 출력하면서 대기합니다.
void PrintAndDelay(int duration, int former, int later);
//기능 : duration 동안 타이머를 출력하면서 폴링을 받습니다.
void PrintAndDelayWithPolling(int duration, int former, int later);

/*
//기능 : duration 동안 pin을 킵니다
void TurnOnLEDWithinTime(int pin, int duration);
*/
//기능 : duration동안 pin을 blinkTime번 점멸시킵니다
void BlinkLEDForUD(int duration, int blinkTime);
//기능 : 신호를 바꿉니다
void AdjustTrafficLightForUD();

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
  //DotMatrix 핀 모드 설정 및 초기화
  for(int i = 0; i < ARRAY_LENGTH; ++i)
  {
    pinMode(gUpperPinRow[i], OUTPUT);
    pinMode(gUpperPinCol[i], OUTPUT);
    pinMode(gLowerPinRow[i], OUTPUT);
    pinMode(gLowerPinCol[i], OUTPUT);

    digitalWrite(gUpperPinRow[i], LOW);
    digitalWrite(gUpperPinCol[i], HIGH);
    digitalWrite(gLowerPinRow[i], LOW);
    digitalWrite(gLowerPinCol[i], HIGH);
  }
}

void loop()
{
  //상하 주행
  digitalWrite(RED_LR_PIN, HIGH);
  digitalWrite(GREEN_UD_PIN, HIGH);
  for (int t = STOP_TIME; t >= 0; --t)
  {
     int former = t / 10;
     int later = t % 10;
     if (t > BLINK_TIME)
     {
        PrintAndDelay(1000, former, later);
     }
     else
     {
       digitalWrite(GREEN_UD_PIN, LOW);
       BlinkLEDForUD(former, later);
     }
  }
  digitalWrite(RED_UD_PIN, HIGH);
}
/*
void TurnOnLEDWithinTime(const int pin, const int duration)
{
  digitalWrite(pin, HIGH);
  Polling(duration);
  digitalWrite(pin, LOW);  
}
*/
void BlinkLED(int pin, int duration, int blinkTime)
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
/*
void AdjustTrafficLight()
{
  if (digitalRead(WALKER_UD_BUTTON) == LOW && digitalRead(GREEN_UD_PIN) == HIGH)
  {
    doAdjustTrafficLight(RED_UD_PIN, GREEN_UD_PIN, YELLOW_UD_PIN);
  }
  else if (digitalRead(WALKER_LR_BUTTON) == LOW && digitalRead(GREEN_LR_PIN) == HIGH)
  {
    doAdjustTrafficLight(RED_LR_PIN, GREEN_LR_PIN, YELLOW_LR_PIN);
  }
}
*/
void doAdjustTrafficLight(int red, int green, int yellow)
{
  delay(TRAFFIC_LIGHT_IDLE_TIME);
  digitalWrite(green, LOW);
  BlinkLED(yellow, LED_YELLOW_BLINK_DURATION, BLINK_TIME);
  digitalWrite(red, HIGH);
}
/*
void Polling(const int duration)
{
  int durationTime = duration / 1000;

  for (int i = 0; i < 1000; ++i)
  {
    AdjustTrafficLight();
    delay(durationTime);
  }
}
*/
void DisplayNumber(int former[][4], int later[][4])
{
  for(int r = 0; r < 8; ++r)
  {
    ClearLower();
    digitalWrite(gLowerPinRow[r], HIGH);
    //십의 자리 출력
    for(int c = 0; c < 4; ++c)
    {
      if (former[r][c])
      {
        digitalWrite(gLowerPinCol[c], LOW);
      }
    }
    //일의 자리 출력
    for(int c = 0; c < 4; ++c)
    {
      if (later[r][c])
      {
        digitalWrite(gLowerPinCol[c + 4], LOW);
      }
    }
    //HACK : 이 함수가 없을 시, 출력 신호가 뚜렷하게 보이지 않음
    delay(1);
  }
}

void DisplayStopSign()
{
  for(int r = 0; r < 8; ++r)
  {
    ClearUpper();
    digitalWrite(gUpperPinRow[r], HIGH);
    for(int c = 0; c < 8; ++c)
    {
      if(gWalkerSigns[0][r][c] == 1)
      {
        digitalWrite(gUpperPinCol[c], LOW);
      }
    }
    //HACK : 출력 신호를 유지하기 위해 사용
    delay(1);
  }
}

void DisplayWalkSign()
{
  for(int r = 0; r < 8; ++r)
  {
    ClearLower();
    digitalWrite(gLowerPinRow[r], HIGH);
    for(int c = 0; c < 8; ++c)
    {
      if(gWalkerSigns[1][r][c])
      {
        digitalWrite(gLowerPinCol[c], LOW);
      }
    }
    //HACK : 출력 신호를 유지하기 위해 사용
    delay(1);
  }
}

void ClearUpper()
{
  for (int i = 0; i < ARRAY_LENGTH; ++i)
  {
    digitalWrite(gUpperPinRow[i], LOW);
    digitalWrite(gUpperPinCol[i], HIGH);
  }
}

void ClearLower()
{
  for (int i = 0; i < ARRAY_LENGTH; ++i)
  {
    digitalWrite(gLowerPinRow[i], LOW);
    digitalWrite(gLowerPinCol[i], HIGH);
  }
}

void DisplayTimer(int duration)
{
  unsigned timeStart;
  unsigned timeEnd;
  for (int t = duration; t >= 0; --t)
  {
    int former = t / 10;
    int later = t % 10;
    timeStart = timeEnd = millis();
    while (timeEnd - timeStart <= 1000)
    {
      DisplayStopSign();
      DisplayNumber(gNumbers[former], gNumbers[later]);
      timeEnd = millis();  
    }
  }
}

void PrintAndDelayWithPolling(int duration, int former, int later)
{
  unsigned timeStart;
  unsigned timeEnd;
  timeStart = timeEnd = millis();
  while (timeEnd - timeStart <= duration)
  {
    DisplayStopSign();
    DisplayNumber(gNumbers[former], gNumbers[later]);
    if (digitalRead(WALKER_UD_BUTTON) == LOW && digitalRead(GREEN_UD_PIN) == HIGH)
    {
      AdjustTrafficLightForUD(former, later);
    }
    /*
    else if (digitalRead(WALKER_LR_BUTTON) == LOW && digitalRead(GREEN_LR_PIN) == HIGH)
    {
      ClearUpper();
      ClearLower();
      doAdjustTrafficLight(RED_LR_PIN, GREEN_LR_PIN, YELLOW_LR_PIN);
    }
    */
    timeEnd = millis();
  }
}

void PrintAndDelay(int duration, int former, int later)
{
  unsigned timeStart;
  unsigned timeEnd;
  timeStart = timeEnd = millis();
  while (timeEnd - timeStart <= duration)
  {
    DisplayStopSign();
    DisplayNumber(gNumbers[former], gNumbers[later]);
    timeEnd = millis();
  }
}

void BlinkLEDForUD(int former, int later)
{
  const int delayTime = LED_YELLOW_BLINK_DURATION / (BLINK_TIME + BLINK_TIME);
  digitalWrite(YELLOW_UD_PIN, HIGH);
  PrintAndDelay(delayTime, former, later);
  digitalWrite(YELLOW_UD_PIN, LOW);
  PrintAndDelay(delayTime, former, later);
}

void AdjustTrafficLightForUD(int former, int later)
{
  delay(TRAFFIC_LIGHT_IDLE_TIME);
  digitalWrite(GREEN_UD_PIN, LOW);
  BlinkLEDForUD(former, later);
  digitalWrite(RED_UD_PIN, HIGH);
}

