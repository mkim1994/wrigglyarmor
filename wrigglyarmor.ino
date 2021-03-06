#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

// i2c
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();

SoftwareSerial btPort(6,10);

float initialTemp;
float targetTemp;
float currentTemp;

float gyroV[] = {0,0,0};
float gyroA;
float gyroLastDir = 1; //1 or -1
float gyroThreshold = 1000; //calibratin

int buttonPin = 9;
int buttonState = LOW;
int buttonLastState = HIGH;
int numButtonPresses = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 8, NEO_GRB + NEO_KHZ800);
#define FACTORYREST_ENABLE  1
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
  btPort.begin(9600);
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
    while (1);
  }
  
  initialTemp = 0;//lsm.temperature;
  
//  Serial.print("readings start");
//  Serial.print("\t");
//  Serial.println(initialTemp);
//  Serial.println("");
//  Serial.println("");

  targetTemp = initialTemp + 9; //needs 2 b tested

  strip.begin();
  strip.show();

  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  //------get the data
  
  lsm.read();
  
  gyroV[0] = gyroV[1];
  gyroV[1] = gyroV[2];
  gyroV[2] = lsm.gyroData.y;

  gyroA = average(gyroV);

  currentTemp = lsm.temperature;

  //------analyze the data

  if (currentTemp >= targetTemp){
    //you have it in your warm sweaty hands! yay!
    
    if (abs(gyroA)>gyroThreshold){
//      Serial.println(gyroA);
      //it's going fast enough to count as actual movement
      if (gyroA > 0 || gyroLastDir < 0){
        if (numButtonPresses==1){
          strip.setPixelColor(0, strip.Color(3,1,1));
        }
        Serial.write(1);
        btPort.write(1);
        gyroLastDir = 1;
      }else if (gyroA < 0 || gyroLastDir > 0){
        if (numButtonPresses==1){
          strip.setPixelColor(0, strip.Color(1,1,3));
        }
        Serial.write(2);
        btPort.write(2);
        gyroLastDir = -1;
      }
    }
  }
  else{
    strip.setPixelColor(0,strip.Color(0,0,0));
  }

  buttonState = digitalRead(buttonPin);
  if (buttonState==LOW && buttonLastState == HIGH){
    buttonLastState = LOW;
    numButtonPresses++;
    if (numButtonPresses == 1){
      Serial.write(3);
      btPort.write(3);
    }
    if (numButtonPresses == 2){
      Serial.write(4);
      btPort.write(4);
      strip.setPixelColor(0,strip.Color(50,10,40));
      numButtonPresses = 0; //so you can restart
    }
  }
  if (buttonState==HIGH && buttonLastState == LOW){
    buttonLastState = HIGH;
  }
  

  strip.show();
  delay(100);
}

//gets the average of all the vals in the array
float average(float vals[]){
  float a = 0;
  for (int i=0; i<sizeof(vals); i++){
    a += vals[i];
  }
  a /= (float)sizeof(vals);

  return a;
}

