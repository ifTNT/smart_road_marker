#include "include/car_sensor_ir.h"
#include <Arduino.h>

CarSensorIR::CarSensorIR(const uint8_t& fromPin, const uint8_t& toPin, int deadZone, float lpfAplha, float hasCarThld, float distance):
  _deadZone(deadZone),
  _lpfAlpha(lpfAplha),
  _hasCarThld(hasCarThld),
  _distance(distance),
  _fromPin(fromPin),
  _toPin(toPin)
  {}

int CarSensorIR::init(){
  int err;
  // Reset the measurment report
  if((err = resetMeasure())!=0){
    return err;
  }

  // Initialize the storage of exponatial moving average (low-pass filter)
  _fromEMV = 0;
  _toEMV = 0;

  // Set the state into no-car
  _state = 0;

  // Set the sensor pin to input mode.
  pinMode(_fromPin, INPUT);
  pinMode(_toPin, INPUT);

  return 0;
}

int CarSensorIR::updateMeasure(){

  // Read the amplitude of from-sensor
  int rawSensorVal = analogRead(_fromPin);
  // Prevent the inverted value goes to infinity
  if(rawSensorVal<1){
    rawSensorVal = 1;
  }
  // Calculate the new distance(inverted value) and exponatial moving average.
  float sensorDist = 1024.0/(float)rawSensorVal;
  float newFromEMV = _lpfAlpha*(float)sensorDist + (1-_lpfAlpha)*_fromEMV;

  // Read the amplitude of to-sensor
  rawSensorVal = analogRead(_toPin);
  // Prevent the inverted value goes to infinity
  if(rawSensorVal<1){
    rawSensorVal = 1;
  }
  // Calculate the new distance(inverted value) and exponatial moving average.
  sensorDist = 1024.0/(float)rawSensorVal;
  float newToEMV = _lpfAlpha*(float)sensorDist + (1-_lpfAlpha)*_toEMV;

#ifdef DEBUG_IR_SENSOR
  // Print the filted data to debug serial
  DEBUG_OUT.print("1100,0,");
  DEBUG_OUT.print(newFromEMV);
  DEBUG_OUT.print(",");
  DEBUG_OUT.println(newToEMV);
#endif

  switch(_state){
  // The empty state
  case 0:
    // If the last tick has no car and now there's a car on from-sensor
    if(_fromEMV>_hasCarThld && newFromEMV<_hasCarThld){
      // Change to measure state.
      _state = 1;

      // Record the system time of begining of measure state.
      _measureBeginTime = millis();

    }
  break;
  
  // The measure state
  case 1:
    // If the last tick has no car and now there's a car on to-sensor
    if(_toEMV>_hasCarThld && newToEMV<_hasCarThld){
      // Change to wait state.
      _state = 2;

      // Calculte the accumulated speed of the car.
      unsigned long long duration = millis()-_measureBeginTime;
      float totalSpeed = _currentReport.avgSpeed*_currentReport.traffic;

      // Calculate the current speed and convert cm per ms to km per hour.
      float currentSpeed = _distance/duration*36.0f;

#ifdef DEBUG_IR_SPEED
      Serial.print("The speed of the car: ");
      Serial.println(currentSpeed);
#endif

      // Accumulate current speed to history speed.
      totalSpeed += currentSpeed;
      // Increase the car counter.
      _currentReport.traffic++;
      // Write back the new average speed.
      _currentReport.avgSpeed = totalSpeed/_currentReport.traffic;
    }

  break;

  // The wait state
  case 2:
    // If the last tick has car and now has no car on to-sensor,
    // change to dead-zone state.
    if(_toEMV<_hasCarThld && newToEMV>_hasCarThld){
      _state = 3;
      _waitEndTime = millis();
    }
  break;

  // The dead-zone state
  case 3:
    // If the dead-zone timer has expired, back to empty state.
    if(millis()-_waitEndTime > _deadZone){
      _state = 0;
    }
  break;
  }

  // Write back the new filtered value.
  _fromEMV = newFromEMV;
  _toEMV = newToEMV;
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
  // The operation is as fast as return a pointer to a structure,
  // since the structure report_t is relatively small.
  return currentReport;
}

int CarSensorIR::resetMeasure(){
  _currentReport.avgSpeed = 0;
  _currentReport.traffic = 0;
  return 0;
}

const char* CarSensorIR::getErrMessage(int errCode){
  switch(errCode){
    case 0: return "Succeed";
    default: return "Unknown error code";
  }
}