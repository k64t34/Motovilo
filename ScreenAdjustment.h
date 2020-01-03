#define NAMESPACE ScreenAdjustment
#define SCREENROW1  "     Adjustment     "
#define SCREENROW2  "U-=___ V  1Km=____|L"
#define SCREENROW3  "U_=___ V  V=___Km/h "
#define SCREENROW4  "Kd=__%              "

//struct MyField{  
//   byte Type ;//0-char,byte,1-int,2-Float,Double,3-String 
//   byte Col ;
//   byte Row ;
//   byte Width ;
//   byte Decimal;
//   byte Action ; //0-Change Screen, 1-Edit
//   byte ActionData PROGMEM; //Action=0 => ActionData=Index Change Screen
//  //char Format[8];
//  void* Value;   
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

#define FLD2_TYPE 2  
#define FLD2_COL  3
#define FLD2_ROW  2
#define FLD2_WIDTH  3
#define FLD2_DECIMAL  1
#define FLD2_ACTION   2
#define FLD2_ACTIONDATA 0
#define FLD2_VALUE   &Profile.PulseVoltageLow 

#define FLD3_TYPE 0  
#define FLD3_COL  3
#define FLD3_ROW  3
#define FLD3_WIDTH  2
#define FLD3_DECIMAL  0
#define FLD3_ACTION   2
#define FLD3_ACTIONDATA 0
#define FLD3_VALUE   &Profile.PulseDuty 

#define FLD4_TYPE 1  
#define FLD4_COL  14
#define FLD4_ROW  1
#define FLD4_WIDTH  4
#define FLD4_DECIMAL  0
#define FLD4_ACTION   2
#define FLD4_ACTIONDATA 0
#define FLD4_VALUE   &Profile.Pulse1km 

#define FLD5_TYPE 0  
#define FLD5_COL  12
#define FLD5_ROW  2
#define FLD5_WIDTH  3
#define FLD5_DECIMAL  0
#define FLD5_ACTION   2
#define FLD5_ACTIONDATA 0
#define FLD5_VALUE   &Profile.Velocity 

namespace NAMESPACE
{
const char Rows[LCD_ROWS][LCD_COLS] PROGMEM ={SCREENROW1,SCREENROW2,SCREENROW3,SCREENROW4};
const MyField Fields[FLD_COUNT]
#if FLD_COUNT>0
 ={{FLD1_TYPE,FLD1_COL,FLD1_ROW,FLD1_WIDTH,FLD1_DECIMAL,FLD1_ACTION,FLD1_ACTIONDATA,FLD1_VALUE} 
#if FLD_COUNT>1
,{FLD2_TYPE,FLD2_COL,FLD2_ROW,FLD2_WIDTH,FLD2_DECIMAL,FLD2_ACTION,FLD2_ACTIONDATA,FLD2_VALUE}
#if FLD_COUNT>2
,{FLD3_TYPE,FLD3_COL,FLD3_ROW,FLD3_WIDTH,FLD3_DECIMAL,FLD3_ACTION,FLD3_ACTIONDATA,FLD3_VALUE}
#if FLD_COUNT>3
,{FLD4_TYPE,FLD4_COL,FLD4_ROW,FLD4_WIDTH,FLD4_DECIMAL,FLD4_ACTION,FLD4_ACTIONDATA,FLD4_VALUE}
#if FLD_COUNT>4
,{FLD5_TYPE,FLD5_COL,FLD5_ROW,FLD5_WIDTH,FLD5_DECIMAL,FLD5_ACTION,FLD5_ACTIONDATA,FLD5_VALUE}
#endif
#endif
#endif
#endif
}
#endif
;

MyScreen Screen = {.Rows=(char*)Rows,.FieldsCount=FLD_COUNT,.Fields=Fields};
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
#undef FLD2_TYPE  
#undef FLD2_COL  
#undef FLD2_ROW  
#undef FLD2_WIDTH  
#undef FLD2_DECIMAL  
#undef FLD2_VALUE   
#undef FLD2_ACTION  
#undef FLD2_ACTIONDATA 
#undef FLD3_TYPE  
#undef FLD3_COL  
#undef FLD3_ROW  
#undef FLD3_WIDTH  
#undef FLD3_DECIMAL  
#undef FLD3_VALUE   
#undef FLD3_ACTION  
#undef FLD3_ACTIONDATA 
