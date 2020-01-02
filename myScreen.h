#include "EditField.h"
#define MAX_MENU_ITEM  5
struct MyMenuItem {
  public:
  byte Col;  
  byte Row;
  void (*Action)(byte); //https://www.eskimo.com/~scs/cclass/int/sx10a.html
};
class MyMenu {
  public:
  byte ItemsCount;
  byte SelectedItem=0;     
  MyMenuItem Items[5]; 
  void GotoNext(void); 
  void GotoPrevious(void);
  void Show(void); 
};
void MyMenu::GotoNext(void){
SelectedItem++;  
if (SelectedItem==ItemsCount)SelectedItem=0;
Buttton[BUTTON_RIGHT].Value=false;  
Buttton[BUTTON_RIGHT].Block=true;
Show();
}
void MyMenu::GotoPrevious(void){
SelectedItem--;  
if (SelectedItem==255)SelectedItem=ItemsCount-1;
Buttton[BUTTON_LEFT].Value=false;  
Buttton[BUTTON_LEFT].Block=true;
Show();
}

void MyMenu::Show(void){
lcd.setCursor(Items[SelectedItem].Col,Items[SelectedItem].Row);
lcd.blink();        
}
//******************************************************************
class MyField{
  public:
  byte Type;//0-char,byte,1-int,2-Float,Double,3-String 
  byte Col;
  byte Row;
  byte Width;
  //char Format[8];
  void* Value; 
  void Show(void); 
};
void MyField::Show(void){//http://www.cplusplus.com/reference/cstdio/printf/
char buff[16]; 
char Format[8];//https://arduinomaster.ru/program/arduino-string-stroki/
switch ( Type ) {
case 0:
  sprintf(Format,"%%%uu",Width);  
  sprintf(buff,Format,*(byte*)Value);
  break;
case 1:
  sprintf(Format,"%%%uu",Width);  
  sprintf(buff,Format,*(int*)Value);
  break;
case 2:  
  //dtostrf(floatVar, minStringWidthIncDecimalPoint, numVarsAfterDecimal, charBuf);
  dtostrf(*(float*)Value, Width, 1, buff);    
  break;    
default:
  sprintf(buff,"%3d",*(byte*)Value);
  break;
}
lcd.setCursor(Col,Row);
lcd.print(buff);  
}
//******************************************************************
class MyScreen{
  public:  
  //String  *Rows[LCD_ROWS];
  char* Rows[LCD_ROWS];
  MyMenu Menu;
  byte FieldsCount;
  MyField Fields[6];
  void Show(void); 
  };
void MyScreen::Show(void){
lcd.clear();
for (byte r=0;r!=LCD_ROWS;r++)
  {
  lcd.setCursor(0, r);
  //char Fch;
  for (byte c = 0; c != LCD_COLS; c++)
  {
    //Fch =  pgm_read_byte_near(Rows[r] + c);
    //lcd.write(Fch);
    lcd.write(pgm_read_byte_near(Rows[r] + c));
  }
  for (int f=0;f!=FieldsCount;f++)
    Fields[f].Show();
  Menu.Show();
  }
if (Menu.ItemsCount>0)
  {
  //lcd.setCursor(Screen.MenuItemPosition[Screen.curMenuItem][0],Screen.MenuItemPosition[Screen->curMenuItem][1]);
  lcd.blink();
  }  
for (byte i=0;i!=BUTTON_PIN_COUNT;i++)Buttton[i].Block=false;
}
//******************************************************************      
#define MAX_SCREENS 16
class MyScreens{
  public:  
  int current=-1;
  MyScreen *Screens[MAX_SCREENS];  
  void Add(MyScreen *Screen);
};
void MyScreens::Add(MyScreen *Screen){
current++;  
Screens[current]=Screen;
Screen->Show();
}
MyScreens ScreenManager;

//******************************************************************
void CreateEdit(){
//******************************************************************
}


//******************************************************************
void LoopScreen(){
//******************************************************************
/*if (Screen->Menu.ItemCount>0)
  {
    if (Buttton[BUTTON_LEFT].Value)
    {
    Buttton[BUTTON_LEFT].Value=false;  
    Buttton[BUTTON_LEFT].Block=true;
    Screen->curMenuItem--;  
    if (Screen->curMenuItem==255)Screen->curMenuItem=Screen->Menu.ItemCount-1;
    //lcd.setCursor(Screen->MenuItemPosition[Screen->curMenuItem][0],Screen->MenuItemPosition[Screen->curMenuItem][1]);
    lcd.blink();    
    }
    if (Buttton[BUTTON_RIGHT].Value)
    {
    Buttton[BUTTON_RIGHT].Value=false;  
    Buttton[BUTTON_RIGHT].Block=true;
    Screen->curMenuItem++;  
    if (Screen->curMenuItem==Screen->Menu.ItemCount)Screen->curMenuItem=0;
    //lcd.setCursor(Screen.MenuItemPosition[Screen->curMenuItem][0],Screen->MenuItemPosition[Screen->curMenuItem][1]);
    lcd.blink();    
    }
    if (Buttton[BUTTON_ESC].Value)
    {
    Buttton[BUTTON_ESC].Value=false;  
    Buttton[BUTTON_ESC].Block=true;
    if (Screen->PreviousScreen!=0)
      CreateScreen(Screen->PreviousScreen);
    }
    if (Buttton[BUTTON_ENTER].Value)
    {
    Buttton[BUTTON_ENTER].Value=false;  
    Buttton[BUTTON_ENTER].Block=true;        
    }
  }*/
}  
//******************************************************************
void KBroutine_Menu()
//******************************************************************
{
}
//******************************************************************
void KBroutine_Edit()
//******************************************************************
{
 /*if (Buttton[BUTTON_LEFT].Value)
    {
    Buttton[BUTTON_LEFT].Value=false;  
    Buttton[BUTTON_LEFT].Block=true;
    Screen->curMenuItem--;  
    if (Screen->curMenuItem==255)Screen->curMenuItem=Screen->Menu.ItemCount-1;
    //lcd.setCursor(Screen->MenuItemPosition[Screen->curMenuItem][0],Screen->MenuItemPosition[Screen->curMenuItem][1]);
    lcd.blink();    
    }
    if (Buttton[BUTTON_RIGHT].Value)
    {
    Buttton[BUTTON_RIGHT].Value=false;  
    Buttton[BUTTON_RIGHT].Block=true;
    Screen->curMenuItem++;  
    //if (Screen.curMenuItem==Screen->Menu.ItemCount)Screen->curMenuItem=0;
    //lcd.setCursor(Screen->MenuItemPosition[Screen->curMenuItem][0],Screen->MenuItemPosition[Screen->curMenuItem][1]);
    lcd.blink();    
    }
    if (Buttton[BUTTON_ESC].Value)
    {
    Buttton[BUTTON_ESC].Value=false;  
    Buttton[BUTTON_ESC].Block=true;
    if (Screen->PreviousScreen!=0)
      CreateScreen(Screen->PreviousScreen);
    }
    if (Buttton[BUTTON_ENTER].Value)
    {
    Buttton[BUTTON_ENTER].Value=false;  
    Buttton[BUTTON_ENTER].Block=true;        
    }*/
}



/*
Pointers to Functions. http://mypractic.com/lesson-15-pointers-in-c-for-arduino-conversion-of-different-data-types-to-bytes/

*/
