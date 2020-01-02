MyScreen ScreenAdjustment;
/*={  
{"     Adjustment",
"Uh=5.1 V  1Km=____",
"Ul=___ V  V=___Km/h",
"Kd=__%    d=_____"
},
5,
{{0,1},  
{0,2},
{0,3},
{10,1},
{10,2}},
0,
0
};*/
const char ScreenAdjustmentRow0[LCD_COLS] PROGMEM ="     Adjustment     ";
const char ScreenAdjustmentRow1[LCD_COLS] PROGMEM ="Uh=___ V  1Km=____im";
const char ScreenAdjustmentRow2[LCD_COLS] PROGMEM ="Ul=___ V  V=___Km/h ";
const char ScreenAdjustmentRow3[LCD_COLS] PROGMEM ="Kd=__%    d=___     ";
//******************************************************************
ScreenAdjustmentEditField(byte Item){
//******************************************************************  
EditField.Col=ScreenAdjustment.Fields[Item].Col;
EditField.Row=ScreenAdjustment.Fields[Item].Row;
EditField.Width=ScreenAdjustment.Fields[Item].Width;
//ScreenAdjustment.Fields[4].Type=0;
EditField.OldValue=&ScreenAdjustment.Fields[Item].Value;
EditField.Show();
}
//******************************************************************
ScreenAdjustmentInit(){
//******************************************************************  
ScreenAdjustment.FieldsCount=5;
ScreenAdjustment.Fields[0].Col=3;
ScreenAdjustment.Fields[0].Row=1;
ScreenAdjustment.Fields[0].Width=3;
ScreenAdjustment.Fields[0].Type=2;
ScreenAdjustment.Fields[0].Value=&Profile1.PulseVoltageHigh;
ScreenAdjustment.Fields[1].Col=3;
ScreenAdjustment.Fields[1].Row=2;
ScreenAdjustment.Fields[1].Width=3;
ScreenAdjustment.Fields[1].Type=2;
ScreenAdjustment.Fields[1].Value=&Profile1.PulseVoltageLow;
ScreenAdjustment.Fields[2].Col=3;
ScreenAdjustment.Fields[2].Row=3;
ScreenAdjustment.Fields[2].Width=2;
ScreenAdjustment.Fields[2].Type=0;
ScreenAdjustment.Fields[2].Value=&Profile1.PulseDuty;
ScreenAdjustment.Fields[3].Col=14;
ScreenAdjustment.Fields[3].Row=1;
ScreenAdjustment.Fields[3].Width=4;
ScreenAdjustment.Fields[3].Type=1;
ScreenAdjustment.Fields[3].Value=&Profile1.Pulse1km;
ScreenAdjustment.Fields[4].Col=12;
ScreenAdjustment.Fields[4].Row=2;
ScreenAdjustment.Fields[4].Width=3;
ScreenAdjustment.Fields[4].Type=0;
ScreenAdjustment.Fields[4].Value=&Profile1.Velocity;

ScreenAdjustment.Rows[0]=ScreenAdjustmentRow0; 
ScreenAdjustment.Rows[1]=ScreenAdjustmentRow1; 
ScreenAdjustment.Rows[2]=ScreenAdjustmentRow2; 
ScreenAdjustment.Rows[3]=ScreenAdjustmentRow3; 
ScreenAdjustment.Menu.ItemsCount=5;
ScreenAdjustment.Menu.Items[0].Col=0;
ScreenAdjustment.Menu.Items[0].Row=1;
ScreenAdjustment.Menu.Items[0].Action=&ScreenAdjustmentEditField;
ScreenAdjustment.Menu.Items[1].Col=0;
ScreenAdjustment.Menu.Items[1].Row=2;
ScreenAdjustment.Menu.Items[1].Action=&ScreenAdjustmentEditField;
ScreenAdjustment.Menu.Items[2].Col=0;
ScreenAdjustment.Menu.Items[2].Row=3;
ScreenAdjustment.Menu.Items[2].Action=&ScreenAdjustmentEditField;
ScreenAdjustment.Menu.Items[3].Col=10;
ScreenAdjustment.Menu.Items[3].Row=1;
ScreenAdjustment.Menu.Items[3].Action=&ScreenAdjustmentEditField;
ScreenAdjustment.Menu.Items[4].Col=10;
ScreenAdjustment.Menu.Items[4].Row=2;
ScreenAdjustment.Menu.Items[4].Action=&ScreenAdjustmentEditField;
}
