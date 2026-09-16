
#include "TinyGPS++.h"
#include "SoftwareSerial.h"

// rx pico goes to tx gps and vice versa
// physical pin 27 - gp 21
// physical pin 26 - gp 20
// software uses GP numbering
SoftwareSerial serial_connection(21, 20);


TinyGPSPlus gps;

#define PMTK_SET_NMEA_OUTPUT_ALLDATA "$PMTK314,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
#define PMTK_SET_NMEA_UPDATE_1HZ  "$PMTK220,1000*1F"
#define PMTK_Q_RELEASE "$PMTK605*31"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {}
  delay(2000);
  serial_connection.begin(9600);
  Serial.println("GPS Start");
  // copied from https://github.com/adafruit/Adafruit_GPS/blob/master/examples/GPS_SoftwareSerial_EchoTest/GPS_SoftwareSerial_EchoTest.ino
  serial_connection.println(PMTK_SET_NMEA_UPDATE_1HZ);
  serial_connection.println(PMTK_Q_RELEASE);
}

void loop() {
  while(serial_connection.available()){
    Serial.write(serial_connection.read());
    int raw = serial_connection.read();
    gps.encode(raw);
  }
  if(gps.location.isUpdated()){
    Serial.println("Satellite Count: ");
    Serial.println(gps.satellites.value());
    Serial.println("Latitude: ");
    Serial.println(gps.location.lat(),6);
    Serial.println("Longitude: ");
    Serial.println(gps.location.lng(),6);
    Serial.println("Speed MPH: ");
    Serial.println(gps.speed.mph());
    Serial.println("Altitude Feet: ");
    Serial.println(gps.altitude.feet());
    Serial.println("");
  }
}
