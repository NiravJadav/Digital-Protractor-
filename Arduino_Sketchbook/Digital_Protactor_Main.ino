
//********************************************************************//
//---------------------**** MINI PROJECT ****-------------------------//
//                          """"""""""""                              //
// DIGITAL SCALE                                                      //
// Guided By: Prof. Ravi Butani                                       //
// Designed By : Nirav Jadav & Krushal Sankhavara                     //
// Department of Electronics & Communication Engineering              //
// Marwadi Education Foundation's Group of Institutions               //
// Rajkot-GUJARAT (INDIA)                                             //
//********************************************************************//
#include <Wire.h>
#include "U8glib.h"
#include "Logo_MEFGI.h"
#define ANGLE_BTN 10      // ANGLE MODE BUTTON
#define REF_BTN 11        // REFERENCE LINE SELECTION BUTTON
#define CALIBRATE_BTN 12    // CALIBRATION BUTTON

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);  // Fast I2C / TWI 

int w=128;
int h=64 ;
int angleflag = 1 ;
int16_t gyroZ;
double gyroZoffset=45.50;
double compAngleZ; // Calculate the angle using a complementary filter
double g3;
double Input_Y;
uint32_t timer;
uint8_t i2cData[14]; // Buffer for I2C data
char buf[9];
int vcc_measure;


void Compute_RPY(void);      //YAW ,PITCH , RAW CALACULATION FUNCTION INITLISE
void Initlize_MPU6050(void); // MPU6050 INITLIZE FUNCTION 
void calculate_offset(void); // OFFSET CALCULATION FUNCTION FOR CALIBRATION


void setup() 
{ 
  pinMode(ANGLE_BTN, INPUT_PULLUP);
  pinMode(REF_BTN, INPUT_PULLUP);
  pinMode(CALIBRATE_BTN, INPUT_PULLUP);
  pinMode(A0, INPUT); // for battry voltage
  analogReference(INTERNAL);

  
  Serial.begin(9600);
  Wire.begin();
  Serial.println(gyroZoffset);
  Initlize_MPU6050();
  calculate_offset();
  Serial.println(gyroZoffset);
  Compute_RPY(Input_Y);
  Serial.println(gyroZoffset);
  Serial.println("setupdone");

  u8g.setFontPosTop();
  u8g.setFont(u8g_font_unifont);
  u8g.setColorIndex(1);
  u8g.firstPage(); 
do{
   u8g.drawBitmapP( 0, 0, 16, 64, mefgi); 
   }while( u8g.nextPage() );
  delay(2000);
  u8g.firstPage(); 
do{
   mainpage();  
  }while( u8g.nextPage() );
  delay(2000);
  
}

void loop() {  
  Compute_RPY(Input_Y);
unsigned int vcc_in = analogRead(A0);
int vcc_measure = (int)((((((float)vcc_in)*1.1)/(1024*0.18) - 0.1)-3.6)*167.0);
if (digitalRead(ANGLE_BTN) == LOW){angleflag =0 ;}
if(angleflag == 0 ){ 
  u8g.firstPage(); 
  do{anglepage();
  u8g.setFont(u8g_font_orgv01); // Battry volatge display 
  u8g.setPrintPos(85,10);
  u8g.print(vcc_measure);
  u8g.print("% BAT");
  u8g.setFont(u8g_font_unifont);
    }
  while(u8g.nextPage());
}
if(digitalRead(REF_BTN)==LOW){ Initlize_MPU6050(); }
if(digitalRead(CALIBRATE_BTN)==LOW ){ calculate_offset();}



}



