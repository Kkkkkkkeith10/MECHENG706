//this file implements the robots behaviour during the running state

STATE running()
{
  static unsigned long previous_millis_battery_check;
  static unsigned long previous_millis;

  //check battery health every 1s
  if (millis() - previous_millis_battery_check > 1000)
  {
    previous_millis_battery_check = millis(); //previous time the battery was checked
      //check battery is ok
    #ifndef NO_BATTERY_V_OK
      if (!is_battery_voltage_OK())
        return STOPPED;
    #endif
  }
  
  execute_movement_phase();

  // if (millis() - previous_millis > 400)
  // {
  //   Serial1.println(movement_phase);
  // }


  return RUNNING;
}