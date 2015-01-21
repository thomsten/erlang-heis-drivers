// Dummy functions for testing erlang interface
#include "elev_test.h"
// Number of signals and lamps on a per-floor basis (excl sensor)
#define N_BUTTONS 3

void elev_set_speed(int speed)
{
  speed = 42;
}



void elev_set_door_open_lamp(int value)
{
  value = 42;
}
 


int elev_get_obstruction_signal(void)
{
  return 1;
}



int elev_get_stop_signal(void)
{
  return 1;
}



void elev_set_stop_lamp(int value)
{
  value = 42;
}



int elev_get_floor_sensor_signal(void)
{
  return 2;
}



void elev_set_floor_indicator(int floor)
{
  floor = 42;
}



int elev_get_button_signal(elev_button_type_t button, int floor)
{
  return 1;
}



void elev_set_button_lamp(elev_button_type_t button, int floor, int value)
{
  button = BUTTON_COMMAND;
  floor = 42;
  value = 42;
}



int elev_init(void)
{
    return 1;
}



