#include "car_sensor_ir.h"

int CarSensorIR::init(){
  return 0;
}

int CarSensorIR::updateMeasure(){
  return 0;
}

report_t CarSensorIR::getReport(){
  // Allocate a new structure on stack.
  // This structure will be direct returned.
  report_t currentReport;

  // Copy the value from data member to new allocated varible
  currentReport = _currentReport;
  
  // Direct return the new allocated structure.
  // This operation will cause another structure copy.
  // Since the structure report_t is relatively small,
  // this operation is as fast as return a pointer to a structure.
  return currentReport;
}

int CarSensorIR::resetMeasure(){

}

String CarSensorIR::getErrMessage(int errCode){

}