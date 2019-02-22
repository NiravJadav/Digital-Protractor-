
void Compute_RPY(double& y)
{
  while(i2cRead(0x3B,i2cData,14));
  gyroZ = ((i2cData[12] << 8) | i2cData[13]);
  double gyroZrate =  (((double)gyroZ - gyroZoffset)/131.0);
  compAngleZ += gyroZrate*((double)(micros()-timer)/1000000);
  timer = micros();
  y = compAngleZ;
  if((y > 360)||(y < -360))  {y =   0;}
}

void Initlize_MPU6050(void)
{
  i2cData[0] = 7; // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
  i2cData[1] = 0x00; // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
  i2cData[2] = 0x00; // Set Gyro Full Scale Range to ±250deg/s
  i2cData[3] = 0x00; // Set Accelerometer Full Scale Range to ±2g
  while(i2cWrite(0x19,i2cData,4,false)); // Write to all four registers at once
  while(i2cWrite(0x6B,0x01,true)); // PLL with X axis gyroscope reference and disable sleep mode 
  
  while(i2cRead(0x75,i2cData,1));
  if(i2cData[0] != 0x68) { // Read "WHO_AM_I" register
    Serial.print(F("Error reading sensor"));
    while(1); // if there is ERROR in Sensor connection, no further action to avoid any accident
  }
  delay(100); // Wait for sensor to stabilize
  
  /* Set gyro starting angle */
  while(i2cRead(0x3B,i2cData,6));
  compAngleZ = 0;
  timer = micros(); 
}

// AIM : obtain raw data from MPU6050

void Compute_gyro(void)
{
  while(i2cRead(0x3B,i2cData,14));
  gyroZ = ((i2cData[12] << 8) | i2cData[13]);
  
}


// AIM : Offsert calculation 
// called in setup for offset calculation at intialization

void calculate_offset(void){
 Serial.println(".........Calculation of Gyro offset.........");
 Serial.println("Wait for 10 Seconds.........");
 int i;
 Compute_gyro();
 Compute_gyro();
 for(i=1;i<=1000;i++)
 {
  Compute_gyro();
  g3 += gyroZ;
 }
  double gyroZoffset=g3/1000;
  g3=0;
  delay(10);
}


