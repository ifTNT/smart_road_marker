#include "include/system.h"

void setup() {
  // Initialize the debugging serial port.
  DEBUG_OUT.begin(115200);

  // Initialize the car-sensor.
  carSensor->init();

  // Initialize last transmission time to current system time.
  lastReportTime = millis();
}

void loop() {
  carSensor->updateMeasure();

  // If the durtion between system time and last report transmission time
  // is larger than threshold, the system should transmit a new report.
  // Overflow of millis() is about 50-days, so it's not be considerd here.
  if(millis()-lastReportTime >= REPORT_DURATION){
    
    // Get a fresh produced report summary from the car-sensor.
    report_t newReport = carSensor->getReport();
    // [TODO] Transmit a new report

    // Clear measured data for next reporting
    carSensor->resetMeasure();

    // Update the last report transmiting time to current system time.
    lastReportTime = millis();
  }

}
