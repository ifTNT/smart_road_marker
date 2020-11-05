#include "include/reporter_bc20.h"
#include "include/cht_iot_api_key.h"

ReporterBC20::ReporterBC20(HardwareSerial& port): _port(port){

}

int ReporterBC20::init(){
  int err;

  _port.begin(9600);

  // Use AT to ensure BC20 is woke up.
  while(1){
    _port.println("AT");
#ifdef DEBUG_BC20
    DEBUG_OUT.print("[BC20] ");
    DEBUG_OUT.println("Sent AT to BC20. Waiting for reply");
#endif
    if(_waitForSerial("OK", 200)==0) break;
  }

  // Disable command displaying
  _port.println("ATE0");
#ifdef DEBUG_BC20
    DEBUG_OUT.print("[BC20] ");
    DEBUG_OUT.println("Disabling command displaying. Waiting for reply");
#endif
  if((err=_waitForSerial("OK", 200))!=0){
#ifdef DEBUG_BC20
    DEBUG_OUT.print("[BC20] ");
    DEBUG_OUT.print("Disable command displaying failed. The error message: ");
    DEBUG_OUT.println(getErrMessage(err));
#endif
  }

  // Disable device sleeping
  _port.println("AT+QSCLK=0");
#ifdef DEBUG_BC20
    DEBUG_OUT.print("[BC20] ");
    DEBUG_OUT.println("Disabling device sleeping. Waiting for reply");
#endif
  if((err=_waitForSerial("OK", 200))!=0){
#ifdef DEBUG_BC20
    DEBUG_OUT.print("[BC20] ");
    DEBUG_OUT.print("Disable device sleeping failed. The error message: ");
    DEBUG_OUT.println(getErrMessage(err));
#endif
  }

  // Wait for device to registered to network and get IP address.
#ifdef DEBUG_BC20
      DEBUG_OUT.print("[BC20] ");
      DEBUG_OUT.print("Waiting for device to be registered to network: ");
#endif
  while(1){
    _port.println("AT+CGPADDR?");
    if((err=_waitForSerial("OK", 1000))!=0){
#ifdef DEBUG_BC20
      DEBUG_OUT.print(".");
#endif
    }else{
#ifdef DEBUG_BC20
      DEBUG_OUT.println("registered");
#endif
      break;
    }

    // Disconnect any potential MQTT socket
    _disconnectMQTT();
  }

  return 0;
}

int ReporterBC20::publish(report_t report){
  int err;

  // Open the MQTT socket to iot.cht.com.tw
  _port.println("AT+QMTOPEN=0,\"203.75.129.103\",1883");
#ifdef DEBUG_BC20
  DEBUG_OUT.print("[BC20] ");
  DEBUG_OUT.println("Send MQTT socket creation command.");
#endif
  if((err=_waitForSerial("+QMTOPEN: 0,0", 1000))!=0){
#ifdef DEBUG_BC20
    DEBUG_OUT.print("[BC20] ");
    DEBUG_OUT.print("Opening MQTT socket failed. The error message: ");
    DEBUG_OUT.println(getErrMessage(err));
#endif
    return err;
  }

  // Send connection message to MQTT
  _port.print("AT+QMTCONN=0,\"bc20test\",\"");
  _port.print(DEVICE_KEY);
  _port.print("\",\"");
  _port.print(DEVICE_KEY);
  _port.println("\"");
#ifdef DEBUG_BC20
  DEBUG_OUT.print("[BC20] ");
  DEBUG_OUT.println("Send MQTT connection command.");
#endif
  if((err=_waitForSerial("+QMTCONN: 0,0,0", 1000))!=0){
#ifdef DEBUG_BC20
    DEBUG_OUT.print("[BC20] ");
    DEBUG_OUT.print("Sending MQTT connection message failed. The error message: ");
    DEBUG_OUT.println(getErrMessage(err));
#endif
    _disconnectMQTT();
    return err;
  }

  // Publish specified report via MQTT
  _port.print("AT+QMTPUB=0,0,0,0,\"/v1/device/24991697058/rawdata\",\"[{'id': 'speed','value': ['");
  _port.print(report.avgSpeed);
  _port.print("']},{'id': 'cars','value':['");
  _port.print(report.traffic);
  _port.println("']}]\"");
#ifdef DEBUG_BC20
  DEBUG_OUT.print("[BC20] ");
  DEBUG_OUT.println("Send MQTT publish command.");
#endif
  if((err=_waitForSerial("+QMTPUB: 0,0,0", 1000))!=0){
#ifdef DEBUG_BC20
    DEBUG_OUT.print("[BC20] ");
    DEBUG_OUT.print("Publish report failed. The error message: ");
    DEBUG_OUT.println(getErrMessage(err));
#endif
    _disconnectMQTT();
    return err;
  }

  _disconnectMQTT();

  return 0;
}
const char* ReporterBC20::getErrMessage(int errCode){
  switch(errCode){
    case 0: return "Succeed";
    case 1: return "Timeout without patten recognized";
    default: return "Unknown error code";
  }
}

void ReporterBC20::_disconnectMQTT(){
  // Close the connection
  _port.println("AT+QMTDISC=0");
#ifdef DEBUG_BC20
  DEBUG_OUT.print("[BC20] ");
  DEBUG_OUT.println("Send MQTT disconnection command.");
#endif
  if((err=_waitForSerial("+QMTDISC: 0,0", 1000))!=0){
#ifdef DEBUG_BC20
    DEBUG_OUT.print("[BC20] ");
    DEBUG_OUT.print("Close connection failed. The error message: ");
    DEBUG_OUT.println(getErrMessage(err));
#endif
  }
}

int ReporterBC20::_waitForSerial(String patten, const unsigned long long timeout){
  int returnCode = 1;
  _port.setTimeout(timeout);

  String resultFromSerial = _port.readString();
  if(resultFromSerial.indexOf(patten) != -1){
    returnCode = 0;
  }
#ifdef DEBUG_BC20_SERIAL
    DEBUG_OUT.print("[BC20] ");
    DEBUG_OUT.print("Received response: ");
    DEBUG_OUT.println(resultFromSerial);
#endif

  return returnCode;
}
