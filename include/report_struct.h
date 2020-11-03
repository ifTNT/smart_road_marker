#ifndef REPORT_STRUCT_H
#define REPORT_STRUCT_H

/*
 * The structure to storage the report of car sensor.
 */
struct report_t{
  // The total traffic in the period.
  // Unit: Car(s)
  int traffic;

  // The average speed in the period.
  // Unit: km/hr
  float avgSpeed;
};

#endif