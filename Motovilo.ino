#define DEBUG 1
unsigned long NextMillisCheck;
#include "Motovilo.h" 

void setup(){
#ifdef _DEBUG
Serial.begin(115200);
Debugln("Setup...");
#endif  
//#ifdef _DEBUG_PROFILE   1
//for ( int i=0;i!=5;i++)
//{
//Debug("%d\t",i);
//Debug("%d\t",(MyField*)(ScreenManager.Screens[0]->Rows[i]).Type);
//serial.print(Value);Debug("\t");
//serial.print(minValueValue);Debug("\t");
//serial.print(maxValueValue);DebugLn("\t");  
//Rows  
//}
//#endif
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
  delay(1000);  
  } 
lcd.noDisplay();
delay(500);    
lcd.display();
delay(1000);
lcd.noDisplay();
delay(500);    
lcd.display();
delay(1000);
lcd.noDisplay();
delay(500);    
lcd.display();
delay(1000);
#endif
//
strcpy (Profile.Name,"Gazelle");
Profile.Mileage=40;
Profile.Velocity=120;
Profile.Pulse1km=6000;
Profile.PulseVoltageHigh=5.1;
Profile.PulseVoltageLow=0.1;
Profile.PulseDuty=50;
sprintf(StatusString,"%s/%3ukph/%3ukm",
  Profile.Name/*.substring(0,7)*/,
  Profile.Velocity,  
  Profile.Mileage
  );
#ifdef _DEBUG
Debugln("Profile.Name=%s",Profile.Name);
Debugln("Profile.Mileage=%d",Profile.Mileage);
Debugln("Profile.Velocity=%d",Profile.Velocity);
Debugln("Profile.Pulse1km=%d",Profile.Pulse1km);
DebugFloat("Profile.PulseVoltageHigh=%s\n",Profile.PulseVoltageHigh,3,1);
DebugFloat("Profile.PulseVoltageLow=%s\n",Profile.PulseVoltageLow,3,1);
Debugln("Profile.PulseDuty=%d",Profile.PulseDuty);
Debugln(StatusString);
#endif 
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
 
//C_loops1min_downcounter--;
//if (C_loops1min_downcounter==0)
//  {
//    C_loops1min_downcounter=C_loops1min;
//  }
  
#ifdef  _DEBUG_GEN_CALC   
lcd.setCursor(0,0);
//lcd.print(g_InterruptCounter);
lcd.print(g_ImpulseCounter);
#endif 
#ifdef  _DEBUG_GEN
last_time=cur_time;
cur_time=millis();
long dtime = cur_time-last_time;
lcd.setCursor(0,r_pos);
lcd.print(millis() );
lcd.write(' ');
if (g_ImpulsePhase)
  {
  lcd.write('H');  
  lcd.print(g_timerIntCntH);
  }
else  
  {
  lcd.write('L');  
  lcd.print(g_timerIntCntL);
  }
lcd.write(' ');
lcd.print(g_InterruptCounter);
lcd.write(' ');
lcd.print(g_ImpulseCounter);
lcd.setCursor(0,2);
lcd.print("dtime=");
lcd.print(dtime);
lcd.setCursor(0,3);
lcd.print("irq/msec=");
lcd.print(((double)(dInterruptCounter-lastdInterruptCounter)/dtime)*(double)1000.0);
lastdInterruptCounter = dInterruptCounter;
#endif

delay(T_loopdelay);
}


    
