//this file implements the robots behaviour during the running state

STATE running()
{
  static unsigned long previous_millis_battery_check;
  static unsigned long previous_millis_gyro_read;
  static unsigned long previous_millis_ir_read;
  static unsigned long previous_millis_sonar_read;

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
  //read gyro every 10ms
  if (millis() - previous_millis_gyro_read > 10)
  { // Arduino style 500ms timed execution statement
    previous_millis_gyro_read = millis(); //previous time the gryo was read
    #ifndef NO_READ_GYRO
    //read gyro here
    //GYRO_reading();
    #endif
  }
  //read IR every 100ms
  if (millis() - previous_millis_ir_read > 100)
  {

  }

  //read sonar every 110ms
  if (millis() - previous_millis_sonar_read > 110)
  {
      #ifndef NO_HC - SR04
        HC_SR04_range(); //sonar read
    #endif
  }


  execute_movement_phase();

  return RUNNING;
}