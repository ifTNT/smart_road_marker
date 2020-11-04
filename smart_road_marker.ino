#include "include/system.h"

void setup() {
  // Initialize the debugging serial port.
  DEBUG_OUT.begin(DEBUG_SERIAL_BUADRATE);

  // Initialize the car-sensor and the reporter.
  // If there's any error, print the error message to the debug output.
  if((err = carSensor->init()) != 0){
    DEBUG_OUT.print("Initialitation of car-sensor failed. Error message:");
    DEBUG_OUT.println(carSensor->getErrMessage(err));
  }
  
  if((err = repoter->init()) != 0){
    DEBUG_OUT.print("Initialitation of repoter failed. Error message:");
    DEBUG_OUT.println(repoter->getErrMessage(err));
  }

  // Initialize last report publishment time to current system time.
  lastPublishTime = millis();
}

void loop() {
  
  // Let the car-sensor detect the current traffic flow.
  // If there's any error, print the error message to the debug output.
  if((err = carSensor->updateMeasure()) != 0){
    DEBUG_OUT.print("Updating the measurement of car-sensor failed. Error message:");
    DEBUG_OUT.println(carSensor->getErrMessage(err));
  }

  // If the durtion between system time and last report publishing time
  // is larger than threshold, the system should publish a new report.
  // Overflow of millis() is about 50-days, so it's not be considerd here.
  if(millis()-lastPublishTime >= REPORT_DURATION){
    
    // Get a fresh produced report summary from the car-sensor.
    report_t newReport = carSensor->getReport();
#ifdef DEBUG_REPORT_PUBLISH
    DEBUG_OUT.println("New report that will be published:");
    DEBUG_OUT.print("\ttraffic: ");
    DEBUG_OUT.println(newReport.traffic);
    DEBUG_OUT.print("\tavgSpeed: ");
    DEBUG_OUT.println(newReport.avgSpeed);
#endif

    // Publish the new produced report to backend.
    // If there's any error, print the error message to the debug output.
    if((err = repoter->publish(newReport)) != 0){
      DEBUG_OUT.print("Publishing the new report failed. Error message:");
      DEBUG_OUT.println(repoter->getErrMessage(err));
    }

    // Clear measured data to generate next report
    carSensor->resetMeasure();

    // Update the last report publishing time to current system time.
    lastPublishTime = millis();
  }

}
