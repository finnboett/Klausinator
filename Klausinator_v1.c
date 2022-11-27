void right_turn()
{
  OnFwd(OUT_A, 5);
  OnFwd(OUT_C, 45);
}


void left_turn()
{
  OnFwd(OUT_A, 45);
  OnFwd(OUT_C, 5);
}


void drive_straight()
{
 OnFwd(OUT_A, 30);
 OnFwd(OUT_C, 30);
}


void reverse_straight()
{
  OnBwd(OUT_A, 20);
  OnBwd(OUT_C, 20);
}


void turn_around()
{
  while (Sensor(IN_1) > Sensor(IN_2) && Sensor(IN_1 > Sensor(IN_3)))
  {
  right_turn();
  }
}


void liniefolgen()
{
  while (Sensor(IN_2) > Sensor(IN_1) && Sensor(IN_2) > Sensor(IN_3))
   {
    drive_straight();
   }

  if (Sensor(IN_2) <= Sensor(IN_1))
   {                                            //Rechts
   right_turn();
   }
   until (Sensor(IN_2) > Sensor(IN_1) && Sensor(IN_2) > Sensor(IN_3));


  if (Sensor(IN_2) <= Sensor(IN_3))            //Links
   {
    left_turn();
   }
   until (Sensor(IN_2) > Sensor(IN_1) && Sensor(IN_2) > Sensor(IN_3));

  if (Sensor(IN_2) == Sensor(IN_1) && Sensor(IN_2) == Sensor(IN_3))
   {
    reverse_straight();
   }

}


task main()
{
 SetSensorLight(IN_1);
 SetSensorLight(IN_2);
 SetSensorLight(IN_3);
 SetSensorDistance(IN_4);

 while (SensorDistance(IN_4) > entfernung)
 {
 liniefolgen();
 }

 if (SensorDistance(IN_4) < entfernung)
  {
    turn_around();
  }

}
