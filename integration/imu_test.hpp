#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);
  
  /* Display the floating point data */
  // Event Orientation Data
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println();

  // Magnetometer Data in micro Teslas
  imu::Vector<3> magnetometer = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
  
  Serial.print("MagnetoX: ");
  Serial.print(magnetometer.x());
  Serial.print(" MagnetoY: ");
  Serial.print(magnetometer.y());
  Serial.print(" MagetoZ: ");
  Serial.print(magnetometer.z());
  Serial.println("");

  // Gyroscope Data in radians per second
  imu::Vector<3> gyroscope = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  
  Serial.print("GyroX: ");
  Serial.print(gyroscope.x());
  Serial.print(" GyroY: ");
  Serial.print(gyroscope.y());
  Serial.print(" GyroZ: ");
  Serial.print(gyroscope.z());
  Serial.println("");

  // Accelerometer Data in radians per second
  imu::Vector<3> accelerometer = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  
  Serial.print("AcceloX: ");
  Serial.print(accelerometer.x());
  Serial.print(" AcceloY: ");
  Serial.print(accelerometer.y());
  Serial.print(" AcceloZ: ");
  Serial.print(accelerometer.z());
  Serial.println("");

  // Linear Acceleration Data in radians per second
  imu::Vector<3> linaccel = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  
  Serial.print("LinAcceloX: ");
  Serial.print(linaccel.x());
  Serial.print(" LinAcceloY: ");
  Serial.print(linaccel.y());
  Serial.print(" LinAcceloZ: ");
  Serial.print(linaccel.z());
  Serial.println("");
  
  // Gravity Data in radians per second
  imu::Vector<3> gravity = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  
  Serial.print("GravX: ");
  Serial.print(gravity.x());
  Serial.print(" GravY: ");
  Serial.print(gravity.y());
  Serial.print(" GravZ: ");
  Serial.print(gravity.z());
  Serial.println("");

  // Quarterion Data
  imu::Quaternion quat = bno.getQuat();

  Serial.print("qW: ");
  Serial.print(quat.w(), 4);
  Serial.print(" qX: ");
  Serial.print(quat.x(), 4);
  Serial.print(" qY: ");
  Serial.print(quat.y(), 4);
  Serial.print(" qZ: ");
  Serial.print(quat.z(), 4);
  Serial.println("");

  // Temperature Data in celcius
  int8_t temp = bno.getTemp();

  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println("");

  delay(100);
}
