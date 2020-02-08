#define MAX_UnsignedLong 4294967295
#ifdef  _DEBUG_GEN
byte c_pos=0;
byte r_pos=0;
unsigned long last_time=0;
unsigned long cur_time=1;
volatile unsigned long dInterruptCounter=0;
unsigned long lastdInterruptCounter=0;
#endif
// Gen
const unsigned long g_Fclk=15104000; //Частота процессора 16MHz
const int g_timerPrescale = 8;// 1024/256/64/8/1  - prescale value
//const byte g_timerOCR =255;//Output compare register
bool gEnable=false; //вкл/выкл генерацию
bool gMeasureUhMode=false; // перевод в режим измерения уровня напряжения выского уровня импульса
volatile unsigned int g_timerIntCntH=1024; //Время высокого уровня импульса
volatile unsigned int g_timerIntCntL=4096; //Время низкого уровня импульса
volatile bool g_ImpulsePhase=LOW;// 1- время высокого, 0 -время низкого
volatile unsigned long g_InterruptCounter; // Счетчик прерываний
volatile unsigned long g_ImpulseCounter=MAX_UnsignedLong;// Счетчик импульсов
float FtIC=59000.0; //Частота появления прерываний таймера
//Progressbar
unsigned long NImpPcharProgressbar; //Кол-во импульсов на один символ прогрессбара
volatile unsigned long CImpPcharProgressbar;// Счетчик импульсов прохождения одного символа в прогрессбаре
volatile byte CharPosInProgressbar;// Char postion in progressbar
//Progress time
const int T_loopdelay=50;//number of milliseconds of delay in the loop
int N_Refresh1min=ceil(60000.0/Period_Refresh);//number of loops to complete one minute
int C_Refresh1min;
byte HH_trevel,MM_trevel;
byte HH_left,MM_left;
unsigned long Millis_start;
//******************************************************************
inline void GenStart(){
//******************************************************************  
#ifdef _DEBUG_GEN_CALC
Debugln("GenStart");
#endif
g_InterruptCounter=0;
CImpPcharProgressbar=NImpPcharProgressbar;
Millis_start=millis();
C_Refresh1min=N_Refresh1min;
NextMillisCheck=millis()+Period_Refresh;
gEnable=true; 
}
//******************************************************************  
inline void GenStop(){
//******************************************************************  
#ifdef _DEBUG_GEN_CALC
Debugln("GenStop");
#endif
gEnable=false;
g_ImpulsePhase=LOW;
digitalWrite(GEN_PIN, LOW);
}
//******************************************************************  
void GenTimerInit(){
//******************************************************************    
pinMode(GEN_PIN, OUTPUT);
//pinMode(GEN_LED_PIN, OUTPUT);
//Set timer2
//- остановка таймера,
TCCR2A = 0;
TCCR2B = 0;
TIFR2=(1<<OCF2B)|(1<<OCF2A)|(1<< TOV2);// Сброс флагов прерываний
ASSR|= (0<<AS2 ); // clk timer от внутреннего генератора CLK
TIMSK2|=(1<<TOIE2);// Разрешени прерывания TOV
//- задание режима Normal в TCCR без старта,
TCCR2A |= (0<<COM2A1) || (0<<COM2A0) | (0<< COM2B1)| (0<< COM2B0)| (0<< WGM21)|(0<< WGM20);
//TCCR2B |= (1<<FOC2A)| (1<<FOC2B)|(0<<WGM22)|(0<<CS22)|(1<<CS21)|(0<<CS20); // Prescal / 8
//TCCR2B |= (1<<FOC2A)| (1<<FOC2B)|(0<<WGM22)|(0<<CS22)|(1<<CS21)|(1<<CS20); // Prescal / 32
TCCR2B |= (1<<FOC2A)| (1<<FOC2B)|(0<<WGM22)|(0<<CS22)|(0<<CS21)|(1<<CS20); // Prescal no prescaling
GTCCR|=(1<<PSRASY); //Reset Prescaler. В о з можно это и не нужно  
}
//******************************************************************
void GenSet(){
//******************************************************************  
GenStop();
FtIC=(float)g_Fclk / 256.0;//Частота появления прерываний таймера
unsigned int TintCount=ceil(3600.0 * FtIC / (float)Profile.Velocity / (float)Profile.Pulse1km);//количество прерываний для верхнего уровня импульса
g_timerIntCntH=ceil( (float)((unsigned long)TintCount * (unsigned long)Profile.PulseDuty) / 100.0    ) ;
if (TintCount>g_timerIntCntH) g_timerIntCntL=TintCount-g_timerIntCntH;else g_timerIntCntL=1;//количество прерываний для нижнего уровня импульса
g_ImpulseCounter=(unsigned long)Profile.Mileage * (unsigned long)Profile.Pulse1km;//количество импульсов для прохождения пути
//Progress time
int Tmin_trevel=ceil((float)(60*Profile.Mileage)/(float)Profile.Velocity);
if (Tmin_trevel==0) Tmin_trevel=1;
HH_trevel=floor((float)Profile.Mileage/(float)Profile.Velocity);
MM_trevel=Tmin_trevel-60*HH_trevel;
HH_left=HH_trevel;
MM_left=MM_trevel;
//Progressbar
NImpPcharProgressbar=floor(g_ImpulseCounter/(unsigned long)LCD_COLS);//Impulse per char in progressbar
CImpPcharProgressbar=0;//Counter chars position in string progressbar
CharPosInProgressbar=0;//Postion char in string progressbar
#ifdef _DEBUG_PROGRSSBAR
Debug("g_ImpulseCounter=");Serial.println(g_ImpulseCounter);
Debugln("NImpPcharProgressbar=%l",NImpPcharProgressbar);
Debugln("CImpPcharProgressbar=%l",CImpPcharProgressbar);
Debugln("CharPosInProgressbar=%d",CharPosInProgressbar);
#endif 
#ifdef _DEBUG_GEN_CALC
DebugFloat("FtIC=%s\n",FtIC,10,1);
Debugln("----");
Debugln("Time=%d",millis());
Debugln("TintCount=%u",TintCount);
Debugln("g_timerIntCntH=%u",g_timerIntCntH);
Debugln("g_timerIntCntL=%u",g_timerIntCntL);
Debugln("g_ImpulseCounter=%u",g_ImpulseCounter);
#endif 
GenStart();
}
//******************************************************************
ISR(TIMER2_OVF_vect){ // Interrupt Service Routines (ISR)
//******************************************************************  
#ifdef  _DEBUG_GEN
dInterruptCounter++;
#endif
if (!gEnable)return;
g_InterruptCounter++;
if (g_ImpulsePhase)
  {
  if (g_InterruptCounter == g_timerIntCntH)
    {
    g_ImpulsePhase=LOW;  
    g_InterruptCounter=0;
    digitalWrite(GEN_PIN, LOW);  
    }
  }
else
  {    
  if (g_InterruptCounter == g_timerIntCntL)    
    {
    g_ImpulsePhase=HIGH;  
    g_InterruptCounter=0;
    g_ImpulseCounter--;      
    if (g_ImpulseCounter==0)
      {GenStop();}
    else
      {
      digitalWrite(GEN_PIN, HIGH);
      }
    CImpPcharProgressbar--;
    if(CImpPcharProgressbar==0)
      {
      CImpPcharProgressbar=NImpPcharProgressbar;
      CharPosInProgressbar++;       
      }
    } 
  }
}
