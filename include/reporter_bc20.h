#ifndef REPORTER_BC20_H
#define REPORTER_BC20_H

#include "reporter.h"
#include <HardwareSerial.h>

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
};

#endif