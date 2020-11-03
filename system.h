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
#define REPORT_DURATION 30000l;

// Defination in system.cpp
extern CarSensor* carSensor;

// Defination in system.cpp
extern unsigned long long lastReportTime;

#endif