const int stepPin = 3;
const int dirPin = 4;
const int stepsPerRevolution = 200; //Based on the step of the motor, currently using Full-Step
float degreePerStep = 360.0/stepsPerRevolution;
float currentAngle = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

float stepperMotortoAngleDiff(float targetAngle, float currentAngle){
  float changeAngle = currentAngle - targetAngle;
  float numberOfSteps = changeAngle/degreePerStep;
  int intNumberOfSteps = int(numberofSteps+0.5)

  if(changeAngle > 0){
    digitalWrite(dirPin,HIGH);
  } else {
    digitalWrite(dirPin, LOW);
  }

  for(int x = 0; x < abs(intNumberOfSteps); x++){
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(2000);
  }
  
  return (currentAngle+(degreePerStep*intNumberOfSteps));
}