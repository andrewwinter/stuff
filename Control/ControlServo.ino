const int SERVO_LIMIT = 10;
const int SERVO_COUNTER_LIMIT = SERVO_LIMIT*100;

int measurecurrent()
{
  //return(analogRead(A3));
}

int controlHopValves()
{
  //Only one opened
  if (Valve_hop1state && !Valve_hop2state && !Valve_hop3state && !Valve_hop4state)
  {
    int pos1 = 150;
    controlValve(Valve_hop1, pos1);
    Serial.print("Hop1 "); Serial.println(pos1);
  }
  else if (!Valve_hop1state && Valve_hop2state && !Valve_hop3state && !Valve_hop4state)
  {
    int pos1 = 140;
    controlValve(Valve_hop2, pos1);
    Serial.print("Hop2 "); Serial.println(pos1);
  }
  else if (!Valve_hop1state && !Valve_hop2state && Valve_hop3state && !Valve_hop4state)
  {
    int pos1 = 130;
    controlValve(Valve_hop3, pos1);
    Serial.print("Hop3 "); Serial.println(pos1);
  }
  else if (!Valve_hop1state && !Valve_hop2state && !Valve_hop3state && Valve_hop4state)
  {
    int pos1 = 120;
    controlValve(Valve_hop4, pos1);
    Serial.print("Hop4 "); Serial.println(pos1);
  }
  //Two opened
  else if (Valve_hop1state && Valve_hop2state && !Valve_hop3state && !Valve_hop4state)
  {
    int pos1 = 150;
    int pos2 = 120;
    controlValve(Valve_hop2, pos2);
    controlValve(Valve_hop1, pos1);
    Serial.print("Hop1 "); Serial.println(pos1);
    Serial.print("Hop2 "); Serial.println(pos2);
  }
  else if (Valve_hop1state && !Valve_hop2state && Valve_hop3state && !Valve_hop4state) 
  {
    int pos1 = 140;
    int pos3 = 130;
    controlValve(Valve_hop3, pos3);
    controlValve(Valve_hop1, pos1);
    Serial.print("Hop1 "); Serial.println(pos1);
    Serial.print("Hop3 "); Serial.println(pos3);
  }
  else if (Valve_hop1state && !Valve_hop2state && !Valve_hop3state && Valve_hop4state) 
  {
    int pos1 = 140;
    int pos4 = 130;
    controlValve(Valve_hop4, pos4);
    controlValve(Valve_hop1, pos1);
    Serial.print("Hop1 "); Serial.println(pos1);
    Serial.print("Hop4 "); Serial.println(pos4);
  }
  else if (!Valve_hop1state && Valve_hop2state && Valve_hop3state && !Valve_hop4state)
  {
    int pos2 = 140;
    int pos3 = 130;
    controlValve(Valve_hop3, pos3);
    controlValve(Valve_hop2, pos2);
    Serial.print("Hop2 "); Serial.println(pos2);
    Serial.print("Hop3 "); Serial.println(pos3);
  }
  else if (!Valve_hop1state && Valve_hop2state && !Valve_hop3state && Valve_hop4state) 
  {
    int pos2 = 140;
    int pos4 = 120;
    controlValve(Valve_hop4, pos4);
    controlValve(Valve_hop2, pos2);
    Serial.print("Hop2 "); Serial.println(pos2);
    Serial.print("Hop4 "); Serial.println(pos4);
  }
  else if (!Valve_hop1state && !Valve_hop2state && Valve_hop3state && Valve_hop4state) 
  {
    int pos3 = 140;
    int pos4 = 120;
    controlValve(Valve_hop4, pos4);
    controlValve(Valve_hop3, pos3);
    Serial.print("Hop3 "); Serial.println(pos3);
    Serial.print("Hop4 "); Serial.println(pos4);
  }
  //3 opened
  else if (Valve_hop1state && Valve_hop2state && Valve_hop3state && !Valve_hop4state)
  {
    int pos1 = 130;
    int pos2 = 115;
    int pos3 = 100;
    controlValve(Valve_hop3, pos3);
    controlValve(Valve_hop2, pos2);
    controlValve(Valve_hop1, pos1);
    Serial.print("Hop1 "); Serial.println(pos1);
    Serial.print("Hop2 "); Serial.println(pos2);
    Serial.print("Hop3 "); Serial.println(pos3);
  }
  else if (Valve_hop1state && Valve_hop2state && !Valve_hop3state && Valve_hop4state)
  {
    int pos1 = 130;
    int pos2 = 130;
    int pos4 = 110;
    controlValve(Valve_hop4, pos4);
    controlValve(Valve_hop2, pos2);
    controlValve(Valve_hop1, pos1);
    Serial.print("Hop1 "); Serial.println(pos1);
    Serial.print("Hop2 "); Serial.println(pos2);
    Serial.print("Hop4 "); Serial.println(pos4);
  }
  else if (Valve_hop1state && !Valve_hop2state && Valve_hop3state && Valve_hop4state)
  {
    int pos1 = 130;
    int pos3 = 130;
    int pos4 = 110;
    controlValve(Valve_hop4, pos4);
    controlValve(Valve_hop3, pos3);
    controlValve(Valve_hop1, pos1);
    Serial.print("Hop1 "); Serial.println(pos1);
    Serial.print("Hop3 "); Serial.println(pos3);
    Serial.print("Hop4 "); Serial.println(pos4);
  }
  else if (!Valve_hop1state && Valve_hop2state && Valve_hop3state && Valve_hop4state)
  {
    int pos2 = 130;
    int pos3 = 130;
    int pos4 = 110;
    controlValve(Valve_hop4, pos4);
    controlValve(Valve_hop3, pos3);
    controlValve(Valve_hop2, pos2);
    Serial.print("Hop2 "); Serial.println(pos2);
    Serial.print("Hop3 "); Serial.println(pos3);
    Serial.print("Hop4 "); Serial.println(pos4);
  }
  else if (Valve_hop1state && Valve_hop2state && Valve_hop3state && Valve_hop4state)
  {
    int pos1 = 130;
    int pos2 = 120;
    int pos3 = 110;
    int pos4 = 20;
    controlValve(Valve_hop4, pos4);
    controlValve(Valve_hop3, pos3);
    controlValve(Valve_hop2, pos2);
    controlValve(Valve_hop1, pos1);
    Serial.print("Hop1 "); Serial.println(pos1);
    Serial.print("Hop2 "); Serial.println(pos2);
    Serial.print("Hop3 "); Serial.println(pos3);
    Serial.print("Hop4 "); Serial.println(pos4);
  }
  else
  {
    Serial.println("All closed");
  }
}

bool controlValve(short pos, int pin)
{
  valve.attach(pin);
  valve.write(pos);
  //delay(1000);
  servo_delay();
  valve.detach();
}

bool openvalve(int pin)
{
  int pos=20;
  switch (pin)
  {
    //Mashing valve
    case 71:
      pos=140;
      break;
    //Boiling valve
    case 24:
    {
      if (Valve_mashoutstate == true)
        pos = 110;
      else
        pos = 20;
      break;
    }
    //Hop 1
    case 26:
      controlHopValves();
      break;
    //Hop2
    case 27:
      controlHopValves();
      break;
    //Hop3
    case 28:
      controlHopValves();
      break;
    //Hop4
    case 29:
      controlHopValves();
      break;
  }
  /*if (Valve_mashoutstate==true && Valve_boilstate==true)
  {
    valve.attach(22);
    valve.write(130);
    delay(1000);
    valve.detach();
    valve.attach(24);
    valve.write(20);
    delay(1000);
    valve.detach();
  }
  else
  {*/
    valve.attach(pin);
    valve.write(pos);
    /*while(measurecurrent()>200)
    {
      pos-=10;
      valve.write(pos);
      delay(50);
    }
    valve.detach();
    if (pos>0) return true;
    else return false;*/
    //delay(1000);
    servo_delay();
    valve.detach();
  //}
}

bool closevalve(int pin)
{
  valve.attach(pin);
  //Serial.println("Servo attached");
  int pos=200;
  valve.write(pos);
  /*while(measurecurrent()<400)
  {
    pos+=10;
    valve.write(pos);
    delay(50);
  }
  valve.detach();
  if (pos<255) return true;
  else return false;*/
  //delay(1000);
  servo_delay();
  valve.detach();
  //Serial.println("Servo detached");
}

void servo_delay()
{
  int counter = 0;
  int start_value = analogRead(A3);
  int value = 0;

  while(true)
  {
    value = analogRead(A3);
    if(abs(value - start_value)<=SERVO_LIMIT)  
    {
      counter++;  
    }

    if(counter==SERVO_COUNTER_LIMIT)
    {
      break;
    }
  }
}

  
