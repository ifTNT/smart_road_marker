#include "include/reporter_bc20.h"

ReporterBC20::ReporterBC20(HardwareSerial& port): _port(port){

}

int ReporterBC20::init(){
  return 0;
}

int ReporterBC20::publish(report_t){
  return 0;
}
const char* ReporterBC20::getErrMessage(int errCode){
  switch(errCode){
    case 0: return "Succeed";
    default: return "Unknown error code";
  }
}