#include "Motovilo.h" 
#define GEN_PIN 15
#define GEN_LED_PIN A0
// Gen
const unsigned long g_Fclk=16777216; //16MHz
const int g_timerPrescale = 8;// 1024/256/64/8/1  - prescale value
const byte g_timerOCR =255;//Output compare register
bool gEnable=false; //вкл/выкл генерацию
bool gMeasureUhMode=false; // перевод в режим измерения уровня напряжения выского уровня импульса
volatile int g_timerIntCntH=1024; //Время высокого уровня импульса
volatile int g_timerIntCntL=4096; //Время низкого уровня импульса
volatile bool g_H;// 1- время высокого, 0 -время низкого
volatile int g_InterruptCounter;
volatile unsigned long g_ImpulseCounter;
byte c_pos=0;
byte r_pos=0;

unsigned long last_time=0;
unsigned long cur_time=1;
volatile unsigned long dInterruptCounter=0;
//******************************************************************
ISR(TIMER2_OVF_vect){ // Interrupt Service Routines (ISR)
dInterruptCounter++;
/*if (gEnable)
  {
  g_InterruptCounter++;
  if (g_H)
    {
    if (g_InterruptCounter == g_timerIntCntH)
      {
      g_H=LOW;  
      g_InterruptCounter=0;
      digitalWrite(GEN_LED_PIN, LOW);  
      }
    }
  else
    {    
    if (g_InterruptCounter == g_timerIntCntL)    
      {
      g_H=HIGH;  
      g_InterruptCounter=0;
      g_ImpulseCounter++;
      digitalWrite(GEN_LED_PIN, HIGH);  
      }
    }
  }*/
}
void setup(){
lcd.begin(LCD_COLS, LCD_ROWS);  
/*lcd.print("5.5 V+-----+300 K/h ");
lcd.print("0.1 V|     |        ");    
lcd.print("     | 15% |6000/1km");
lcd.print("-----+     +--------");   
//delay(10000);*/
//
Profile.Name="Gazelle 1";
Profile.Mileage=100;
Profile.Velocity=255;
Profile.Pulse1km=6000;
Profile.PulseVoltageHigh=5.1;
Profile.PulseVoltageLow=0.1;
Profile.PulseDuty=5;
//Gen
pinMode(GEN_PIN, OUTPUT);
pinMode(GEN_LED_PIN, OUTPUT);
digitalWrite(GEN_LED_PIN, HIGH); 
gEnable=true;
g_H=LOW;
//Set timer2
noInterrupts(); //disable all interrupts
TCCR2A = 0;
TCCR2B |= (0<<CS22)|(0<<CS21)|(1<<CS20);// set no  prescaler for timer2 
//TCCR2B |= (0<<CS22)|(1<<CS21)|(0<<CS20);// set 8 the prescaler for timer2 
TIMSK2 |= (1<<TOIE2);// enable overflow intterupts for timer2
TCNT2 = 0;// initailize the counter
interrupts(); //enable all interrupts  
//$003 rjmp TIMER2_COMP_vect    ;прерывание совпадения сравнения таймера 2
//$004 rjmp TIMER2_OVF_vect     ;прерывание переполнения таймера 2
  
for (byte i=0;i!=KB_COUNT;i++) pinMode(Keys[i].Pin,INPUT_PULLUP);  
for (byte i=0;i!=KB_COUNT;i++)Keys[i].Block=false; 
ScreenManager.Screens[0]=&(ScreenAdjustment::Screen);           
  
//ScreenManager.Show(0);

cur_time=millis();
//micros(): версия 16 МГц возвращает результат с дискретностью 4, а 8 МГц - с дискретностью 8.

}

//******************************************************************
void loop(){
//******************************************************************  
last_time=cur_time;
cur_time=millis();
long dtime = cur_time-last_time;
lcd.setCursor(0,r_pos);
lcd.print(millis() );
lcd.write(' ');
if (g_H)
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
lcd.print(dInterruptCounter);

//if (r_pos==3)
//  {
//  r_pos=0;
//  //if (c_pos==0) c_pos=10;else c_pos=0;  
//  }else r_pos++ ;
//if (r_pos==0 || r_pos==2)
//  {
//  digitalWrite(GEN_LED_PIN, HIGH);
//  analogWrite(GEN_PIN, HIGH);
//  }
//else
//  {
//  digitalWrite(GEN_LED_PIN, LOW);
//  digitalWrite(GEN_PIN, LOW);
//  }
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
delay(100);
}


    
