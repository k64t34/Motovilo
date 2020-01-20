#define noDEBUG 1
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
  
lcd.begin(LCD_COLS, LCD_ROWS);  
/*lcd.print("5.5 V+-----+300 K/h ");
lcd.print("0.1 V|     |        ");    
lcd.print("     | 15% |6000/1km");
lcd.print("-----+     +--------");   
//delay(10000);*/
//
Profile.Name="Gazelle 1\0";
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
  
for (byte i=0;i!=KB_COUNT;i++) pinMode(Keys[i].Pin,INPUT_PULLUP);  
for (byte i=0;i!=KB_COUNT;i++)Keys[i].Block=false; 
ScreenManager.Screens[0]=&(ScreenAdjustment::Screen);           
  
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


    
