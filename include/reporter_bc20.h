#ifndef REPORTER_BC20_H
#define REPORTER_BC20_H

#include "reporter.h"

/*
 * The implementation class of repoter on BC20 NB-IoT module.
 * If you want to know the descrption of each function,
 * reference to reporter.h
 */
class ReporterBC20: public Repoter{
  public:

  int init();
  int publish(report_t);
  const char* getErrMessage(int);
};

#endif