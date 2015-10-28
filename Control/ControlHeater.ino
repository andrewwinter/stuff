//Variables for SMC
float PreviousTemperature1, PreviousTemperature2;
float lambda=0.01;
float error1, error2;
float error_dot1, error_dot2;
float sigma1, sigma2;

void controlheater()
{
  error1=Setpoint1-CalibratedTemperature1;
  error_dot1=-(CalibratedTemperature1 - PreviousTemperature1);
  sigma1=lambda*error1+error_dot1;
  if (sigma1>0 && Setpoint1 > CalibratedTemperature1)
  { 
    digitalWrite(Heater1, HIGH);
  }
  else
  {
    digitalWrite(Heater1, LOW);
  }
  PreviousTemperature1 = CalibratedTemperature1;
  
  error2=Setpoint2-CalibratedTemperature2;
  error_dot2=-(CalibratedTemperature2 - PreviousTemperature2);
  sigma2=lambda*error2+error_dot2;
  if (sigma2>0 && Setpoint2 > CalibratedTemperature2 && digitalRead(Heater1) == LOW)
  { 
    digitalWrite(Heater2, HIGH);
  }
  else
  {
    digitalWrite(Heater2, LOW);
  }
  PreviousTemperature2 = CalibratedTemperature2;
}
