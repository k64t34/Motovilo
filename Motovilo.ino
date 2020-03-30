#define  no_DEBUG 1
unsigned long NextMillisCheck;
#include "Motovilo.h" 

void setup(){
#ifdef _DEBUG
Serial.begin(115200);
Debugln("Setup....."); 
#endif  
kpd.begin(); 
lcd.begin(LCD_COLS, LCD_ROWS);  
lcd.clear();
#ifndef _DEBUG
char* adr= (char*)strBoot;
for (byte r=0;r!=LCD_ROWS;r++)
  {
  lcd.setCursor(0, r);  
  for (byte c = 0; c != LCD_COLS; c++)
    {
      lcd.write(pgm_read_byte_near(adr));
      adr++;
    }
  //delay(1000);  
  } 
lcd.noDisplay();
delay(100);    
lcd.display();
delay(800);
lcd.noDisplay();
delay(100);    
lcd.display();
delay(800);
lcd.noDisplay();
delay(100);    
lcd.display();
delay(800);
#endif
//
// Read datafrom EEPROM
//  eeprom_read_block((void*)&Profile, 0, sizeof(Profile));
EEPROM.get(0,Profile);
bool needRewrite=false;
strcpy (Profile.Title,"Gazelle");
if (Profile.Mileage<1 || Profile.Mileage>999)
  {
  needRewrite=true;  
  Profile.Mileage=100;
  }
if (Profile.Velocity<1 || Profile.Velocity>180) 
  {
  needRewrite=true;    
  Profile.Velocity=160;
  }
if (Profile.Pulse1km<1 || Profile.Pulse1km>=6000)
  {
  needRewrite=true; 
  Profile.Pulse1km=6000;     
  }
if (isnan(Profile.PulseVoltageHigh) || Profile.PulseVoltageHigh < 5.0 || Profile.PulseVoltageHigh > 8.5)
  {
  needRewrite=true; 
  Profile.PulseVoltageHigh=5.1;
  }
if (Profile.PulseDuty < 5 || Profile.PulseDuty > 95)
  {
  needRewrite=true;   
  Profile.PulseDuty=50;
  }
if (needRewrite)EEPROM.put(0,Profile);

#ifdef _DEBUG
Debugln("Profile.Name=%s",Profile.Title);
Debugln("Profile.Mileage=%d",Profile.Mileage);
Debugln("Profile.Velocity=%d",Profile.Velocity);
Debugln("Profile.Pulse1km=%d",Profile.Pulse1km);
DebugFloat("Profile.PulseVoltageHigh=%s\n",Profile.PulseVoltageHigh,3,1);
DebugFloat("Profile.PulseVoltageLow=%s\n",Profile.PulseVoltageLow,3,1);
Debugln("Profile.PulseDuty=%d",Profile.PulseDuty);
#endif 
//Assigng screen dialogs
Choose_action::Screen.Loop= NULL;
Choose_action::Screen.Load=&Choose_action_Load;
Choose_action::Screen.Close=nullptr;
Movement::Screen.Loop=&Movement_Loop;
Movement::Screen.Load=&Movement_Load;
Movement::Screen.Close=&Movement_Close;
ScreenAdjustment::Screen.Loop=nullptr;
ScreenAdjustment::Screen.Load=&ScreenAdjustment_Load;
ScreenAdjustment::Screen.Close=&ScreenAdjustment_Close;
ScreenManager.Screens[Choose_actionIndex]=&(Choose_action::Screen);           
ScreenManager.Screens[ScreenAdjustmentIndex]=&(ScreenAdjustment::Screen);           
ScreenManager.Screens[MovementIndex]=&(Movement::Screen);           
#ifdef  _DEBUG_GEN
cur_time=millis();
#else
ScreenManager.Show(0);
#endif
GenTimerInit();
#ifdef _DEBUG
Debugln("Loop....."); 
#endif  
}
//******************************************************************
void loop(){
//******************************************************************  
key = kpd.getKey();  
if (fRefreshInLoop) 
  {
  curMillis=millis();
  if (curMillis>=NextMillisCheck)
    {    
    NextMillisCheck=curMillis+(unsigned long)Period_Refresh;
    (*pRefreshInLoop)();
    }
  }
if (key) ScreenManager.Loop(key); 
   
delay(T_loopdelay);
}


    
