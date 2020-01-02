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
struct myButttonPin {
  byte Pin; 
  const String  Name;
  bool Block; //Если значение заблокировано, то не смотря на поступающие данные поле Value остается неизменным
  bool Value;
  bool Raw;
  };  
#define BUTTON_PIN_COUNT 4
#define BUTTON_LEFT   0
#define BUTTON_RIGHT  1
#define BUTTON_ESC    2
#define BUTTON_ENTER  3
myButttonPin Buttton[]={
{PIN_BUTTON_LEFT,"LEFT",true,false,true},
{PIN_BUTTON_RIGHT,"RIGHT",true,false,true},
{PIN_BUTTON_ESC,"ESC",true,false,true},
{PIN_BUTTON_ENTER,"ENTER",true,false,true}
};
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

class MyProfile
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
MyProfile Profile1;
MyProfile *Profile = &Profile1;


#include "myScreen.h"
#include "ScreenAdjustment.h"
