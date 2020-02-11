#define _DEBUG 1
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
//#include "LiquidCrystalRus.h"

#include "debug.h" 
#include <MyDebug.h>
#include "config.h"

LiquidCrystal lcd(LCD_RS,LCD_E,LCD_D4,LCD_D5,LCD_D6,LCD_D7);

// Keypad
#include <Keypad_I2C.h> //https://github.com/joeyoung/arduino_keypads/tree/master/Keypad_I2C
#define KP_ROWS  4
#define KP_COLS  4
const char KP_KEYS[KP_ROWS][KP_COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
//Use this array if the cable is connected directly.
//const byte I2Cpin_rows[KP_ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
//const byte I2Cpin_cols[KP_COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad
//Use this array if the cable is connected rotated 180
const byte I2Cpin_rows[KP_ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
const byte I2Cpin_cols[KP_COLS] = {3, 2, 1, 0}; //connect to the column pinouts of the keypad

#define I2CAddress  0x20
Keypad_I2C kpd = Keypad_I2C( makeKeymap(KP_KEYS),  
  I2Cpin_rows, 
  I2Cpin_cols, 
  KP_ROWS, 
  KP_COLS,
  I2CAddress,
  PCF8574);
char key; // Pressed key in loop

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
unsigned long curMillis;
bool fRefreshInLoop=false;
void (*pRefreshInLoop)();


struct MyProfile
{ 
  char Title[LCD_COLS];
  int Mileage ;//Пробег
  byte Velocity;
  int Pulse1km;
  float PulseVoltageHigh;
  float PulseVoltageLow;
  byte PulseDuty;  
  };  
MyProfile Profile;

printStatusString(){//************************************
lcd.setCursor(0,3);
lcd.print(Profile.Title);
lcd.setCursor(7,3);
lcd.write(' ');
lcd.print(Profile.Velocity);
lcd.print("kmh");
lcd.write(' ');
lcd.print(Profile.Mileage);
lcd.print("km");
}

//MyProfile *Profile = &Profile1;
#define Period_Refresh 1000
#include "myGen.h"
#include "myScreen.h"
#include "Movement.h"
#include "ScreenAdjustment.h"
#include "Choose_action.h"


const char strBoot[LCD_ROWS][LCD_COLS] PROGMEM =
{
"  L O A D I N G ... ",
" Crankshaft sensor  ",
" TESTER   ver 0102  ",
"   (c) Bosch 2020   "};

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
