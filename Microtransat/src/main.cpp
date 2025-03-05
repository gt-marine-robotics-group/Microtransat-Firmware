#include "Arduino.h"

// Length of control loop
#define CONTROL_LOOP_TIME 20

// Cores to pin RTOS tasks to
uint8_t CORE_0 = 0;
uint8_t CORE_1 = 1;

// Task prototypes
void TaskNavigation(void *pvParameters);
void TaskGuidance(void *pvParameters);
void TaskControl(void *pvParameters);

// Define task handles
TaskHandle_t navigationHandle;
TaskHandle_t guidanceHandle;
TaskHandle_t controlHandle;

// The setup function runs once when you press reset or power on the board.
void setup() {
  // Initialize sensors and things
  // Load data from SD card (waypoints, etc.)

  // Creates tasks (function, name, stack memory, parameters, priority, handle, core)
  xTaskCreatePinnedToCore(TaskControl, "Control", 2048, NULL, 3, &controlHandle, CORE_1);
  xTaskCreatePinnedToCore(TaskGuidance, "Guidance", 2048, NULL, 2, &guidanceHandle, CORE_1);
  xTaskCreatePinnedToCore(TaskNavigation, "Navigation", 2048, NULL, 1, &navigationHandle, CORE_1);
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/
void TaskNavigation(void *pvParameters) {
  (void)pvParameters;
  for (;;) {
    // Fetchs IMU and GPS data
    // Runs localization algorithms
    // Determines current location and heading

    // Yields to guidance
    xTaskNotifyGive(guidanceHandle);
  }
}

void TaskGuidance(void *pvParameters) {
  (void)pvParameters;
  for (;;) {
    // Waits for notification from navigation
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    // Fetches current location and heading
    // Fetches wingsail encoder and wind vane data
    // Fetches RC receiver data
    // Fetches LoRA data
    // Checks operation mode
    // IF MANUAL
    //  Do nothing
    // ELSE IF SEMIAUTO
    //  Read joystick positions from RC receiver
    //  Map to heading and angle of attack targets
    // ELSE IF AUTO
    //  Check for waypoint updates over LoRA
    //  Check current location against waypoints
    //  Run controls algorithms to determine heading and angle of attack targets

    // Log telemetry to SD card and LoRA
  }
}

void TaskControl(void *pvParameters) {
  (void)pvParameters;
  for (;;) {
    // Checks operation mode
    // IF MANUAL
    //  Read PWM signal from RC receiver
    //  Directly relay signal to servos
    // IF SEMIAUTO || AUTO
    //  Fetch heading and angle of attack targets
    //  Fetch wingsail encoder and wind data
    //  Run PIDs to determine servo powers (rudder and wingsail)
    //  Drive servos

    // Delays a bit
    vTaskDelay(pd_MS_TO_TICKS(CONTROL_LOOP_TIME));
  }
}