#ifndef CAR_SENSOR_IR_H
#define CAR_SENSOR_IR_H

#include "car_sensor.h"
#include <Arduino.h>

/*
 * The implementation class of car-sensor on GP2Y0A02YK0F IR module.
 * If you want to know the descrption of each function,
 * reference to car_sensor.h
 */
class CarSensorIR: public CarSensor{
  public:
  /*
   * The constructor takes four parameters. 
   * The first one is fromPin, indicating the analog pin connected to the IR
   * seneor located where the traffic from direction.
   * The second one is toPin, indicating the analog pin connected to the IR
   * sensor located the traffic goes direction.
   * The third parameter is deadZone, indicating the duraction between a car
   * passed to-sensor and the timing of enabling the from-sensor. Unit is ms.
   * The fourth parameter is lpfAlpha, indicating the alpha of low-pass filter.
   * The fifth parameter is hasCarThld, indicating the threshold to decide
   * whether there is a car in front of the IR sensor.
   * The sixth parameter is distance, indicating the distance between two
   * sensors. Unit is centimeter.
   */
  CarSensorIR(const uint8_t& fromPin, const uint8_t& toPin, int deadZone = 500, float lpfAplha = 0.05, float hasCarThld = 600.0, float distance = 9.0);
  int init();
  int updateMeasure();
  report_t getReport();
  int resetMeasure();
  const char* getErrMessage(int);
  
  private:
  const unsigned long long _deadZone;
  const float _lpfAlpha;
  const float _hasCarThld;
  const float _distance;
  const uint8_t& _fromPin;
  const uint8_t& _toPin;
  float _fromEMV;
  float _toEMV;

  // The state of this system
  // 0: Empty. Indicating there is no car sensed by two sensors.
  // 1: Measure. Indicating there is exatly one car passed from-sensor 
  //    but not passed to-sensor yet. The duration of this state point out
  //    the speed of the car.
  // 2: Wait. Indicating there is a car sensed by both of sensor.
  //    In this state, any changing of both sensor will be ignored until
  //    the car leaving detecting zone.
  // 3: Dead-zone. After a car leaving detecting zone. The system will goes
  //    to this state and start a timer. In this state, any changing of both 
  //    sensors have no effect on system.
  int _state;

  // The system time of the ending of last wait state.
  // Unit: milliseconds.
  // The overflow duration of millis() is about 50-days,
  // so the overflow problem is not considerd here.
  unsigned long long _waitEndTime;
  
  // The system time of the beging of last measure state.
  // Unit: milliseconds.
  // The overflow duration of millis() is about 50-days,
  // so the overflow problem is not considerd here.
  unsigned long long _measureBeginTime;


  report_t _currentReport;
};

#endif