#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>

// i2c
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();

//put a button for calibrating, to get initial values for gyro and temp

float initialTemperature;
float targetTemperature;

float gyroV[] = {0,0,0};
float gyroA;

void setupSensor()
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_6G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_16G);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_2000DPS);
}

void setup() {
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  Serial.begin(9600);
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
    while (1);
  }
  
  initialTemperature = 0;//lsm.temperature;
  
  Serial.print("readings start");
  Serial.print("\t");
  Serial.println(initialTemperature);
  Serial.println("");
  Serial.println("");

  targetTemperature = initialTemperature + 9; //needs 2 b tested

  for (int i=0; i<3; i++){
//    gyroV[i] = 0;
     Serial.print(gyroV[i]);
  }
  Serial.println("");
}

void loop() {
  lsm.read();
  
  gyroV[0] = gyroV[1];
  gyroV[1] = gyroV[2];
  gyroV[2] = lsm.gyroData.y;

  gyroA = average(gyroV);

  Serial.println(gyroA);

  delay(100);
}

float average(float vals[]){
  float a = 0;
  for (int i=0; i<sizeof(vals); i++){
    a += vals[i];
  }
  a /= (float)sizeof(vals);

  return a;
}

