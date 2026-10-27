// ReSharper disable CppNonInlineFunctionDefinitionInHeaderFile
// ReSharper disable file CppNonInlineVariableDefinitionInHeaderFile
#pragma once
// #include "Servo.h"
#include "AS5600.h"


// pin servo signal is gp22

Servo serv;
AS5600 as5600(&Wire); // NOLINT(*-interfaces-global-init)


int pos = 0;    // variable to store the servo position


void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  delay(2000);

  Serial.println("Servo Test");
  Serial.println(__FILE__);
  Serial.println();

  Wire.begin();
  as5600.begin(); // no hw dir pin since we are tying DIR to GND
  as5600.setDirection(AS5600_COUNTERCLOCK_WISE);
  as5600.setOffset(311.13 + 180); // undo the transformation we do later to maintain zero point
  serv.attach(22);

}

float P = 2;
float I = 0.001;
float D = .01;
const float SERVO_OFFSET = 90;


float vaneRead() {
  // transform [0, 360) -> [-180, 180)
  return as5600.readAngle() * AS5600_RAW_TO_DEGREES - 180;
}

float lastError = -99999;
float lastTime = millis();
float error_acc = 0;

float out(float error) {
  if (lastError == -99999) lastError = error; // make d term go to 0 on first run

  float dt = millis() - lastTime; // compute delta t = current time - last time
  lastTime = millis();

  // error_acc += error * dt;

  float o = P * error + D * (error - lastError) / dt;
  lastError = error;
  return o;
}


float computeOffset(float degrees) {
  float degsOffset = degrees;
  if (abs(degsOffset) > 60) {
    int sign = (degsOffset > 0 ? 1 : -1);
    degsOffset = static_cast<float>(45.0) * sign;
  }
  return degsOffset + SERVO_OFFSET;
}


void writeServo(float degrees) {
  float degsOffset = computeOffset(degrees);
  serv.write(degsOffset);
}


void loop() {
  float target_angle = 45;
  float angle = vaneRead();
  float err = target_angle - angle;
  float cntrl_out = out(err);
  float final_out = computeOffset(cntrl_out);
  Serial.print("target=");
  Serial.print(target_angle);
  Serial.print("\tangle=");
  Serial.print(angle);
  Serial.print("\terr=");
  Serial.print(err);
  Serial.print("\tout=");
  Serial.print(cntrl_out);
  Serial.print("\tfinal_out=");
  Serial.print(final_out);
  Serial.println();

  writeServo(cntrl_out);
  // delay(100);


  // serv.write(90);
  // for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
  //   // in steps of 1 degree
  //   serv.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(100);                       // waits 15ms for the servo to reach the position
  // }
  // for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //   // Serial.printl(millis());
  //   Serial.println(pos);
  //   serv.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(250);                       // waits 15ms for the servo to reach the position
  // }


}
