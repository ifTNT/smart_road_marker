#ifndef SMART_ROAD_MARK_SYSTEM_H
#define SMART_ROAD_MARK_SYSTEM_H

#include "car_sensor.h"
#include "report.h"

/* =========================
 *  Constant section
 * =========================
 */

// The expeted duration between report transmissions
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
extern unsigned long long lastReportTime;

#endif