///AUTHOR: Harsh
///Kalman Filter code 
///IMU used: MPU 9255
#include <Wire.h>

#define MPU_ADDRESS 0x68 // MPU9255 address when AD0 pin is connected to GND
#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG 0x1B
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43

int16_t accelerometer_x, accelerometer_y, accelerometer_z;
int16_t gyro_x, gyro_y, gyro_z;


float kalman_roll= 0, uncertainroll= 2*2;
float kalman_pitch =0, uncertainpitch= 2*2; 


float Output[]={0,0};


void setup() {
  Wire.begin();
  Serial.begin(9600);
  initializeMPU9255();
}



//___main___

void loop() {
  readAccelerometerData();
  readGyroData();

  // Serial.print(accelerometer_x);
  // Serial.print(" ");
  // Serial.print(accelerometer_y);
  // Serial.print(" ");
  // Serial.print(accelerometer_z);
  // Serial.print(" ");


  float pitch = atan2(accelerometer_y, sqrt(accelerometer_x * accelerometer_x + accelerometer_z * accelerometer_z) )*180/3.14;
  float roll = atan2(accelerometer_x, sqrt(accelerometer_y * accelerometer_y + accelerometer_z * accelerometer_z) )*180/3.14;
  // Serial.print(pitch);
  // Serial.print(" ");
  // Serial.print(roll);
  // Serial.print(" ");

  float gyro_pitch = pitch + (gyro_x) * 0.01; // Convert gyro data to degrees per second
  float gyro_roll = roll + (gyro_y) * 0.01;  

  //gyro_x is rateroll||   accelerometer_x is AccX
  // angleroll is roll ||| anglepitch is pitch

  kalmanFilter(kalman_roll, uncertainroll,gyro_roll , roll);
  kalman_roll= Output[0];
  uncertainroll= Output[1];

  kalmanFilter(kalman_pitch, uncertainpitch, gyro_pitch, pitch);
  kalman_pitch= Output[0];
  uncertainpitch= Output[1];

  Serial.print(kalman_roll);
  Serial.print(" ");
  Serial.println(kalman_pitch);



    
  
}

void kalmanFilter(float state, float uncertainity, float input, float measurement)
{
  const float processNoise = 0.003;
  const float measurementNoise = 0.3;
  
  state = state + processNoise*input;
  uncertainity= uncertainity + processNoise*processNoise*4*4;
  float kalmangain = uncertainity*1/(1*uncertainity + measurementNoise*measurementNoise);
  state= state+ kalmangain*(measurement-state);
  uncertainity=(1-kalmangain)*uncertainity;

  Output[0]=state;
  Output[1]=uncertainity;  

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
  accelerometer_z = (Wire.read() << 8 | Wire.read())/4096.0;
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


