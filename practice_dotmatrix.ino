int pinRow[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
int pinCol[] = { 10, 11, 12, 13, 14, 15, 16, 17 };

int num[10][8][4] =
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
  }
};

void clear()
{
  for(int k = 0; k < 8; ++k)
  {
    digitalWrite(pinRow[k], LOW);
    digitalWrite(pinCol[k], HIGH);
  }
}

void displayPattern(int former[][4], int later[][4])
{
  for(int r = 0; r < 8; ++r)
  {
    clear();
    digitalWrite(pinRow[r], HIGH);
    for(int c = 0; c < 4; ++c)
    {
      if(former[r][c]==1)
      {
        digitalWrite(pinCol[c], LOW);
      }
    }
    for(int c = 0; c < 4; ++c)
    {
      if(later[r][c]==1)
      {
        digitalWrite(pinCol[c+4], LOW);
      }
    }
    delay(2);
  }
}

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 8; ++i)
  {
    pinMode(pinRow[i], OUTPUT);
    pinMode(pinCol[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  displayPattern(num[0], num[1]);
}
