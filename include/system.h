#ifndef SMART_ROAD_MARK_SYSTEM_H
#define SMART_ROAD_MARK_SYSTEM_H

#include "car_sensor.h"
#include "reporter.h"
#include "report_struct.h"

/* =========================
 *  Constant section
 * =========================
 */

// The expeted duration between report publishment
// Unit: miliseconds
#define REPORT_DURATION 30000l

// Define the debug output macro to decopule the debug purpose
// from the serial port object.
#define DEBUG_OUT Serial

/* ============================
 *  External defined varibles
 * ============================
 */

// Defination in system.cpp
extern CarSensor* carSensor;

// Defination in system.cpp
extern Repoter* repoter;

// Defination in system.cpp
extern unsigned long long lastPublishTime;

// Defination in system.cpp
extern int err;

#endif