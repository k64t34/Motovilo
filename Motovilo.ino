#include "Motovilo.h" 
//******************************************************************
void setup(){
Profile.Name="Gazelle 1";
Profile.Mileage=100;
Profile.Velocity=255;
Profile.Pulse1km=6000;
Profile.PulseVoltageHigh=5.1;
Profile.PulseVoltageLow=0.1;
Profile.PulseDuty=5;
  
ScreenManager.Screens[0]=&(ScreenAdjustment::Screen);
lcd.begin(LCD_COLS, LCD_ROWS);
for (byte i=0;i!=KB_COUNT;i++) pinMode(Keys[i].Pin,INPUT_PULLUP);  
for (byte i=0;i!=KB_COUNT;i++)Keys[i].Block=false;    
ScreenManager.Show(0);
}

//******************************************************************
void loop(){
//******************************************************************  
KeyPressed=-1;
for (byte i=0;i!=KB_COUNT;i++)
  {
  Keys[i].Raw=digitalRead(Keys[i].Pin);
  if (Keys[i].Block)
    {
      if (Keys[i].Raw==HIGH)
        Keys[i].Block=false;
    }
  else if (Keys[i].Raw==LOW)
    {    
    Keys[i].Value=true;
    KeyPressed=Keys[i].Id;
    Keys[i].Value=false;  
    Keys[i].Block=true;
    break;
    }  
  } 
if (KeyPressed>=0)  ScreenManager.Loop(KeyPressed);  
//time = millis();
delay(50);
}


    
