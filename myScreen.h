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
  const void* Value PROGMEM;    //https://www.eskimo.com/~scs/cclass/int/sx10a.html
  const void* minValue PROGMEM; //https://www.eskimo.com/~scs/cclass/int/sx10a.html
  const void* maxValue PROGMEM; //https://www.eskimo.com/~scs/cclass/int/sx10a.html
};
void FldStrValue(char* buff,MyField* Field){ 
char Format[8];   
switch (Field->Type )
  {
  case 0:          
    sprintf(buff,"%c",*(char*)Field->Value);//http://www.c-cpp.ru/content/printf
    break;
  case 1:
    sprintf(Format,"%%%uu",Field->Width);  
    sprintf(buff,Format,*(int*)Field->Value);
    break;
  case 2:  
    //dtostrf(floatVar, minStringWidthIncDecimalPoint, numVarsAfterDecimal, charBuf);
    dtostrf(*(float*)Field->Value, Field->Width, Field->Decimal, buff);    
    break;    
  case 4:  
    sprintf(Format,"%%%uu",Field->Width);
    sprintf(buff,Format,*(byte*)Field->Value);    
    break;     
  default:
    sprintf(buff,"%s",*(char*)Field->Value);
    break;
  }   
}
#include "myEditField.h"
//******************************************************************
struct MyScreen{  
  const char* Rows PROGMEM;  
  const byte FieldsCount;
  const MyField* Fields;  
  const byte KB_mode;//0 - arrow; 1- digit    
  byte PreviousScreen;  
  void (*Loop)();  
  void (*Load)();  
  void (*Close)();  
  };
#define KB_MODE_ARROW 0
#define KB_MODE_DIGIT 1  
//******************************************************************      
#define MAX_SCREENS 5
class MyScreenManager{
  public:  
  byte current=-1;
  byte SelectedField;
  const MyScreen *Screens[MAX_SCREENS] PROGMEM;  
  //byte PreviousScreen[MAX_SCREENS];
  //void Add(MyScreen *Screen);
  void Show(int Item);
  void Loop(char);
  inline void GotoNextField(void);
  inline void GotoPreviousField(void);
  inline void GotoField(char);
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
}//************************************ 
void MyScreenManager::Loop(char Key){
//************************************  
if (EditField.EditMode) 
  {  
  EditField.Loop(Key);
  }
else if (Screens[current]->KB_mode==KB_MODE_ARROW)
  {  
  if (Key==KEY_RIGHT || Key==KEY_DOWN)   GotoNextField();
  else if (Key==KEY_LEFT || Key==KEY_UP) GotoPreviousField(); 
  else if (Key==KEY_ENTER)ActField();
  else if (Key==KEY_ESC)
    {
      if (Screens[current]->Close!=0)(*Screens[current]->Close)();
      Show(Screens[current]->PreviousScreen);
    }
  }
else if (Screens[current]->KB_mode==KB_MODE_DIGIT) 
  {
  if ('1' <= Key && Key <= '9') 
    {
    GotoField(Key);
    }
  else if (Key==KEY_ENTER) 
    {        
    if (Screens[current]->FieldsCount!=0)
      {
      ((MyScreen*)Screens[Screens[current]->Fields[SelectedField].ActionData])->PreviousScreen=current;
      Show(Screens[current]->Fields[SelectedField].ActionData);   
      }
    }
  else if (Key==KEY_ESC) 
    {
    if (Screens[current]->Close!=0)(*Screens[current]->Close)();
      Show(Screens[current]->PreviousScreen);
    }    
  }
else 
  {
  //if (Screens[current]->Loop!=0)(*Screens[current]->Loop)();  
  }
}//************************************    
void MyScreenManager::GotoField(char Key){
byte ChoosenKey=Key-49;// char '0' has code 48. number = 48 and then minus 1 to alight array index
if (ChoosenKey<Screens[current]->FieldsCount)
SelectedField=ChoosenKey;
lcd.setCursor(Screens[current]->Fields[SelectedField].Col-1+Screens[current]->Fields[SelectedField].Width,Screens[current]->Fields[SelectedField].Row);
}//************************************    
void MyScreenManager::Show(int Item){
//************************************   
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
if (Screens[current]->Load!=nullptr)
  {    
    (*Screens[current]->Load)();  
  }
if (Screens[current]->Loop!=nullptr)
  {
  pRefreshInLoop=Screens[current]->Loop;
  fRefreshInLoop=true;    
  }
else
  {
  fRefreshInLoop=false;
  }
}
MyScreenManager ScreenManager;
