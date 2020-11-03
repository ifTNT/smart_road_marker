#ifndef CAR_SENSOR_H
#define CAR_SENSOR_H

#include "report.h"

/*
 * The interface of car sensor.
 */
class CarSensor{
  public:

  /*
   * This funcation is called at setup().
   * And it should perform any required initialization of underlying sensor.
   */
  virtual int init() = 0;
  
  /*
   * This function should query the sensor and update the measurement.
   * Measurement = Traffic + Average Speed.
   * Once single measure is completed, this function should return immeadiatly.
   * Return 0 if succeed. Otherwise, return the error code.
  */
  virtual int updateMeasure() = 0;

  /*
   * This function should return inner-storaged report data since last reset. 
   */
  virtual report_t getReport() = 0;

  /*
   * This function should clear any inner-storaged traffic or average speed data.
   * Return 0 if succeed. Otherwise, return the error code.
   */
  virtual int resetMeasure() = 0;

  /*
   * Get a human readable error message form given error code
   */
  virtual const char* getErrMessage(int) = 0;
};

#endif