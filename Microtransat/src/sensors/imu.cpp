#include "imu.h"

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
// #include <utility/imumaths.h>

#define BNO55_SENSOR_ID 55

Adafruit_BNO055 bno = Adafruit_BNO055(BNO55_SENSOR_ID);


void imu_driver_open() {
    if (!bno.begin()) {
        Serial.println("No BNO055 detected...");
        // Log_Message("No BNO055 detected...", ERROR);
    }

    delay(1000);

    bno.setExtCrystalUse(true);
}

void imu_driver_close() { }

IMU_DATA* imu_driver_read() {
    IMU_DATA* imu_data = (IMU_DATA*) (sizeof(IMU_DATA));

    imu_data->accelerometer = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    imu_data->gyroscope = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    imu_data->linear_acceleration = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    imu_data->gravity = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
    imu_data->quaternion = bno.getQuat();

    return imu_data;
}
