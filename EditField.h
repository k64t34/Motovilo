ShowFieldInt(byte Row,byte Col,byte Width,int Value){
lcd.setCursor(Col,Row);
lcd.print(Value);
}
class MyEditFieldInt{
  public:
  bool Enable=false;
  byte Row;
  byte Col;
  byte Width;
  byte Decimal;
  byte Delta;
  int  OldValue;
  byte NewValue[4];
  byte EditByte;
  void NextByteValue(void);
  void IncreaseValue(void);
  void ReduceValue(void);
  void Exit(void);
  void Save(void);
  void Show(void);
  };
void MyEditFieldInt::Show(void){
 itoa(OldValue, NewValue, 10);
 lcd.setCursor(Col,Row);
 for ( byte c=0;c!=Width;c++)
  lcd.write(NewValue[c]);
 lcd.setCursor(Col,Row); 
 Enable=true;   
}



void MyEditFieldInt::Exit(void){
Enable=false;  
}
void MyEditFieldInt::Save(void){
Enable=false;  
}

void MyEditFieldInt::IncreaseValue(void){
  
}
void MyEditFieldInt::ReduceValue(void){
  
}
void MyEditFieldInt::NextByteValue(void){
  
}

  
MyEditFieldInt EditField;
