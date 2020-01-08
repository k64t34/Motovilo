#define _DEBUG 1
#include <avr/pgmspace.h>
//#include <EEPROM.h>
#include <LiquidCrystal.h>
//#include "LiquidCrystalRus.h"

#include "debug.h" 
#include <MyDebug.h>
#include "config.h"

LiquidCrystal lcd(LCD_RS,LCD_E,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
//
// Digital Input
//
struct myKB {
  const byte Pin;  
  const byte Id; 
  bool Block; //Если значение заблокировано, то не смотря на поступающие данные поле Value остается неизменным
  bool Value;
  bool Raw;
  };  
#define KB_COUNT 4
#define KEY_LEFT   0
#define KEY_RIGHT  1
#define KEY_ESC    2
#define KEY_ENTER  3
myKB Keys[]={
{PIN_BUTTON_LEFT,KEY_LEFT,true,false,true},
{PIN_BUTTON_RIGHT,KEY_RIGHT,true,false,true},
{PIN_BUTTON_ESC,KEY_ESC,true,false,true},
{PIN_BUTTON_ENTER,KEY_ENTER,true,false,true}
};
short KeyPressed=-1;

//***********************************************************
lcd_print_center(int Row,String Text){ 
//***********************************************************
int str_len=Text.length();
if (str_len>=LCD_COLS)
  str_len=0;
else
  str_len=ceil((LCD_COLS-str_len)/2);
lcd.setCursor(str_len, Row);
lcd.print(Text);
}
//
// Variable
//

struct MyProfile
{  
  public:
  String  Name;
  int Mileage ;//Пробег
  byte Velocity;
  int Pulse1km;
  float PulseVoltageHigh;
  float PulseVoltageLow;
  byte PulseDuty;  
  };  
MyProfile Profile;
//MyProfile *Profile = &Profile1;
#include "myGen.h"

#include "myScreen.h"
#include "ScreenAdjustment.h"



/*
// HW Info
#define Vref 1100
int mvVcc;
ADMUX = 1<<REFS0 | 0x0E;
ADCSRA = (1<<ADEN) | (1<<ADATE) | (1<<ADSC) | 5;
delay(1);
mvVcc = (1023L * Vref) / ADC;
lcd.setCursor(0,0);
lcd.print("VCC = ");
lcd.print(mvVcc);
lcd.print(" mV");

//micros(): версия 16 МГц возвращает результат с дискретностью 4, а 8 МГц - с дискретностью 8.
unsigned long ustime1, ustime2;
int i, mhzFreq, iMax = 10000;
lcd.setCursor(0,1);
lcd.print("F_CPU=");
lcd.println(F_CPU);
ustime1 = micros();
for(i=iMax; i>0; i--) __asm__("nop\n\t");
ustime2 = micros();
mhzFreq = 5 * (long)iMax / (ustime2 - ustime1) + 1;
lcd.setCursor(0,2);
lcd.print("Freq = ");
lcd.print(mhzFreq);
lcd.println(" MHz");
*/
