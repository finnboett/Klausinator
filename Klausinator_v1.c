/////////////////////////////////////////////
//             Definitionen                //
////////////////////////////////////////////

#define RECHTS  IN_1
#define MITTE   IN_2
#define LINKS   IN_3

/////////////////////////////////////////////
//         Globale Variablen               //
////////////////////////////////////////////

int counter = 0;

/////////////////////////////////////////////
//             Funktionen                 //
////////////////////////////////////////////

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
  //Geradeausfahren, wenn der mittlere Sensor auf dr schwarzen Linie ist
  while (Sensor(MITTE) < Sensor(RECHTS) && Sensor(MITTE) < Sensor(LINKS))
   {
    drive_straight();
   }

  //Wenn der rechte Sensor auf der schwarzen Linie ist, nach rechts drehen
  if (Sensor(MITTE) >= Sensor(RECHTS))
   {                                            //Rechts
    right_turn();
    until (Sensor(MITTE) < Sensor(RECHTS) && Sensor(MITTE) < Sensor(LINKS));
   }

  //Wenn der linke Sensor auf der schwarzen Linie ist, nach links drehen
  if (Sensor(MITTE) >= Sensor(LINKS))            //Links
   {
    left_turn();
    until (Sensor(MITTE) < Sensor(RECHTS) && Sensor(MITTE) < Sensor(LINKS));
   }

  //Rückwärts fahren, wenn alle Sensorwerte gleich sind
  while (Sensor(MITTE) == Sensor(RECHTS) && Sensor(MITTE) == Sensor(LINKS))
   {
    reverse_straight();
   }
}

/////////////////////////////////////////////
//             Main Funktion              //
////////////////////////////////////////////

task main()
{
  //Sensoren Initalisieren
  SetSensorLight(RECHTS);
  SetSensorLight(MITTE);
  SetSensorLight(LINKS);
  SetSensorLowspeed(IN_4);
  SetSensorMode(IN_4, SENSOR_MODE_BOOL);
  
  while (true){
    //Entfernung vom Ultraschallsensor auslesen
    int us_distance = SensorUS(IN_4);
    
    //Wenn der weg Frei ist, der Linie folgen
    if (us_distance < 500)
    {
      liniefolgen();
    }
    
    //Bei erstem Hindernis Umdrehen und Counter erhöhen
    if ((us_distance > 500) && counter == 0)
    {
      PlaySound(SOUND_UP);
      turn_around();
      counter += 1;
    }                ;
    
    //Bei zweitem Hindernis für 5 Sekunden warten
    if ((us_distance > 500) && counter == 1 )
    {
      Wait(5000);
      counter += 1;
    }
    
    //Was passiert, wenn Klausinator auf ein Hindernis trifft und der Counter größer als 1 ist?
  }
}
