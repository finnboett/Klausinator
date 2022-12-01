int counter = 0;

void right_turn()
{
  OnRev(OUT_A, 45);
  OnFwd(OUT_C, 45);
}


void left_turn()
{
  OnFwd(OUT_A, 45);
  OnRev(OUT_C, 45);
}


void drive_straight()
{
 OnFwd(OUT_A, 35);
 OnFwd(OUT_C, 35);
}


void reverse_straight()
{
  OnRev(OUT_A, 35);
  OnRev(OUT_C, 35);
}


void turn_around()
{
  OnFwd(OUT_C, 35);
  OnRev(OUT_A, 35);
  until (Sensor(IN_1) < Sensor(IN_2));
}


void liniefolgen()
{
  while (Sensor(IN_2) < Sensor(IN_1) && Sensor(IN_2) < Sensor(IN_3))
   {
    drive_straight();
   }

  if (Sensor(IN_2) >= Sensor(IN_1))
   {                                            //Rechts
   right_turn();
   until (Sensor(IN_2) < Sensor(IN_1) && Sensor(IN_2) < Sensor(IN_3));
   }


  if (Sensor(IN_2) >= Sensor(IN_3))            //Links
   {
    left_turn();
    until (Sensor(IN_2) < Sensor(IN_1) && Sensor(IN_2) < Sensor(IN_3));
   }

  while (Sensor(IN_2) == Sensor(IN_1) && Sensor(IN_2) == Sensor(IN_3))
   {
    reverse_straight();
   }
}


task main()
{
 SetSensorLight(IN_1);
 SetSensorLight(IN_2);
 SetSensorLight(IN_3);
 SetSensorLowspeed(IN_4);
 SetSensorMode(IN_4, SENSOR_MODE_BOOL);
 

while (true){
int us_distance = SensorUS(IN_4);
 if (us_distance < 500)
 {
  liniefolgen();
 }

 if ((us_distance > 500) && counter == 0)
  {
    PlaySound(SOUND_UP);
    turn_around();
    counter += 1;
  }                ;
  
  if ((us_distance > 500) && counter == 1 )
  {
   Wait(5000);
   counter += 1;
  }
  }
}
