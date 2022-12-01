#define RECHTS  IN_1
#define MITTE   IN_2
#define LINKS   IN_3

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
  until (Sensor(RECHTS) < Sensor(MITTE));
}


void liniefolgen()
{
  while (Sensor(MITTE) < Sensor(RECHTS) && Sensor(MITTE) < Sensor(LINKS))
   {
    drive_straight();
   }

  if (Sensor(MITTE) >= Sensor(RECHTS))
   {                                            //Rechts
   right_turn();
   until (Sensor(MITTE) < Sensor(RECHTS) && Sensor(MITTE) < Sensor(LINKS));
   }


  if (Sensor(MITTE) >= Sensor(LINKS))            //Links
   {
    left_turn();
    until (Sensor(MITTE) < Sensor(RECHTS) && Sensor(MITTE) < Sensor(LINKS));
   }

  while (Sensor(MITTE) == Sensor(RECHTS) && Sensor(MITTE) == Sensor(LINKS))
   {
    reverse_straight();
   }
}


task main()
{
 SetSensorLight(RECHTS);
 SetSensorLight(MITTE);
 SetSensorLight(LINKS);
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
