///AUTHOR: HARSH
///Complementry Filter using MPU9255 IMU
///I2C protocol
///without using libraries


#include <Wire.h>

#define MPU_ADDRESS 0x68 // MPU9255 address when AD0 pin is connected to GND
#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG 0x1B
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43

int16_t accelerometer_x, accelerometer_y, accelerometer_z;
int16_t gyro_x, gyro_y, gyro_z;

const float alpha = 0.64; // Complementary filter constant

float firstgyrotime = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  // Initialize MPU9255
  initializeMPU9255();
}

void loop() {
  readAccelerometerData();
  readGyroData();

  // Apply complementary filter
  float pitch = atan2(accelerometer_y, sqrt(accelerometer_x * accelerometer_x + accelerometer_z * accelerometer_z) );
  float roll = atan2(accelerometer_x, sqrt(accelerometer_y * accelerometer_y + accelerometer_z * accelerometer_z) );
  Serial.print(pitch);
  Serial.print(" "); 
  Serial.print(roll);
  Serial.print(" ");

  float gyro_pitch = pitch + (gyro_x) * 0.01; // Convert gyro data to degrees per second
  float gyro_roll = roll + (gyro_y) * 0.01;

  // float gyrotime=millis();
  // float gyro_roll=0;
  // float gyro_pitch=0;
  // gyro_roll = gyro_roll + (gyrotime- firstgyrotime)*gyro_x*0.001;  
  // gyro_pitch = gyro_pitch + (gyrotime- firstgyrotime)*gyro_y*0.001;
  //firstgyrotime = gyrotime;

  Serial.print(gyro_pitch);
  Serial.print(" ");
  Serial.print(gyro_roll);
  Serial.print(" ");
  

  float final_pitch = alpha * gyro_pitch + (1 - alpha) * pitch; // Apply complementary filter
  float final_roll = alpha * gyro_roll + (1 - alpha) * roll;

  // Print filtered pitch and roll  
  Serial.print((final_pitch * 180 / M_PI)-10);
  Serial.print(" ");
  Serial.println(final_roll * 180 / M_PI);
  
  
}



void initializeMPU9255() {
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(ACCEL_CONFIG);
  Wire.write(0x01); // Set accelerometer range to +/- 4g
  Wire.endTransmission();

  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(GYRO_CONFIG);
  Wire.write(0x01); // Set gyroscope range to +/- 500 degrees/s
  Wire.endTransmission();
}



void readAccelerometerData() {
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDRESS, 6, true);
  accelerometer_x = (Wire.read() << 8 | Wire.read())/4096;
  accelerometer_y = (Wire.read() << 8 | Wire.read())/4096;
  accelerometer_z = (Wire.read() << 8 | Wire.read())/4096;
}



void readGyroData() {
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(GYRO_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDRESS, 6, true);
  gyro_x = (int16_t)(Wire.read() << 8 | Wire.read()) / 65.5 ;
  gyro_y = (int16_t)(Wire.read() << 8 | Wire.read()) / 65.5 ;
  gyro_z = (int16_t)(Wire.read() << 8 | Wire.read()) / 65.5;
}


void printvalue(){
  initializeMPU9255();
  readGyroData();
  readAccelerometerData();

  Serial.print(accelerometer_x);
  Serial.print(" ");
  Serial.print(accelerometer_y);
  Serial.print(" ");
  Serial.print(accelerometer_z);
  Serial.print(" ");

  Serial.print(gyro_x);
  Serial.print(" ");
  Serial.print(gyro_y);
  Serial.print(" ");
  Serial.print(gyro_z);
  Serial.print(" ");
}
