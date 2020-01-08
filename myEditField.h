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
    #ifdef _DEBUG
    Debugln("Field->Type=%i",Field->Type);
    #endif
    switch (Field->Type )
      {
      case 0:{
         byte bNewValue=atoi(NewValue);
         #ifdef _DEBUG
         Debug("NewValue=");Debugln(NewValue);
         Debugln("bNewValue=%i",bNewValue);
         Debugln("maxValue=%i",*(byte*)Field->maxValue);
         Debugln("minValue=%i",*(byte*)Field->minValue);         
         #endif
         if (bNewValue > *(byte*)Field->maxValue)bNewValue=*(byte*)Field->maxValue;
         else if (bNewValue < *(byte*)Field->minValue)bNewValue=*(byte*)Field->minValue;          
         *(byte*)Field->Value=bNewValue;
        }break;
      case 1:{
         int iNewValue=atoi(NewValue);
         #ifdef _DEBUG
         Debugln("NewValue=%s",NewValue);
         Debugln("iNewValue=%i",iNewValue);
         Debugln("maxValue=%i",*(int*)Field->maxValue);
         Debugln("minValue=%i",*(int*)Field->minValue);         
         #endif
         if (iNewValue > *(int*)Field->maxValue)     iNewValue=*(int*)Field->maxValue;
         else if (iNewValue < *(int*)Field->minValue)iNewValue=*(int*)Field->minValue;                  
         *(int*)Field->Value=iNewValue;
        }break;
      case 2: {
         #ifdef _DEBUG
         Debugln("case 2");
         #endif   
         float fNewValue=atof(NewValue);
         #ifdef _DEBUG
         Debug("NewValue=");Debugln(NewValue);         
         DebugFloat("fNewValue=%s\n",fNewValue,Field->Width,Field->Decimal);
         DebugFloat("maxValue=%s\n",*(float*)Field->maxValue,Field->Width,Field->Decimal);         
         DebugFloat("minValue=%s\n",*(float*)Field->minValue,Field->Width,Field->Decimal);                           
         #endif
         if (fNewValue > *(float*)Field->maxValue) fNewValue=*(float*)Field->maxValue;
         else if (fNewValue < *(float*)Field->minValue)fNewValue=*(float*)Field->minValue;                  
         *(float*)Field->Value=fNewValue;        
        }break;    
      default: { 
         #ifdef _DEBUG
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
