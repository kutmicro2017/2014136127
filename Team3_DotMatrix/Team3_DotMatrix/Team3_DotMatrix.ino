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

//상단 신호 출력용 매트릭스 핀 번호 배열
int gUpperPinRow[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
int gUpperPinCol[] = { 10, 11, 12, 13, 14, 15, 16, 17 };
//하단 신호 출력용 매트릭스 핀 번호 배열
int gLowerPinRow[] = { 22, 24, 26, 28, 30, 32, 34, 36 };
int gLowerPinCol[] = { 23, 25, 27, 29, 31, 33, 35, 37 };

//기타 기호상수
#define DRIVABLE_DURATION           20000u                                                  //주행 가능 시간, 녹색등 유지시간(20sec)
#define LED_YELLOW_BLINK_DURATION   5000u                                                   //경고등 점멸 시간(5sec)
#define BLINK_TIME                  LED_YELLOW_BLINK_DURATION / 1000                        //점멸 횟수(1초당 1회)
#define TRAFFIC_LIGHT_IDLE_TIME     3000u                                                   //입력 받았을 시 대기 시간(3sec)
#define ARRAY_LENGTH                8                                                       //배열 길이
#define CYCLE                       (DRIVABLE_DURATION + LED_YELLOW_BLINK_DURATION) / 1000  //신호 바뀔 때까지의 걸리는 시간

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

//좌우를 위한 함수
//기능 : 좌우의 노란등을 한번 점멸합니다.
void BlinkLEDForLR();

//위아래를 위한 함수
//기능 : 위아래의 노란등을 한번 점멸합니다.
//인자 : former는 출력할 수의 십의 자리, later는 출력할 수의 일의 자리입니다.
void BlinkLEDForUD(int former, int later);
//기능 : 신호를 바꿉니다.
void AdjustTrafficLightForUD();
//기능 : duration 동안 타이머를 출력하면서 폴링을 받습니다.
//인자 : duration은 ms단위이고, former는 출력할 수의 십의 자리, later는 출력할 수의 일의 자리입니다.
void PrintStopSignWithPolling(int duration, int former, int later);
//기능 : duration 동안 타이머를 출력합니다.
//인자 : duration은 ms단위입니다.
void DisplayTimer(int duration);

//공통 함수
//기능 : 상단의 DotMatrix 신호를 지웁니다.
void ClearUpper();
//기능 : 하단의 DotMatrix 신호를 지웁니다.
void ClearLower();
//기능 : former, later순으로 DotMatrix에 숫자를 출력합니다.
//인자 : former는 출력할 수의 십의 자리, later는 출력할 수의 일의 자리입니다.
void DisplayNumber(int former[][4], int later[][4]);
//기능 : 상단 DotMatrix에 정지 신호를 출력합니다.
void DisplayStopSign();
//기능 : 하단 DotMatrix에 보행 신호를 출력합니다.
void DisplayWalkSign();
//기능 : duration 동안 타이머를 출력하면서 대기합니다.
//인자 : duration은 ms 단위, former는 출력할 수의 십의 자리, later는 출력할 수의 일의 자리입니다.
void PrintStopSign(int duration, int former, int later);
//기능 : 보행 신호를 출력합니다.
void PrintWalkSign();

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
  //입력 핀 모드 설정
  pinMode(WALKER_UD_BUTTON, INPUT_PULLUP);
}

void loop()
{
  //상하 주행
  digitalWrite(RED_LR_PIN, HIGH);
  digitalWrite(GREEN_UD_PIN, HIGH);
  for (int t = CYCLE; t >= 0; --t)
  {
     int former = t / 10;
     int later = t % 10;
     if (t > BLINK_TIME)
     {
        PrintStopSignWithPolling(1000, former, later);
     }
     else if (digitalRead(RED_UD_PIN) == LOW)
     {
       digitalWrite(GREEN_UD_PIN, LOW);
       BlinkLEDForUD(former, later);
     }
  }
  digitalWrite(RED_LR_PIN, LOW);
  
  //좌우 주행
  digitalWrite(RED_UD_PIN, HIGH);
  digitalWrite(GREEN_LR_PIN, HIGH);
  for (int t = CYCLE; t >= 0; --t)
  {
     int former = t / 10;
     int later = t % 10;
     if (t > BLINK_TIME)
     {
        PrintWalkSign(1000);
     }
     else if (digitalRead(RED_LR_PIN) == LOW)
     {
       digitalWrite(GREEN_LR_PIN, LOW);
       BlinkLEDForLR();
     }
  }
  digitalWrite(RED_UD_PIN, LOW);
}

void BlinkLEDForLR()
{
  static const int delayTime = LED_YELLOW_BLINK_DURATION / (BLINK_TIME + BLINK_TIME);
  
  digitalWrite(YELLOW_LR_PIN, HIGH);
  PrintWalkSign(delayTime);
  digitalWrite(YELLOW_LR_PIN, LOW);
  PrintWalkSign(delayTime);
}

void BlinkLEDForUD(int former, int later)
{
  static const int delayTime = LED_YELLOW_BLINK_DURATION / (BLINK_TIME + BLINK_TIME);
  
  digitalWrite(YELLOW_UD_PIN, HIGH);
  PrintStopSign(delayTime, former, later);
  digitalWrite(YELLOW_UD_PIN, LOW);
  PrintStopSign(delayTime, former, later);
}

void AdjustTrafficLightForUD()
{
  for (int t = TRAFFIC_LIGHT_IDLE_TIME / 1000 + BLINK_TIME; t >= 0; --t)
  {
    if (t > BLINK_TIME)
    {
      //1초간 타이머 출력
      PrintStopSign(1000, t / 10, t % 10);
    }
    else
    {
      digitalWrite(GREEN_UD_PIN, LOW);
      BlinkLEDForUD(t / 10, t % 10);
    }
  }
  digitalWrite(RED_UD_PIN, HIGH);
  PrintWalkSign(DRIVABLE_DURATION + LED_YELLOW_BLINK_DURATION);
}

void PrintStopSignWithPolling(int duration, int former, int later)
{
  unsigned timeStart;
  unsigned timeEnd;
  timeStart = timeEnd = millis();
  while (timeEnd - timeStart <= duration)
  {
    DisplayStopSign();
    DisplayNumber(gNumbers[former], gNumbers[later]);
    //Polling
    if (digitalRead(WALKER_UD_BUTTON) == LOW && digitalRead(GREEN_UD_PIN) == HIGH)
    {
      AdjustTrafficLightForUD();
    }
    timeEnd = millis();
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
      if(gWalkerSigns[0][r][c])
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

void PrintStopSign(int duration, int former, int later)
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

void PrintWalkSign(unsigned duration)
{
  ClearUpper();
  unsigned timeStart;
  unsigned timeEnd;
  timeStart = timeEnd = millis();
  while (timeEnd - timeStart <= duration)
  {
    DisplayWalkSign();
    timeEnd = millis();
  }
}
