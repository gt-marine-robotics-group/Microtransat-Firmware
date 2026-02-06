/**
 * @file TempSensor.cpp
 * @author Jason Hsiao
 * @date 12/24/2025
 * @version 1.0
 *
 * @brief Implementation of Temp and Humid Sensor Interface.
 *
 * This file holds the functions for instantiating, setting up, 
 * and reading/printing the sensor data.
 * 
 * @todo See if there is a way to directly interface with Protobuf or PIO DMA
 * @see config.h for the hardware definitions like GPIO mapping
 */

#ifdef HAS_SENSORS

#include "TempSensor.h"

// Constructor
TempSensor::TempSensor() {
    // Initialize internal variables if needed

}

void TempSensor::setup(){
    // Set up the I2C object
    Wire1.setSDA(config::TEMP_SDA);
    Wire1.setSCL(config::TEMP_SCL);
    Wire1.begin();


    // 2. Initialize the sensor by passing the Wire1 pointer
    while (!sensor.begin(Wire1)) {
        Serial.println("Could not find a valid Si7021 sensor, check wiring!");
    }
    Serial.println("Si7021 initialized!");
    
    // Standard set-up stuff
    sensor.setResolution(0); // RH 12-bit, Temp 14-bit (Default)
    sensor.heaterOff(); // Turn internal heater off

}

bool TempSensor::estop(){
    // No need to estop a passive sensor
    // but can just end the I2C connection
    return true;
}

// If syntax here looks weird, my bad, I took some code from 4180 and vibed it to work
uint16_t TempSensor::readData() {
    Serial.print("Humidity: ");
    Serial.print(sensor.getRH(), 2);
    
    Serial.print("%\tTemperature: ");
    float temp = sensor.getTemperature();
    Serial.print(temp, 2);
    Serial.println("C");
    
    
    // delay(1000);
    return static_cast<uint16_t>(temp);
}

#endif

