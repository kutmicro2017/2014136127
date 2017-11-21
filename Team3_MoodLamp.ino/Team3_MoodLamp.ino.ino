#include <Adafruit_NeoPixel.h>
#include <math.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

enum eColor { RED_TO_BLUE, ORANGE_TO_PURPLE, YELLOW_TO_CYAN };

#define NEO_PIXEL 4
#define COLOR_BUTTON 2
#define BRIGHTNESS_BUTTON 3
#define TEMP_SENSOR A5

#define LOWEST_TEMPERATURE 0
#define NORMAL_TEMPERATURE 15
#define HIGHEST_TEMPERATURE 30

volatile int gBrightness = 2;
volatile int gColor = eColor::RED_TO_BLUE;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void EmitRB(int temperature);
void EmitOP(int temperature);
void EmitYC(int temperature);

void ChangeColor();
void ChangeBrightness();

void setup()
{
#ifdef __AVR_ATtiny85__
  if (F_CPU) == 16000000)
  {
    clock_prescale_set(clock_div_1); 
  }
#endif
  strip.begin();
  strip.show();
/*터치센서
  pinMode(COLOR_BUTTON, INPUT_PULLUP);
  pinMode(BRIGHTNESS_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(COLOR_BUTTON), ChangeColor, LOW);
  attachInterrupt(digitalPinToInterrupt(BRIGHTNESS_BUTTON), ChangeBrightness, LOW); 
*/

/*온도측정
  Serial.begin(9600);
  */
}

void loop()
{
  /*온도측정
  static const int thermistor = 4275;
  static const int R0 = 100000; // 100kelvin

  int analogVal = analogRead(TEMP_SENSOR);
  float R = 1023.f / a - 1.f;
  R *= R0;
  float temperature = 1.f / (log(R / R0) / thermistor + 1 / 298.15f) - 273.15f;
  */

/*
  switch (gColor)
  {
  case eColor::RED_TO_BLUE:
    EmitRB(0);
    break;
  case eColor::ORANGE_TO_PURPLE:
    EmitOP(0);
    break;
  default:
    EmitYG(0);
    break;
  }
  */

  
  for (int i = 300; i >= 0; --i)
  {
    EmitOP(i);
    delay(100);
  }
}

void EmitRB(int temperature)
{
  //RED : (255, 0, 0)
  //BLUE : (0, 0, 255)
  static const int normalTemperature = NORMAL_TEMPERATURE * 10;
  
  int red = 0;
  int green = 0;
  int blue = 0;
  if (temperature >= normalTemperature)
  {
    red = 255;
    green = 255 - 1.7f * (temperature - normalTemperature);
    blue = 255 - 1.7f * (temperature - normalTemperature);
  }
  else
  {
    red = 255 - 1.7f * (normalTemperature - temperature);
    green = 255 - 1.7f * (normalTemperature - temperature);
    blue = 255;
  }
  for (int i = 0; i < gBrightness; ++i)
  {
    strip.setPixelColor(i, red, green, blue);
  }
  strip.show();
}
void EmitOP(int temperature)
{
  //ORANGE : (255, 50, 0)
  //PURPLE : (150, 0, 220)
  static const int normalTemperature = NORMAL_TEMPERATURE * 10;
  
  int red = 0;
  int green = 0;
  int blue = 0;
  if (temperature >= normalTemperature)
  {
    red = 255;
    green = 255 - 1.4f * (temperature - normalTemperature);
    blue = 255 - 1.7f * (temperature - normalTemperature);
  }
  else
  {
    red = 255 - 0.7f * (normalTemperature - temperature);
    green = 255 - 1.7f * (normalTemperature - temperature);
    blue = 255 - 0.23f * (normalTemperature - temperature);
  }
  for (int i = 0; i < gBrightness; ++i)
  {
    strip.setPixelColor(i, red, green, blue);
  }
  strip.show();
}

void EmitYC(int temperature)
{
  //YELLOW : (255, 255, 0)
  //CYAN : (0, 255, 255)
  static const int normalTemperature = NORMAL_TEMPERATURE * 10;
  
  int red = 0;
  int green = 0;
  int blue = 0;
  if (temperature >= normalTemperature)
  {
    red = 255;
    green = 255;
    blue = 255 - 1.7f * (temperature - normalTemperature);
  }
  else
  {
    red = 255 - 1.7f * (normalTemperature - temperature);
    green = 255;
    blue = 255;
  }
  for (int i = 0; i < gBrightness; ++i)
  {
    strip.setPixelColor(i, red, green, blue);
  }
  strip.show();
}
void ChangeColor()
{
  gColor = (gColor + 1) % 3;
}

void ChangeBrightness()
{
  if (gBrightness == 16)
  {
    gBrightness = 2;
  }
  else
  {
    gBrightness += 2;
  }
}

