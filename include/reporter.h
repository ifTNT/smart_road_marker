#ifndef REPORTER_H
#define REPORTER_H

#include "report_struct.h"

class Repoter{
  public:
  
  /*
   * This funcation is called at setup().
   * And it should perform any required initialization of underlying transmiter.
   * Return 0 if succeed. Otherwise, return an error code.
   */
  virtual int init() = 0;
  
  /*
   * Transmit the given report to backend.
   * Return 0 if succeed. Otherwise, return an error code.
   */
  virtual int publish(report_t) = 0;
  
  /*
   * Get a human readable error message form given error code
   */
  virtual const char* getErrMessage(int) = 0;
};

#endif