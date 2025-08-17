#include "board_layout.h"
#include <utility/imumaths.h>

typedef struct IMU_DATA{
    imu::Vector<3> accelerometer;
    imu::Vector<3> gyroscope;
    imu::Vector<3> linear_acceleration;
    imu::Vector<3> gravity;
    imu::Quaternion quaternion;
} IMU_DATA;

void imu_driver_open();

void imu_driver_close();

IMU_DATA* imu_driver_read();
