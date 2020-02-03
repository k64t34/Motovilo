#define ScreenAdjustmentIndex 1
#define NAMESPACE ScreenAdjustment
#define SCREENROW1  "     Adjustment     "
#define SCREENROW2  "U-=___ V  1Km=____\xa2L"
#define SCREENROW3  "U_=___ V  V=___Km/h "
#define SCREENROW4  "Kd=__%              "
//struct MyField{  
//   byte Type ;//0-char,1-int,2-Float,Double,3-String,4-byte 
//   byte Col ;
//   byte Row ;
//   byte Width ;
//   byte Decimal;
//   byte Action ; //0-Change Screen, 1-Edit
//   byte ActionData PROGMEM; //Action=0 => ActionData=Index Change Screen
//  //char Format[8];
//  void* Value;   
//  void* minValue 
//  void* maxValue 
//};  
#define FLD_COUNT 5

#define FLD1_TYPE 2  
#define FLD1_COL  3
#define FLD1_ROW  1
#define FLD1_WIDTH  3
#define FLD1_DECIMAL  1
#define FLD1_ACTION   2
#define FLD1_ACTIONDATA 0
#define FLD1_VALUE   &Profile.PulseVoltageHigh 
#define FLD1_MINVALUE &FLD_FLOAT_MINVALUE_5 
#define FLD1_MAXVALUE &FLD_FLOAT_MAXVALUE_9 

#define FLD2_TYPE 2  
#define FLD2_COL  3
#define FLD2_ROW  2
#define FLD2_WIDTH  3
#define FLD2_DECIMAL  1
#define FLD2_ACTION   2
#define FLD2_ACTIONDATA 0
#define FLD2_VALUE   &Profile.PulseVoltageLow 
#define FLD2_MINVALUE &FLD_FLOAT_MINVALUE_ZERO 
#define FLD2_MAXVALUE &FLD_FLOAT_MAXVALUE_1 

#define FLD3_TYPE 4  
#define FLD3_COL  3
#define FLD3_ROW  3
#define FLD3_WIDTH  2
#define FLD3_DECIMAL  0
#define FLD3_ACTION   2
#define FLD3_ACTIONDATA 0
#define FLD3_VALUE   &Profile.PulseDuty 
#define FLD3_MINVALUE &FLD_BYTE_MINVALUE_ONE 
#define FLD3_MAXVALUE &FLD_BYTE_MAXVALUE_99 

#define FLD4_TYPE 1  
#define FLD4_COL  14
#define FLD4_ROW  1
#define FLD4_WIDTH  4
#define FLD4_DECIMAL  0
#define FLD4_ACTION   2
#define FLD4_ACTIONDATA 0
#define FLD4_VALUE   &Profile.Pulse1km 
#define FLD4_MINVALUE &FLD_INT_MINVALUE_ONE 
#define FLD4_MAXVALUE &FLD_INT_MAXVALUE_10000 

#define FLD5_TYPE 4  
#define FLD5_COL  12
#define FLD5_ROW  2
#define FLD5_WIDTH  3
#define FLD5_DECIMAL  0
#define FLD5_ACTION   2
#define FLD5_ACTIONDATA 0
#define FLD5_VALUE   &Profile.Velocity 
#define FLD5_MINVALUE &FLD_BYTE_MINVALUE_ONE 
#define FLD5_MAXVALUE &FLD_BYTE_MAXVALUE_255 

namespace NAMESPACE
{
const char Rows[LCD_ROWS][LCD_COLS] PROGMEM ={SCREENROW1,SCREENROW2,SCREENROW3,SCREENROW4};
const MyField Fields[FLD_COUNT]
#if FLD_COUNT>0
 ={{FLD1_TYPE,FLD1_COL,FLD1_ROW,FLD1_WIDTH,FLD1_DECIMAL,FLD1_ACTION,FLD1_ACTIONDATA,FLD1_VALUE,FLD1_MINVALUE,FLD1_MAXVALUE} 
#if FLD_COUNT>1
,{FLD2_TYPE,FLD2_COL,FLD2_ROW,FLD2_WIDTH,FLD2_DECIMAL,FLD2_ACTION,FLD2_ACTIONDATA,FLD2_VALUE,FLD2_MINVALUE,FLD2_MAXVALUE}
#if FLD_COUNT>2
,{FLD3_TYPE,FLD3_COL,FLD3_ROW,FLD3_WIDTH,FLD3_DECIMAL,FLD3_ACTION,FLD3_ACTIONDATA,FLD3_VALUE,FLD3_MINVALUE,FLD3_MAXVALUE}
#if FLD_COUNT>3
,{FLD4_TYPE,FLD4_COL,FLD4_ROW,FLD4_WIDTH,FLD4_DECIMAL,FLD4_ACTION,FLD4_ACTIONDATA,FLD4_VALUE,FLD4_MINVALUE,FLD4_MAXVALUE}
#if FLD_COUNT>4
,{FLD5_TYPE,FLD5_COL,FLD5_ROW,FLD5_WIDTH,FLD5_DECIMAL,FLD5_ACTION,FLD5_ACTIONDATA,FLD5_VALUE,FLD5_MINVALUE,FLD5_MAXVALUE}
#endif
#endif
#endif
#endif
}
#endif
;

MyScreen Screen = {.Rows=(char*)Rows,.FieldsCount=FLD_COUNT,.Fields=Fields,.KB_mode=KB_MODE_ARROW};
}//end namespace

#undef SCREENROW1
#undef SCREENROW2
#undef SCREENROW3
#undef SCREENROW4
#undef NAMESPACE
#undef FLD_COUNT 

#undef FLD1_TYPE  
#undef FLD1_COL  
#undef FLD1_ROW  
#undef FLD1_WIDTH  
#undef FLD1_DECIMAL  
#undef FLD1_VALUE   
#undef FLD1_ACTION 
#undef FLD1_ACTIONDATA 
#undef FLD1_MINVALUE 
#undef FLD1_MAXVALUE 

#undef FLD2_TYPE  
#undef FLD2_COL  
#undef FLD2_ROW  
#undef FLD2_WIDTH  
#undef FLD2_DECIMAL  
#undef FLD2_VALUE   
#undef FLD2_ACTION  
#undef FLD2_ACTIONDATA 
#undef FLD2_MINVALUE 
#undef FLD2_MAXVALUE 

#undef FLD3_TYPE  
#undef FLD3_COL  
#undef FLD3_ROW  
#undef FLD3_WIDTH  
#undef FLD3_DECIMAL  
#undef FLD3_VALUE   
#undef FLD3_ACTION  
#undef FLD3_ACTIONDATA 
#undef FLD3_MINVALUE 
#undef FLD3_MAXVALUE 

#undef FLD4_TYPE  
#undef FLD4_COL  
#undef FLD4_ROW  
#undef FLD4_WIDTH  
#undef FLD4_DECIMAL  
#undef FLD4_VALUE   
#undef FLD4_ACTION  
#undef FLD4_ACTIONDATA 
#undef FLD4_MINVALUE 
#undef FLD4_MAXVALUE 

#undef FLD5_TYPE  
#undef FLD5_COL  
#undef FLD5_ROW  
#undef FLD5_WIDTH  
#undef FLD5_DECIMAL  
#undef FLD5_VALUE   
#undef FLD5_ACTION  
#undef FLD5_ACTIONDATA 
#undef FLD5_MINVALUE 
#undef FLD5_MAXVALUE 
