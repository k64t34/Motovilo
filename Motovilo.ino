#define DEBUG 1
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
Profile.Name="Gazelle1";
Profile.Mileage=100;
Profile.Velocity=50;
Profile.Pulse1km=6000;
Profile.PulseVoltageHigh=5.1;
Profile.PulseVoltageLow=0.1;
Profile.PulseDuty=50;
#ifdef _DEBUG
Debugln("Profile.Name=%s",Profile.Name);
Debugln("Profile.Mileage=%d",Profile.Mileage);
Debugln("Profile.Velocity=%d",Profile.Velocity);
Debugln("Profile.Pulse1km=%d",Profile.Pulse1km);
DebugFloat("Profile.PulseVoltageHigh=%s\n",Profile.PulseVoltageHigh,3,1);
DebugFloat("Profile.PulseVoltageLow=%s\n",Profile.PulseVoltageLow,3,1);
Debugln("Profile.PulseDuty=%d",Profile.PulseDuty);
#endif 
ScreenManager.Screens[Choose_actionIndex]=&(Choose_action::Screen);           
ScreenManager.Screens[ScreenAdjustmentIndex]=&(ScreenAdjustment::Screen);           
  
#ifdef  _DEBUG_GEN
cur_time=millis();
#else
ScreenManager.Show(0);
#endif
GenTimerInit();
GenSet();
}
//******************************************************************
void loop(){
//******************************************************************  
key = kpd.getKey();  
if (key)ScreenManager.Loop(key);
 
  
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

delay(50);
}


    
