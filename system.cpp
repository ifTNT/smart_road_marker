#include "include/system.h"
#include "include/car_sensor_ir.h"

/* =========================
 *  System module section
 * =========================
 */

// The sensor that return the traffic and average speed data.
CarSensor* carSensor = new CarSensorIR;

/* =========================
 *  Global varible section
 * ========================= 
 */

// The system time of last report publishment
unsigned long long lastPublishTime;

// The error code storage place which is frequently used in the code.
int err = 0;