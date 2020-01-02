//sprint(line1, "Temp: %d C", tempC);
#define _DEBUG 1
#include "Motovilo.h" 
byte Status=0; // 0 - startup, 1 - tune, 2- control
unsigned long time; //Current time
volatile bool statusAlarm=false;
volatile bool statusStopEngine=false;
bool INPUT_CHG=false;
unsigned long FramePeriod; // Период одного фрейма = 1000/FPS
#ifdef _DEBUG
unsigned long SecondInterval;
#endif
int ch=0;
//******************************************************************
void setup(){
//******************************************************************  
Profile1.Name="Gazelle 1";
Profile1.Mileage=100;
Profile1.Velocity=255;
Profile1.Pulse1km=6000;
Profile1.PulseVoltageHigh=5.1;
Profile1.PulseVoltageLow=0.1;
Profile1.PulseDuty=5;
#if (_DEBUG & _DEBUG_SETUP)
Debug("Setup...");
#endif  
time = millis();
#ifdef _DEBUG
#endif

lcd.begin(LCD_COLS, LCD_ROWS);
lcd.print("     Attantion!");
lcd.setCursor(0, 1);
lcd.print("  This device use ");
lcd.setCursor(0, 2);
lcd.print("  custom Pin 1 OBD2");
lcd.setCursor(0, 3);
lcd.print("It must connect to");
delay(1000);
lcd.setCursor(0, 0);
lcd.print("  This device use ");
lcd.setCursor(0, 1);
lcd.print("  custom Pin 1 OBD2   ");
lcd.setCursor(0, 2);
lcd.print("It must connect to  ");
lcd.setCursor(0, 3);
lcd.print("speed sensor!       ");
//lcd.print("12345678901234567890");
delay(1000);
for (byte i=0;i!=BUTTON_PIN_COUNT;i++){
  pinMode(Buttton[i].Pin,INPUT_PULLUP);
  } 
for (byte i=0;i!=BUTTON_PIN_COUNT;i++)Buttton[i].Block=false;    
//Debugln("OK");
ScreenAdjustmentInit();
ScreenManager.Add(&ScreenAdjustment);
}

//******************************************************************
void loop(){
//******************************************************************  
bool PressAnyKey=false;
for (byte i=0;i!=BUTTON_PIN_COUNT;i++)
  {
  Buttton[i].Raw=digitalRead(Buttton[i].Pin);
  if (Buttton[i].Block)
    {
      if (Buttton[i].Raw==HIGH)
        Buttton[i].Block=false;
    }
  else
    {    
    Buttton[i].Value=!Buttton[i].Raw;
    PressAnyKey=true;
    }  
  } 
if (PressAnyKey)
  if (EditField.Enable)
    {
    if (Buttton[BUTTON_RIGHT].Value)      EditField.IncreaseValue();
    else if (Buttton[BUTTON_LEFT].Value)  EditField.ReduceValue();
    else if (Buttton[BUTTON_ENTER].Value) EditField.Save();
    else if (Buttton[BUTTON_ESC].Value) EditField.Exit();  
    }
  else if(ScreenManager.Screens[ScreenManager.current]->Menu.ItemsCount!=0)
  {
  if (Buttton[BUTTON_RIGHT].Value)
    ScreenManager.Screens[ScreenManager.current]->Menu.GotoNext();
  else if (Buttton[BUTTON_LEFT].Value)
    ScreenManager.Screens[ScreenManager.current]->Menu.GotoPrevious(); 
  else if (Buttton[BUTTON_ENTER].Value)
    {    
    (*ScreenManager.Screens[ScreenManager.current]->Menu.Items[ScreenManager.Screens[ScreenManager.current]->Menu.SelectedItem].Action)(ScreenManager.Screens[ScreenManager.current]->Menu.SelectedItem);  
  //  ScreenManager.Screens[ScreenManager.current]->Menu.Items[ScreenManager.Screens[ScreenManager.current]->Menu.SelectedItem] 
    }
  }  
//time = millis();
//lcd.cursor(); // показываем курсор*/
//lcd.setCursor(2, 1);
//lcd.blink();
delay(50);
}


    
