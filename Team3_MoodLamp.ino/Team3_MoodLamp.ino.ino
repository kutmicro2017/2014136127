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
#define BATTERY A0

#define LOWEST_TEMPERATURE 0
#define NORMAL_TEMPERATURE 15
#define HIGHEST_TEMPERATURE 30

volatile int gBrightness = 2;
volatile int gColor = eColor::RED_TO_BLUE;
Adafruit_NeoPixel gCirclePixel = Adafruit_NeoPixel(16, NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void EmitRB(int temperature);
void EmitOP(int temperature);
void EmitYC(int temperature);
void TurnOnPixel(int red, int green, int blue);

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
  gCirclePixel.begin();
  gCirclePixel.show();
/*터치센서
  pinMode(COLOR_BUTTON, INPUT_PULLUP);
  pinMode(BRIGHTNESS_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(COLOR_BUTTON), ChangeColor, LOW);
  attachInterrupt(digitalPinToInterrupt(BRIGHTNESS_BUTTON), ChangeBrightness, LOW); 
*/

  Serial.begin(9600);
}

void loop()
{
  static const int thermistor = 4275;
  static const int R0 = 100000; // 100kelvin

  int analogVal = analogRead(TEMP_SENSOR);
  float R = 1023.f / a - 1.f;
  R *= R0;
  float temperature = 1.f / (log(R / R0) / thermistor + 1 / 298.15f) - 273.15f;

  Serial.print("Temp : ");
  Serial.println(temperature);
  
  switch (gColor)
  {
  case eColor::RED_TO_BLUE:
    EmitRB(temperature * 10.f);
    break;
  case eColor::ORANGE_TO_PURPLE:
    EmitOP(temperature * 10.f);
    break;
  default:
    EmitYC(temperature * 10.f);
    break;
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

  TurnOnPixel(red, green, blue);
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

  TurnOnPixel(red, green, blue);
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

  TurnOnPixel(red, green, blue);
}

void TurnOnPixel(int red, int green, int blue)
{ 
  gCirclePixel.clear();
  for (int i = 0; i < gBrightness; ++i)
  {
    gCirclePixel.setPixelColor(i, red, green, blue);
  }
  gCirclePixel.show();
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

