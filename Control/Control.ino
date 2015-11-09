#include <hx711.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <Servo.h>
#include <Wire.h> 

//Digital peripheries
OneWire  onewire(10);
OneWire  onewire2(12);
DallasTemperature Temperatures(&onewire);
DallasTemperature Temperatures2(&onewire2);
DeviceAddress Temp1, Temp2, Temp3;
Hx711 level(74, 75);
Servo valve;

int Setpoint1, Setpoint2;

//Pins
const int Valve_mash  = 71;
const int Valve_pump1 = 23;
const int Valve_boil  = 24;
const int Valve_pump2 = 25;
const int Valve_hop1  = 27;
const int Valve_hop2  = 26;
const int Valve_hop3  = 28;
const int Valve_hop4  = 29;
const int Valve_cool  = 73; 
const int Valve_outlet= 72;
const int Fan1        = 6;
const int Fan2        = 7;
const int Fan3        = 8;
const int Fan4        = 46;
const int Fan5        = 45;
const int Pump_A      = 2;
const int Pump_B      = 5;
const int Heater1     = 13;
const int Heater2     = 4;
//const int Led1        = 74;
//const int Led2        = 75;
const int Valve_inlet = 70;
const int Valve_current = A4;
const int Pump_current1 = A1;
const int Pump_current2 = A0;

const float WATER_LEVEL_TO_LITER = 35294.1;

long water_level_null, water_level;
double water_level_calibrated;
boolean water_level_condition, water_level_outlet_condition;
float water_level_setpoint;

//Main Variables
unsigned long ID = 1234567890;
double Temperature1, Temperature2, Temperature3;
double CalibratedTemperature1, CalibratedTemperature2;
short CurrentStep = 0;
int CurrentStepTime = 0;
boolean brewing = false;
boolean new_step_started = false; 
boolean Valve_inletstate, Valve_mashoutstate, Valve_boilstate, Valve_coolstate;
boolean Valve_hop1state, Valve_hop2state, Valve_hop3state, Valve_hop4state, Valve_outletstate, Ventilatorstate; 
boolean Valve_pump1state, Valve_pump2state, Pump_Astate, Pump_Bstate;
short numberofsteps = 23;
boolean paused_mashout_state, paused_boil_state, paused_hop1_state, paused_hop2_state, paused_hop3_state, paused_hop4_state, paused_cool_state, paused_outlet_state, paused_pump1_state, paused_pump2_state;

//Auxilliary variables
int retrythermometer = 0;
boolean maxpower = false;
long seconds, tempsecs, tempmins, temphours;
long start_seconds, current_seconds, current_start_seconds, paused_at_current_start_seconds, paused_at_current_seconds, timeremaining, paused_at;
int counter = 0;
int wlsetpoint;
int currentPWM1, currentPWM2;
long looptime = 0;
long last_pump_in_time = 0;
long last_loop_time = 0;

//Functions
void readserial(), controlheater();
boolean openvalve(short pin), closevalve(short pin), tankempty(short tank);
//int readlevel();

void setup() {
  // initialize serial communication:
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.println("Brewie v1.0");
  Serial.println("Copyright Brewie 2015");
  Serial1.println("Brewie v1.0 debug console");
  Serial1.println("Copyright Brewie 2015");
  senddata();
  pinMode(Valve_inlet, OUTPUT);
  pinMode(Fan1, OUTPUT);
  pinMode(Fan2, OUTPUT);
  pinMode(Fan3, OUTPUT);
  pinMode(Fan4, OUTPUT);
  pinMode(Fan5, OUTPUT);
  pinMode(Pump_A, OUTPUT);
  pinMode(Pump_B, OUTPUT);
  pinMode(Heater1, OUTPUT);
  pinMode(Heater2, OUTPUT);
  //digitalWrite(Led1, HIGH);
  
  //VEDD KI A KOMMENTET HA AKAROD HOGY MINDENT BEZARJON
  initialize();
  
  Temperatures.begin();
  Temperatures2.begin();
  while (Temperatures.getDeviceCount() == 0 && retrythermometer < 3) 
  {
    Temperatures.begin();
    retrythermometer++;
    delay(500);
  }
  Temperatures.getDeviceCount();
  Temperatures2.getAddress(Temp3, 0);
  Temperatures2.setResolution(Temp3, 12);
  if (!Temperatures.getDeviceCount()) {Serial.println("E006");}
  else Serial.println("OK");
  Temperatures.getAddress(Temp1, 0);
  Temperatures.getAddress(Temp2, 1);
  Temperatures.setResolution(Temp1, 12);
  Temperatures.setResolution(Temp2, 12);
  if (!Temperatures2.getDeviceCount()) {Serial.println("No secondary thermometer");}
  Temperatures.setWaitForConversion(false);
  Temperatures2.setWaitForConversion(false);
  Serial.print("Channel 1 parasite "); Serial.println(Temperatures.isParasitePowerMode());
  Serial.print("Channel 2 parasite "); Serial.println(Temperatures2.isParasitePowerMode());
  water_level_null = level.averageValue(10);
  Serial.print("Water level nullpoint: "); Serial.println(water_level_null);
}

void loop() 
{
  if (Serial.available() > 0)
  {
    readserial();
  }

  if(water_level_condition || water_level_outlet_condition)
  {
    if ((water_level_condition && (water_level_calibrated > (water_level_setpoint - 1))) || 
        (water_level_outlet_condition && ((water_level_calibrated < water_level_setpoint) || Boilingtankempty())))
    {
      new_step_started = true;
    }
  }
  
  if ((millis() - last_loop_time)>1000)
  {
    //Never switch on both heat elements
    last_loop_time = millis();
    looptime = millis();
    if (digitalRead(Heater1) == true) digitalWrite(Heater2, LOW);
    else if (digitalRead(Heater2) == true) digitalWrite(Heater1, LOW);
    readtemp();
    senddata();
    water_level = level.averageValue(2);
    water_level_calibrated = (water_level - water_level_null)/WATER_LEVEL_TO_LITER;
    if (maxpower == false)
    {
      controlheater();
    }
    else 
    {
      digitalWrite(Heater2, HIGH);
    }
    if (brewing==true)
    {
      Serial.print("R107 ");
      Serial.println(CurrentStep + 1);
      Brewing();
    }
    else Serial.println("R107 0");
    Serial.print("Temperature inside: "); Serial.println(Temperature3);
    Serial.print("Water level delta: "); Serial.println(water_level - water_level_null);
    Serial.print("Water level: "); Serial.print(water_level_calibrated); Serial.println(" liter");
    looptime -= millis();
    Serial.print("Loop time "); Serial.println(-looptime);
    //digitalWrite(Led1, !digitalRead(Led1));
  }
}

void readtemp()
{
  //Serial.println("Getting temperatures");
  //int looptime = millis();
  Temperatures.requestTemperatures();
  Temperature1 = Temperatures.getTempC(Temp1);
  Temperature2 = Temperatures.getTempC(Temp2);
  //Serial.print("Raw temp 1"); Serial.println(Temperature1);
  //Serial.print("Raw temp 2"); Serial.println(Temperature2);
  CalibratedTemperature1 = 9.825*Temperature1*pow(Temperature1, 0.0382);
  CalibratedTemperature2 = 9.825*Temperature2*pow(Temperature2, 0.0382);
  Temperatures2.requestTemperatures();
  Temperature3 = Temperatures2.getTempC(Temp3);
  //Serial.print("Got temperatures in "); Serial.println(millis()-looptime);
}

void initialize()
{
  digitalWrite(Valve_inlet, LOW);
  digitalWrite(Fan1, LOW);
  digitalWrite(Fan2, LOW);
  digitalWrite(Fan3, LOW);
  digitalWrite(Fan4, LOW);
  digitalWrite(Fan5, LOW);
  digitalWrite(Pump_A, LOW);
  digitalWrite(Pump_B, LOW);
  digitalWrite(Heater1, LOW);
  digitalWrite(Heater2, LOW);
  closevalve(Valve_outlet); Valve_outletstate = false; Serial1.println("Outlet valve off");
  closevalve(Valve_mash); Valve_mashoutstate = false; Serial1.println("Mashing valve off");
  closevalve(Valve_boil); Valve_boilstate = false; Serial1.println("Boiling valve off");
  closevalve(Valve_hop1); Valve_hop1state = false; Serial1.println("Hop valve 1 off");
  closevalve(Valve_hop2); Valve_hop2state = false; Serial1.println("Hop valve 2 off");
  closevalve(Valve_hop3); Valve_hop3state = false; Serial1.println("Hop valve 3 off");
  closevalve(Valve_hop4); Valve_hop4state = false; Serial1.println("Hop valve 4 off");
  closevalve(Valve_cool); Valve_coolstate = false; Serial1.println("Cooling valve off");
  
  closevalve(Valve_pump1); Valve_pump1state = false; Serial1.println("One way valve 1 off");
  closevalve(Valve_pump2); Valve_pump2state = false; Serial1.println("One way valve 2 off");
  Setpoint1 = -2000;
  Setpoint2 = -2000;
}

void pause_brew()
{
  if (Valve_mashoutstate) 
  {
    paused_mashout_state = true;
    closevalve(Valve_mash); 
    Serial1.println("Mashing valve off");
  }
  if (Valve_boilstate) 
  {
    paused_boil_state = true;
    closevalve(Valve_boil); 
    Serial1.println("Boiling valve off");
  }
  if (Valve_hop1state) 
  {
    paused_hop1_state = true;
    closevalve(Valve_hop1); 
    Serial1.println("Hop valve 1 off");
  }
  if (Valve_hop2state) 
  {
    paused_hop2_state = true;
    closevalve(Valve_hop2); 
    Serial1.println("Hop valve 2 off");
  }
  if (Valve_hop3state) 
  {
    paused_hop3_state = true;
    closevalve(Valve_hop3); 
    Serial1.println("Hop valve 3 off");
  }
  if (Valve_hop4state) 
  {
    paused_hop4_state = true;
    closevalve(Valve_hop4); 
    Serial1.println("Hop valve 4 off");
  }
  if (Valve_coolstate) 
  {
    paused_cool_state = true;
    closevalve(Valve_cool); 
    Serial1.println("Cooling valve off");
  }
  if (Valve_outletstate) 
  {
    paused_outlet_state = true;
    closevalve(Valve_outlet); 
    Serial1.println("Outlet valve off");
  }
  if (Valve_pump1state) 
  {
    paused_pump1_state = true;
    closevalve(Valve_pump1); 
    Serial1.println("One way valve 1 off");
  }
  if (Valve_pump2state) 
  {
    paused_pump2_state = true;
    closevalve(Valve_pump2); 
    Serial1.println("One way valve 2 off");
  } 
}

void continue_brew()
{
  if (paused_mashout_state) 
  {
    Valve_mashoutstate = true;
    openvalve(Valve_mash); 
    Serial1.println("Mashing valve on");
  }
  if (paused_boil_state) 
  {
    Valve_boilstate = true;
    openvalve(Valve_boil); 
    Serial1.println("Boiling valve on");
  }
  if (paused_hop1_state) 
  {
    Valve_hop1state = true;
    openvalve(Valve_hop1); 
    Serial1.println("Hop valve 1 on");
  }
  if (paused_hop2_state) 
  {
    Valve_hop2state = true;
    openvalve(Valve_hop2); 
    Serial1.println("Hop valve 2 on");
  }
  if (paused_hop3_state) 
  {
    Valve_hop3state = true;
    openvalve(Valve_hop3); 
    Serial1.println("Hop valve 3 on");
  }
  if (paused_hop4_state) 
  {
    Valve_hop4state = true;
    openvalve(Valve_hop4); 
    Serial1.println("Hop valve 4 on");
  }
  if (paused_cool_state) 
  {
    Valve_coolstate = true;
    openvalve(Valve_cool); 
    Serial1.println("Cooling valve on");
  }
  if (paused_outlet_state) 
  {
    Valve_outletstate = true;
    openvalve(Valve_outlet); 
    Serial1.println("Outlet valve on");
  }
  if (paused_pump1_state) 
  {
    Valve_pump1state = true;
    openvalve(Valve_pump1); 
    Serial1.println("One way valve 1 on");
  }
  if (paused_pump2_state) 
  {
    Valve_pump2state = true;
    openvalve(Valve_pump2); 
    Serial1.println("One way valve 2 on");
  } 

  paused_mashout_state = false;
  paused_boil_state = false;
  paused_hop1_state = false;
  paused_hop2_state = false;
  paused_hop3_state = false;
  paused_hop4_state = false;
  paused_cool_state = false;
  paused_outlet_state = false;
  paused_pump1_state = false;
  paused_pump2_state = false;
}

void switchoffeverything()
{
  if (Valve_mashoutstate==true ) {closevalve(Valve_mash); Serial1.println("Mashing valve off");}
  if (Valve_boilstate==true ) {closevalve(Valve_boil); Serial1.println("Boiling valve off");}
  if (Valve_hop1state == true ) {closevalve(Valve_hop1); Serial1.println("Hop valve 1 off");}
  if (Valve_hop2state == true ) {closevalve(Valve_hop2); Serial1.println("Hop valve 2 off");}
  if (Valve_hop3state == true ) {closevalve(Valve_hop3); Serial1.println("Hop valve 3 off");}
  if (Valve_hop4state == true ) {closevalve(Valve_hop4); Serial1.println("Hop valve 4 off");}
  if (Valve_coolstate == true ) {closevalve(Valve_cool); Serial1.println("Cooling valve off");}
  if (Valve_outletstate == true ) {closevalve(Valve_outlet); Serial1.println("Outlet valve off");}
  if (Valve_pump1state == true ) {closevalve(Valve_pump1); Serial1.println("One way valve 1 off");}
  if (Valve_pump2state == true ) {closevalve(Valve_pump2); Serial1.println("One way valve 2 off");}
  digitalWrite(Valve_inlet, LOW);
  digitalWrite(Fan1, LOW);
  digitalWrite(Fan2, LOW);
  digitalWrite(Fan3, LOW);
  digitalWrite(Fan4, LOW);
  digitalWrite(Fan5, LOW);
  digitalWrite(Pump_A, LOW);
  digitalWrite(Pump_B, LOW);
  digitalWrite(Heater1, LOW);
  digitalWrite(Heater2, LOW);
  Setpoint1 = 0;
  Setpoint2 = 0;
  CurrentStep = 0;

  paused_mashout_state = false;
  paused_boil_state = false;
  paused_hop1_state = false;
  paused_hop2_state = false;
  paused_hop3_state = false;
  paused_hop4_state = false;
  paused_cool_state = false;
  paused_outlet_state = false;
  paused_pump1_state = false;
  paused_pump2_state = false;
}

void resetvariables()
{
  seconds = 0;
  current_seconds = 0;
}

void switchon(int pin)
{
  digitalWrite(pin, HIGH);
}

void switchoff(int pin)
{
  digitalWrite(pin, LOW);
}

void senddata()
{
    Serial.print("R100 ");
    Serial.println(int(CalibratedTemperature1));
    Serial.print("R101 ");
    Serial.println(int(CalibratedTemperature2));
    Serial.print("R103 ");
    Serial.println(seconds);
    if (current_seconds > 0 && brewing == true)
    {
      Serial.print("R104 ");
      Serial.println(current_seconds);
      Serial.print("R105 ");
      int current_time = CurrentStepTime - current_seconds;
      if(current_time<0) 
      {
        current_time = 0;  
      }
      Serial.println(current_time);//1000-currentseconds);
    }
    //Serial.print("Current 1 ");
    //Serial.println(analogRead(Pump_current1));
    //Serial.print("Current 2 ");
    //Serial.println(analogRead(Pump_current2));
}


  


