/**
 * @file DOFStick.cpp
 * @author Jason Hsiao
 * @date 12/24/2025
 * @version 1.0
 *
 * @brief Implementation of 9 DOF Stick Sensor Interface.
 *
 * This file holds the functions for instantiating, setting up, 
 * and reading/printing the sensor data.
 * 
 * @todo See if there is a way to directly interface with Protobuf or PIO DMA
 * @see config.h for the hardware definitions like GPIO mapping
 */

#ifdef HAS_SENSORS

#include "DOFStick.h"

// Constructor
DOFStick::DOFStick() {
    // Initialize internal variables if needed

}

void DOFStick::setup(){
    // Set up the I2C object - Unnecessary since already defined in Temp Sensor
    Wire1.setSDA(config::TEMP_SDA);
    Wire1.setSCL(config::TEMP_SCL);
    Wire1.begin();


    // 2. Initialize the sensor by passing the Wire1 pointer
    imu = Adafruit_LSM9DS1(&Wire1, 0);
    if (!imu.begin()) {
        Serial.println("9DOF Sensor not detected. Please check connections.");
    }

    // 1.) Set the accelerometer range
    imu.setupAccel(imu.LSM9DS1_ACCELRANGE_2G, imu.LSM9DS1_ACCELDATARATE_10HZ);
    //imu.setupAccel(imu.LSM9DS1_ACCELRANGE_4G, imu.LSM9DS1_ACCELDATARATE_119HZ);
    //imu.setupAccel(imu.LSM9DS1_ACCELRANGE_8G, imu.LSM9DS1_ACCELDATARATE_476HZ);
    //imu.setupAccel(imu.LSM9DS1_ACCELRANGE_16G, imu.LSM9DS1_ACCELDATARATE_952HZ);
    
    // 2.) Set the magnetometer sensitivity
    imu.setupMag(imu.LSM9DS1_MAGGAIN_4GAUSS);
    //imu.setupMag(imu.LSM9DS1_MAGGAIN_8GAUSS);
    //imu.setupMag(imu.LSM9DS1_MAGGAIN_12GAUSS);
    //imu.setupMag(imu.LSM9DS1_MAGGAIN_16GAUSS);

    // 3.) Setup the gyroscope
    imu.setupGyro(imu.LSM9DS1_GYROSCALE_245DPS);
    //imu.setupGyro(imu.LSM9DS1_GYROSCALE_500DPS);
    //imu.setupGyro(imu.LSM9DS1_GYROSCALE_2000DPS);
    Serial.println("9DOF Sensor Initialized Successfully.");

}

bool DOFStick::estop(){
    // No need to estop a passive sensor
    // but can just end the I2C connection
    return true;
}

// If syntax here looks weird, my bad, I took some code from 4180 and vibed it to work
uint16_t DOFStick::readData() {
    // Read acceleration, gyroscope, and magnetometer data
    imu.read();

    // Variables to store sensor readings
    sensors_event_t accel, gyro, mag, temp;

    // Read accelerometer data
    imu.getEvent(&accel, &gyro, &mag, &temp);

    // Print Accelerometer Data (in m/s^2)
    Serial.println("Accelerometer Data (m/s^2):");
    Serial.print("X: "); Serial.print(accel.acceleration.x); 
    Serial.print(" Y: "); Serial.print(accel.acceleration.y); 
    Serial.print(" Z: "); Serial.println(accel.acceleration.z);

    // Print Gyroscope Data (in rad/s)
    Serial.println("Gyroscope Data (rad/s):");
    Serial.print("X: "); Serial.print(gyro.gyro.x); 
    Serial.print(" Y: "); Serial.print(gyro.gyro.y); 
    Serial.print(" Z: "); Serial.println(gyro.gyro.z);

    // Print Magnetometer Data (in uTesla)
    Serial.println("Magnetometer Data (uT):");
    Serial.print("X: "); Serial.print(mag.magnetic.x); 
    Serial.print(" Y: "); Serial.print(mag.magnetic.y); 
    Serial.print(" Z: "); Serial.println(mag.magnetic.z);

    return 1;
}

#endif

