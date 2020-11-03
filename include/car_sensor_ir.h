#ifndef CAR_SENSOR_IR_H
#define CAR_SENSOR_IR_H

#include "car_sensor.h"

/*
 * The implementation class of car-sensor on GP2Y0A02YK0F IR module.
 * If you want to know the descrption of each function,
 * reference to car_sensor.h
 */
class CarSensorIR: public CarSensor{
  public:
  virtual int init();
  virtual int updateMeasure();
  virtual report_t getReport();
  virtual int resetMeasure();
  virtual const char* getErrMessage(int);
  
  private:
  report_t _currentReport;
};

#endif