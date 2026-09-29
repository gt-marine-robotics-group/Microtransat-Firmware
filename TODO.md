controls:
    controller - master controller class
    rudder - mid-level driver for rudder
    servo_driver - low-level servo driver
    tailwing - mid-level driver for tailwing

data_managment:
    logger - handles what data is logged to sd card and sent via telemetry
    lora_comm - low-level driver for lora telemetry updates/commands
    rc_receiver - low-level driver for incoming rc commands
    sd_driver - low-level driver for logging/reading from sd card

localization:
    ekf - kalman filter for localization sensor fusion

sensors:
    wind_vane - mid-level driver for wind vane sensor
    imu - low-level driver for imu
    gps - low-level driver for gps
    mag_encoder - low-level driver for magnetic encoder
    wingsail_encoder - mid-level driver for wingsail encoder

utility:
    logger - organizes logged data/telemetry
    robot_state
    math_structs

main:
    main
    board_layout
    rc_controller
    state_machine
    state_manager
