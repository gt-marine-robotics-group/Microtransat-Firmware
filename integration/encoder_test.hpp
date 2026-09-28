// ReSharper disable CppNonInlineFunctionDefinitionInHeaderFile
// ReSharper disable file CppNonInlineVariableDefinitionInHeaderFile
#pragma once
#include "AS5600.h"


// see https://arduino-pico.readthedocs.io/en/latest/wire.html
// the default i2c setup using Wire
// is pins gp5 and gp4 (7, 6) for scl/sda
AS5600 as5600(&Wire); // NOLINT(*-interfaces-global-init)


void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  delay(2000);

  Serial.println("Encoder Test");
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);
  Serial.println();


  Wire.begin();
  as5600.begin(); // no hw dir pin since we are tying DIR to GND
  as5600.setDirection(AS5600_CLOCK_WISE);
  Serial.print("AS5600 connected: ");
  Serial.println(as5600.isConnected() ? "true" : "false");
  delay(1000);
}

void loop() {

  Serial.print(millis());
  Serial.print("\t");
  Serial.print(as5600.readAngle() * AS5600_RAW_TO_DEGREES);
  Serial.print("\n");
  delay(100);
}
