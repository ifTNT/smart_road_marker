#include "include/system.h"

void setup() {
  // For debug purpose
  Serial.begin(115200);

  // Initialize the car sensor.
  carSensor->init();

  // Initialize last transmission time to current system time
  lastReportTime = millis();
}

void loop() {
  carSensor->updateMeasure();

  // If the durtion between system time and last transmission time
  // is larger than threshold, the system should transmit a new report.
  if(1){

    
  }

}
