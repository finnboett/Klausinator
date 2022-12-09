i/////////////////////////////////////////////
//             Definitionen                //
////////////////////////////////////////////

#define RECHTS  IN_1
#define MITTE   IN_2
#define LINKS   IN_3
#define DIST    IN_4

/////////////////////////////////////////////
//         Globale Variablen               //
////////////////////////////////////////////

int counter = 0;

/////////////////////////////////////////////
//             Funktionen                 //
////////////////////////////////////////////

void right_turn()
{
  OnRev(OUT_A, 100);
  OnFwd(OUT_C, 100);
}

void left_turn()
{
  OnFwd(OUT_A, 100);
  OnRev(OUT_C, 100);
}

void drive_straight()
{
 OnFwd(OUT_A, 40);
 OnFwd(OUT_C, 40);
}

void reverse_straight()
{
  OnRev(OUT_A, 50);
  OnRev(OUT_C, 50);
}

void turn_around()
{
  if (counter == 1)
  {
    OnRev(OUT_A, 100);
    OnFwd(OUT_C, 100);
    if (Sensor(RECHTS) < Sensor(MITTE))    // Wenn der rechte Sonsor wieder auf schwarz ist soll Klausi wieder der Linie folgen
    {
      PlaySound(SOUND_DOWN);
      counter = 2;
      until (counter == 2);
    }
    until(counter == 2);
  }

}

void break_wait()
{
  if (counter == 3)
  {
    OnRev(OUT_A, 0);
    OnFwd(OUT_C, 0);
    if (SensorUS(DIST) > 30)
    {
      counter = 4;
      until (counter == 4);
    }
    until (counter = 4);
  }
}

void counter_addition()
{
 if (SensorUS(DIST) < 30 && counter == 0)   //Wenn der Sensor das erste mal eine Wand die näher als 30 ist wird der nächste schritt ausgelöst
  {
    PlaySound(SOUND_UP);
    counter = 1;
    until (counter == 1);
  }
  if (SensorUS(DIST) < 30 && counter == 2)     // das Zweite mal wenn Klausi etwas vor der Nase hat soll er anhalten, bis die SChranke wieder auf geht.
  {
    PlaySound(SOUND_DOWN);
    counter = 3;
    until (counter = 3);
  } 
}

void liniefolgen()  // schwarz ist kleiner!!!
{
  //Geradeaus fahren, wenn alle weiß sind
  if (Sensor(MITTE) > 20 && Sensor(LINKS) > 20 && Sensor(RECHTS) > 20)
  {
    drive_straight();
    counter_addition();
    until (Sensor(MITTE) < 25 || Sensor(LINKS) < 25 || Sensor(RECHTS) < 25);  // wenn dann wieder Linie da ist soll er Normal der Linie Folgen
  }

    //Geradeausfahren, wenn der mittlere Sensor auf dr schwarzen Linie ist
  while (Sensor(MITTE) < Sensor(RECHTS) && Sensor(MITTE) < Sensor(LINKS))
   {
    drive_straight();
    if (SensorUS(DIST) < 30 && counter == 0)   //Wenn der Sensor das erste mal eine Wand die näher als 30 ist wird der nächste schritt ausgelöst
      {
       PlaySound(SOUND_UP);
       counter = 1;
       break;
      }
    if (SensorUS(DIST) < 30 && counter == 2)     // das Zweite mal wenn Klausi etwas vor der Nase hat soll er anhalten, bis die SChranke wieder auf geht.
      {
       counter = 3;
       until (counter = 3);
       break;
      }
   }

  //Wenn der rechte Sensor auf der schwarzen Linie ist, nach rechts drehen
  if (Sensor(MITTE) >= Sensor(RECHTS))
   {                                            //Rechts
    right_turn();
    counter_addition();
    until (Sensor(MITTE) < Sensor(RECHTS) && Sensor(MITTE) < Sensor(LINKS));
   }

  //Wenn der linke Sensor auf der schwarzen Linie ist, nach links drehen
  if (Sensor(MITTE) >= Sensor(LINKS))            //Links
   {
    left_turn();
    counter_addition();
    until (Sensor(MITTE) < Sensor(RECHTS) && Sensor(MITTE) < Sensor(LINKS));
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
  SetSensorUltrasonic(DIST);
  //SetSensorMode(IN_4, SENSOR_MODE_PERCENT);

  while (true){
    //Entfernung vom Ultraschallsensor auslesen
    int us_dist = SensorUS(IN_4);


    //Wenn der Weg frei ist, der Linie folgen
    while (counter == 0)    //Klausi fährt als erstes normal 
    {
      liniefolgen();
    }

    //Bei erstem Hindernis umdrehen und Counter erhöhen
    while (counter == 1)
    {
      turn_around();
    }
    
    while (counter == 2)
    {
      liniefolgen();
    }

    //Bei zweitem Hindernis für 5 Sekunden warten
    while (counter == 3)
    {
      break_wait();
    }
    
    while (counter == 4)
      {
      liniefolgen();
      }
  }
  
}