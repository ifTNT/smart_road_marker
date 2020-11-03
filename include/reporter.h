#include "report_struct.h"

class Repoter{
  public:
  
  /*
   * This funcation is called at setup().
   * And it should perform any required initialization of underlying transmiter.
   */
  virtual int init() = 0;
  
  /*
   *
   */
  virtual int publish(report_t) = 0;
  
  /*
   * Get a human readable error message form given error code
   */
  virtual const char* getErrMessage(int) = 0;
};