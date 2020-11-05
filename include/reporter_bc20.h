#ifndef REPORTER_BC20_H
#define REPORTER_BC20_H

#include "reporter.h"
#include "system.h"
#include <HardwareSerial.h>
#include <Arduino.h>

#define DEBUG_BC20

/*
 * The implementation class of repoter on BC20 NB-IoT module.
 * If you want to know the descrption of each function,
 * reference to reporter.h
 */
class ReporterBC20: public Repoter{
  public:

  ReporterBC20(HardwareSerial&);
  int init();
  int publish(report_t);
  const char* getErrMessage(int);

  private:
  HardwareSerial& _port;
  int _waitForSerial(String, const unsigned long long);
  void _disconnectMQTT();
  void _closeMQTTSocket();
};

#endif