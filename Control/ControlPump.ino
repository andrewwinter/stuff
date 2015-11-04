const int counter_bonus_limit = 4;
int counter_limit = 12;
int half_counter_limit = int(counter_limit/2);
int mashing_counter = 0;
int boiling_counter = 0;

boolean Mashingtankempty()
{
  if (analogRead(Pump_current1) < 400)
  {
    mashing_counter++;
    Serial.println("Low current");
    if (mashing_counter == half_counter_limit)
    {
      digitalWrite(Pump_A, LOW);
      delay(1000);
      digitalWrite(Pump_A, HIGH);
    } 
    else if (mashing_counter == (counter_limit + counter_bonus_limit))
    {
      mashing_counter = 0;
      Serial.println("Empty");
      return true;
    }
  }
  else if(mashing_counter >= counter_limit && mashing_counter < (counter_limit + counter_bonus_limit))
  {
    counter_limit = mashing_counter;
    half_counter_limit = int(counter_limit/2);
    mashing_counter = 0;  
  }
  
  Serial.println("Check if empty");
  return false;
}

boolean Boilingtankempty()
{
  if (analogRead(Pump_current2) < 400)
  {
    boiling_counter++;
    Serial.println("Low current");
    if (boiling_counter == half_counter_limit)
    {
      digitalWrite(Pump_A, LOW);
      delay(1000);
      digitalWrite(Pump_A, HIGH);
    } 
    else if (boiling_counter == (counter_limit + counter_bonus_limit))
    {
      boiling_counter = 0;
      Serial.println("Empty");
      return true;
    }
  }
  else if(boiling_counter >= counter_limit && boiling_counter < (counter_limit + counter_bonus_limit))
  {
    counter_limit = boiling_counter;
    half_counter_limit = int(counter_limit/2);
    boiling_counter = 0;  
  }
  
  Serial.println("Check if empty");
  return false;
}

/*
boolean Mashingtankempty()
{
  boolean empty = false;
  if (analogRead(Pump_current1) < 400)
  {
    counter++;
    Serial.println("Low current");
    if (counter == 5)
    {
      digitalWrite(Pump_A, LOW);
      delay(1000);
      digitalWrite(Pump_A, HIGH);
    }
    if (counter == 10)
    {
      empty = true;
      counter = 0;
      Serial.println("Empty");
      return empty;
    }
  }
  Serial.println("Check if empty");
  return empty;
}
  
boolean Boilingtankempty()
{
  boolean empty = false;
  Serial.print("Current "); Serial.println(analogRead(Pump_current2));
  if (analogRead(Pump_current2) < 500)
  {
    counter++;
    Serial.println("Low current");
    if (counter == 5)
    {
      digitalWrite(Pump_B, LOW);
      delay(1000);
      digitalWrite(Pump_B, HIGH);
    }
    if (counter == 10)
    {
      empty = true;
      counter = 0;
      Serial.println("Empty");
      return empty;
    }
  }
  Serial.println("Check if empty");
  return empty;
}

/*void ControlPump1()
{
  int average = 0;
  for (int i=0; i<5; i++)
  {
    average += analogRead(Pump_current1);
    delay (20);
  }
  int averagecurrent = average/5;
  Serial.print("Av current ");
  Serial.println(averagecurrent);
  if (averagecurrent < 795)
  {
    analogWrite(Pump_A, currentPWM1 + 5);
    currentPWM1 += 5;
  }
  else if (averagecurrent > 805)
  {
    analogWrite(Pump_A, currentPWM1 - 5);
    currentPWM1 -= 5;
  }
  Serial.print("PWM1 ");
  Serial.println(currentPWM1);
}*/
