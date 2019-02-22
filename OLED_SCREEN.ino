
void mainpage(){
  int h1 =u8g.getFontAscent()-u8g.getFontDescent();
  u8g.setFont(u8g_font_unifont);
  u8g.setFontPosTop();
  u8g.setColorIndex(1);
  u8g.drawStr( w/8, 20, "Digital Scale");  
  u8g.drawHLine(0,h1+20 ,w);
  u8g.setFont(u8g_font_6x13);
  u8g.drawBox(0,h1+22,w,13);
  u8g.setColorIndex(0);
  u8g.drawStr(w/32-1 ,45, "Mini Project(2151102)");
  u8g.setFont(u8g_font_unifont);
  u8g.setColorIndex(1);
}

void anglepage(void){
  u8g.setFontPosTop();
  int h1 =u8g.getFontAscent()-u8g.getFontDescent();
//  Serial.println(h1);
  u8g.setFont(u8g_font_unifont);
  u8g.drawHLine(0,h1+2 ,w);
  u8g.drawStr(40 , 0 , "Angle");
  u8g.setFont(u8g_font_unifont);
  
float x = (40*cos(abs(Input_Y)*PI/180))+64; 
float y = -(40*sin(abs(Input_Y)*PI/180))+60 ;
  
  u8g.drawCircle(64, 60, 40, U8G_DRAW_UPPER_RIGHT);
  u8g.drawCircle(64, 60, 40, U8G_DRAW_UPPER_LEFT);
  u8g.drawBox(x-1,y,5,5);
  
if(abs((int)Input_Y) == 0 || abs((int)Input_Y) == 180)
{ u8g.drawHLine(55,35,20);u8g.drawHLine(55,36,20);
  u8g.drawHLine(55,45,20);u8g.drawHLine(55,46,20);
  u8g.setFont(u8g_font_courR08);
  u8g.drawStr(40 ,60, "Reference");
  u8g.setFont(u8g_font_unifont);}

else if(abs((int)Input_Y) == 90){
  u8g.drawVLine(65,30,15);u8g.drawVLine(66,30,15);
  u8g.drawHLine(55,45,20);u8g.drawHLine(55,46,20);
  u8g.setFont(u8g_font_courR08);
  u8g.drawStr(35 ,60, "Right Angle");
  u8g.setFont(u8g_font_unifont);}

else
{ u8g.setFont(u8g_font_courB14);
  u8g.setFontPosCenter();
  u8g.setPrintPos(55,45);
  u8g.print(abs((int)Input_Y));
  Serial.println(Input_Y);
  u8g.setFont(u8g_font_unifont);}
}

void calibratepage(void) // THIS PAGE IS NOT USE COZ OF OVER_MEMORY_USAGE_ERROR 
{

u8g.setFont(u8g_font_8x13);
u8g.drawStr(45 ,15, "Wait for");
u8g.setFont(u8g_font_fub14);
u8g.drawStr(20 ,35, "Calibration");
u8g.setFont(u8g_font_8x13);
u8g.drawStr(64 ,50, "...");
}
