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
    switch (Field->Type )
      {
      case 0:
        *(byte*)Field->Value=atoi(NewValue);
        break;
      case 1:
        *(int*)Field->Value=atoi(NewValue);
        break;
      case 2:  
        *(float*)Field->Value=atof(NewValue);
        break;    
      default:    
        break;
      }       
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
