// 신호등 작동시간 출력용 매트릭스 핀 번호 배열
int timePinRow[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
int timePinCol[] = { 10, 11, 12, 13, 14, 15, 16, 17 };
// 보행자 신호 출력용 매트릭스 핀 번호 배열
int signPinRow[] = { 22, 24, 26, 28, 30, 32, 34, 36 };
int signPinCol[] = { 23, 25, 27, 29, 31, 33, 35, 37 };

// 보행자 신호등 작동시간
#define WALKABLE_TIME 10

// 시간 간격 유지를 위한 변수들
unsigned timeFirst = 0;
unsigned timeLast = 0;
#define ONE_SECOND 1000

int numbers[10][8][4] =
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

int signs[2][8][8] =
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

void clearTime()
{
  for(int k = 0; k < 8; ++k)
  {
    digitalWrite(timePinRow[k], LOW);
    digitalWrite(timePinCol[k], HIGH);
  }
}
void clearSign()
{
  for(int k = 0; k < 8; ++k)
  {
    digitalWrite(signPinRow[k], LOW);
    digitalWrite(signPinCol[k], HIGH);
  }
}

void displayNumbers(int former[][4], int later[][4])
{
  for(int r = 0; r < 8; ++r)
  {
    clearTime();
    digitalWrite(timePinRow[r], HIGH);
    for(int c = 0; c < 4; ++c)
    {
      if(former[r][c]==1)
      {
        digitalWrite(timePinCol[c], LOW);
      }
    }
    for(int c = 0; c < 4; ++c)
    {
      if(later[r][c]==1)
      {
        digitalWrite(timePinCol[c+4], LOW);
      }
    }
    delay(2);
  }
}
void displaySigns(int signs[][8])
{
  for(int r = 0; r < 8; ++r)
  {
    clearSign();
    digitalWrite(signPinRow[r], HIGH);
    for(int c = 0; c < 8; ++c)
    {
      if(signs[r][c]==1)
      {
        digitalWrite(signPinCol[c], LOW);
      }
    }
    delay(2);
  }
}

void canCross()
{
  for(int t = WALKABLE_TIME; t > -1; --t)
  {
    int FORM = t/10, LATE = t%10;
    timeFirst = millis();
    for(;;)
    {
      displaySigns(signs[1]);
      displayNumbers(numbers[FORM], numbers[LATE]);
      timeLast = millis();
      if(timeLast - timeFirst >= ONE_SECOND)
      {
        clearTime();
        clearSign();
        break;
      }
    }
  }
}
void crosswalk()
{
  timeFirst = millis();
  for(;;)
  {
    displaySigns(signs[0]);
    timeLast = millis();
    if(timeLast - timeFirst >= 5000)
    {
      break;
    }
  }
  
  canCross();
}

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 8; ++i)
  {
    pinMode(timePinRow[i], OUTPUT);
    pinMode(timePinCol[i], OUTPUT);

    pinMode(signPinRow[i], OUTPUT);
    pinMode(signPinCol[i], OUTPUT);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  crosswalk();
}
