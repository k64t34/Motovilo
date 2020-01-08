//******************************************************************
struct MyField{  
   const byte Type PROGMEM;//0-char,byte,1-int,2-Float,3-String 
   const byte Col PROGMEM ;
   const byte Row PROGMEM ;
   const byte Width PROGMEM ;
   const byte Decimal PROGMEM;
   const byte Action PROGMEM ; //0-noAct, 1-Change Screen, 2-Edit
   const byte ActionData PROGMEM; //Action=0 => ActionData=Index Change Screen
  //char Format[8];
  const void* Value PROGMEM;   //https://www.eskimo.com/~scs/cclass/int/sx10a.html
  const void* minValue PROGMEM;   //https://www.eskimo.com/~scs/cclass/int/sx10a.html
  const void* maxValue PROGMEM;   //https://www.eskimo.com/~scs/cclass/int/sx10a.html
};
void FldStrValue(char* buff,MyField* Field)
{ 
char Format[8];   
switch (Field->Type )
  {
  case 0:
    sprintf(Format,"%%%uu",Field->Width);  
    sprintf(buff,Format,*(byte*)Field->Value);
    break;
  case 1:
    sprintf(Format,"%%%uu",Field->Width);  
    sprintf(buff,Format,*(int*)Field->Value);
    break;
  case 2:  
    //dtostrf(floatVar, minStringWidthIncDecimalPoint, numVarsAfterDecimal, charBuf);
    dtostrf(*(float*)Field->Value, Field->Width, Field->Decimal, buff);    
    break;    
  default:
    sprintf(buff,"%3s",*(byte*)Field->Value);
    break;
  }   
}
#include "myEditField.h"
//******************************************************************
struct MyScreen{  
  const char* Rows PROGMEM;  
  const byte FieldsCount;
  const MyField* Fields;
  byte PreviousScreen;    
  };
//******************************************************************      
#define MAX_SCREENS 1
class MyScreenManager{
  public:  
  int current=-1;
  byte SelectedField;
  const MyScreen *Screens[MAX_SCREENS] PROGMEM;  
  //void Add(MyScreen *Screen);
  void Show(int Item);
  void Loop(short);
  inline void GotoNextField(void);
  inline void GotoPreviousField(void);
  void ActField(void);  
};
void MyScreenManager::ActField(void){//const byte Action PROGMEM ; //0-noAct, 1-Change Screen, 2-Edit
if (Screens[current]->Fields[SelectedField].Action==2)
  { 
  EditField.EditMode=true;  
  EditField.Show(&Screens[current]->Fields[SelectedField]);
  }
}
void MyScreenManager::GotoNextField(void){
SelectedField++;  
if (SelectedField==Screens[current]->FieldsCount)SelectedField=0;
lcd.setCursor(Screens[current]->Fields[SelectedField].Col-1+Screens[current]->Fields[SelectedField].Width,Screens[current]->Fields[SelectedField].Row);
}
void MyScreenManager::GotoPreviousField(void){
SelectedField--;  
if (SelectedField==255)SelectedField=Screens[current]->FieldsCount-1;
lcd.setCursor(Screens[current]->Fields[SelectedField].Col-1+Screens[current]->Fields[SelectedField].Width,Screens[current]->Fields[SelectedField].Row);
}
void MyScreenManager::Loop(short Key){
if (EditField.EditMode) EditField.Loop(Key);
else
if (Key==KEY_RIGHT)     GotoNextField();
else if (Key==KEY_LEFT) GotoPreviousField(); 
else if (Key==KEY_ENTER)ActField();
else if (Key==KEY_ESC) ;
}    
void MyScreenManager::Show(int Item){
current=Item;  
lcd.clear();
char* adr=Screens[Item]->Rows;
for (byte r=0;r!=LCD_ROWS;r++)
  {
  lcd.setCursor(0, r);  
  for (byte c = 0; c != LCD_COLS; c++)
    {
      lcd.write(pgm_read_byte_near(adr));
      adr++;
    }
  } 
char buff[16]; 
for (byte f=0;f!=Screens[current]->FieldsCount;f++)
  {
  lcd.setCursor(Screens[current]->Fields[f].Col,Screens[Item]->Fields[f].Row); 
  FldStrValue(buff,&Screens[current]->Fields[f]);  
  lcd.print(buff);  
  }
if(Screens[Item]->FieldsCount!=0)
  {  
  SelectedField=0;  
  lcd.setCursor(Screens[Item]->Fields[0].Col-1+Screens[Item]->Fields[0].Width,Screens[Item]->Fields[0].Row);
  lcd.blink();   
  }
}
MyScreenManager ScreenManager;
