#define MAX_EDITFIELD_WIDTH 5 // +1 for EOL;
class MyEditFieldInt{
  public:
  bool EditMode=false;
  MyField* Field;
  byte Delta;  
  byte NewValue[MAX_EDITFIELD_WIDTH];
  byte SelectedByte;
  //void ByteValue(void);
  inline void IncreaseValue(void);
  inline void ReduceValue(void);
  inline void Exit(void);
  inline void Save(void);
  inline void Show(MyField*);
  inline void Loop(short);
  };
void MyEditFieldInt::Show(MyField* pField){
Field=pField;
//if (Field->Type==0)itoa(*(byte*)Field->Value, NewValue, 10);
//else if(Field->Type==1)  itoa(*(int*)Field->Value, NewValue, 10);
FldStrValue(NewValue,Field);
SelectedByte=0; 
lcd.setCursor(Field->Col,Field->Row);
byte c=0;
for (;c!=Field->Width;c++)
  {
  if (NewValue[c]==' ')NewValue[c]='0';
  lcd.write(NewValue[c]);
  }
for (;c!=MAX_EDITFIELD_WIDTH;c++)NewValue[c]=0;  
lcd.setCursor(Field->Col,Field->Row);
}//***********************************
void MyEditFieldInt::Loop(short Key){
if (Key==KEY_RIGHT)     IncreaseValue();
else if (Key==KEY_LEFT) ReduceValue(); 
else if (Key==KEY_ENTER)Save();
else if (Key==KEY_ESC) Exit();  
}//************************************
void MyEditFieldInt::Exit(void){
EditMode=false;  
lcd.setCursor(Field->Col,Field->Row);
char buff[8];
FldStrValue(buff,Field);
lcd.print(buff);  
lcd.setCursor(Field->Col-1+Field->Width,Field->Row);
//lcd.blink(); 
}//*************************************
void MyEditFieldInt::Save(void){
SelectedByte++;
if (NewValue[SelectedByte]=='.') Save();
else 
{
  if (SelectedByte==Field->Width)
    {
    #ifdef _DEBUG_PROFILE
    Debugln("Field->Type=%i",Field->Type);
    #endif
    switch (Field->Type )
      {
      case 0:{
         byte bNewValue=atoi(NewValue);          
         byte minValue = pgm_read_byte(Field->minValue);
         byte maxValue = pgm_read_byte(Field->maxValue);
         #ifdef _DEBUG_PROFILE
         Debug("NewValue=");Debugln(NewValue);
         Debugln("bNewValue=%i",bNewValue);
         Debugln("maxValue=%i",maxValue);
         Debugln("minValue=%i",minValue);         
         #endif
         if (bNewValue > maxValue)bNewValue=maxValue;
         else if (bNewValue < minValue)bNewValue=minValue;          
         *(byte*)Field->Value=bNewValue;
        }break;
      case 1:{
         int iNewValue=atoi(NewValue);
         int minValue = pgm_read_word(Field->minValue);
         int maxValue = pgm_read_word(Field->maxValue);
         #ifdef _DEBUG_PROFILE
         Debugln("NewValue=%s",NewValue);
         Debugln("iNewValue=%i",iNewValue);
         Debugln("maxValue=%i",maxValue);
         Debugln("minValue=%i",minValue);         
         #endif
         if (iNewValue > maxValue)     iNewValue=maxValue;
         else if (iNewValue < minValue)iNewValue=minValue;                  
         *(int*)Field->Value=iNewValue;
        }break;
      case 2: {           
         float fNewValue=atof(NewValue);
         float minValue = pgm_read_float(Field->minValue);
         float maxValue = pgm_read_float(Field->maxValue);
         #ifdef _DEBUG_PROFILE
         Debug("NewValue=");Debugln(NewValue);         
         DebugFloat("fNewValue=%s\n",fNewValue,Field->Width,Field->Decimal);
         DebugFloat("maxValue=%s\n",maxValue,Field->Width,Field->Decimal);         
         DebugFloat("minValue=%s\n",minValue,Field->Width,Field->Decimal);                           
         #endif
         if (fNewValue > maxValue) fNewValue=maxValue;
         else if (fNewValue < minValue)fNewValue=minValue;                  
         *(float*)Field->Value=fNewValue;        
        }break;    
      default: { 
         #ifdef _DEBUG_PROFILE
         Debugln("default");
         #endif  
        }break;
      }       
    GenSet();  
    Exit();
    }
  else
    {
    lcd.setCursor(Field->Col+SelectedByte,Field->Row);
    } 
}     
}//************************************
void MyEditFieldInt::IncreaseValue(void){
if (NewValue[SelectedByte]=='9')NewValue[SelectedByte]='0';
else NewValue[SelectedByte]++; 
lcd.write(NewValue[SelectedByte]);
lcd.setCursor(Field->Col+SelectedByte,Field->Row);
}//************************************
void MyEditFieldInt::ReduceValue(void){
if (NewValue[SelectedByte]=='0')NewValue[SelectedByte]='9';
else NewValue[SelectedByte]--; 
lcd.write(NewValue[SelectedByte]);
lcd.setCursor(Field->Col+SelectedByte,Field->Row);
}//************************************
//void MyEditFieldInt::NextByteValue(void){}

  
MyEditFieldInt EditField;
