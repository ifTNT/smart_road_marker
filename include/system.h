#ifndef SMART_ROAD_MARK_SYSTEM_H
#define SMART_ROAD_MARK_SYSTEM_H

#include "car_sensor.h"
#include "reporter.h"
#include "report_struct.h"
#include <SoftwareSerial.h>

/* =========================
 *  Constant section
 * =========================
 */

// The expeted duration between report publishment
// Unit: miliseconds
#define REPORT_DURATION 30000l

// Define the debug output macro to decopule the debug purpose
// from the serial port object.
#define DEBUG_OUT DebugSoftwareSerial

// The buadrate that be used in debug serial port.
#define DEBUG_SERIAL_BUADRATE 115200

/* ============================
 *  External defined varibles
 *  Definations in system.cpp
 * ============================
 */

extern CarSensor* carSensor;
extern Repoter* repoter;
extern SoftwareSerial DebugSoftwareSerial;
extern unsigned long long lastPublishTime;
extern int err;

#endif