boolean waterlevelcondition, temperaturecondition1, temperaturecondition2, tankemptycondition1, tankemptycondition2, timercondition, userinteraction;
boolean maxtime, holdwaterlevel, boilingreached;
boolean newstepstarted = false, brewingstarted = false;
float Waterlevelsetpoint; 
int Timesetpoint, i = 0;

struct BrewingStep {
  short number;
  boolean inletvalve, mashingvalve, boilingvalve;
  float temperature1, temperature2;
  boolean hop1, hop2, hop3, hop4, coolingvalve;
  short fan;
  boolean outletvalve;
  short pump1, pump2;
  int waterlevel, time;
  short condition, auxcondition;
  boolean oneway1, oneway2;
};
//                                     #   inlet  mash   boil   SP1  SP2   1st h. 2nd h. 3rd h. 4th h. cool   fan  outlet P1   P2   WL time  MC SC OV1    OV2
struct BrewingStep BrewingSteps[30] ={/*{0,  false, true,  false, 0,   0,    false, false, false, false, false, 0,   false, 0,   255, 0, 90,   5, 0, false, true },
                                      {1,  false, true,  true,  0,   0,    false, false, false, false, false, 0,   false, 255, 255, 0, 240,  6, 0, true,  true },
                                      {2,  false, false, true,  0,   0,    false, false, false, false, false, 0,   false, 255, 0,   0, 150,  4, 0, true,  false},
                                      //{3,  false, false, false, 0,   0,    false, false, false, false, false, 0,   false, 0,   0,   0, 60,   6, 0, false, false},
                                      //{4,  false, false, false, 0,   0,    false, false, false, false, false, 0,   false, 0,   0,   0, 0,    8, 0, false, false}*/
                                      /* {0,  false, false, false, 0,   0,  false, false, false, false, false, 0,   false, 0,   0,   0, 0,    3, 0, false, false},
                                      {1,  false, true,  false, 0,   0,    false, false, false, false, false, 0,   false, 0,   255, 0, 90,   5, 0, false, true },
                                      {2,  false, true,  false, 0, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {3,  false, true,  false, 0, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 30,  6, 0, true,  false},
                                      {4,  false, true,  false, 0, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {5,  false, true,  false, 0, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 30, 6, 0, true,  false},
                                      {6,  false, true,  false, 0, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {7,  false, true,  false, 0, 0,  false, false, false, false, false, 0,   false, 255, 0,   0, 30, 6, 0, true,  false},
                                      {8,  false, true,  false, 0, 0,  false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {9,  false, true,  false, 0, 0,  false, false, false, false, false, 0,   false, 255, 0,   0, 30, 6, 0, true,  false},
                                      {10, false, true,  false, 0, 0,  false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {11, false, true,  false, 0, 0,  false, false, false, false, false, 0,   false, 255, 0,   0, 30,   6, 0, true,  false},
                                      {12, false, true,  true,  0, 0,  false, false, false, false, false, 0,   false, 255, 255, 0, 180,  6, 0, true,  true },
                                      {13, false, false, true,  0,   0,    false, false, false, false, false, 0,   false, 255, 0,   0, 0,  4, 0, true,  false},
                                      {14, false, false, false, 0,   0, false, false, false, false, false, 0,   false, 0,   0,   0, 0,    3, 3, false, false},
                                      {15, false, false, false,  0,   0, true,  false, false, false, false, 0,   false, 0,   200, 0, 60,  6, 3, false, true },
                                      {16, false, false, false,  0,   0, true,  true,  false, false, false, 0,   false, 0,   200, 0, 60,  6, 3, false, true },
                                      {17, false, false, false,  0,   0, true,  true,  true,  false, false, 0,   false, 0,   200, 0, 60,  6, 3, false, true },
                                      {18, false, false, false,  0,   0, true,  true,  true,  true,  false, 0,   false, 0,   200, 0, 60,  6, 3, false, true },
                                      {19, false, false, false, 0,   0,    false, false, false, false, true,  255, false, 0,   255, 0, 60, 6, 0, false, true },
                                      {20, false, false, false, 0,   0,    false, false, false, false, false, 0,   false, 0,   0,   0, 0,    8, 0, false, false}*/
                                      {0,  false, false, false, 0,   560,  false, false, false, false, false, 0,   false, 0,   0,   0, 0,    3, 0, false, false},
                                      {1,  false, true,  false, 0,   0,    false, false, false, false, false, 0,   false, 0,   255, 0, 90,   5, 0, false, true },
                                      {2,  false, true,  false, 520, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {3,  false, true,  false, 520, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 900,  6, 0, true,  false},
                                      {4,  false, true,  false, 620, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {5,  false, true,  false, 620, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 2700, 6, 0, true,  false},
                                      {6,  false, true,  false, 680, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {7,  false, true,  false, 680, 780,  false, false, false, false, false, 0,   false, 255, 0,   0, 2700, 6, 0, true,  false},
                                      {8,  false, true,  false, 720, 780,  false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {9,   false, true,  false, 720, 780,  false, false, false, false, false, 0,   false, 255, 0,   0, 1200, 6, 0, true,  false},
                                      {10, false, true,  false, 780, 780,  false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {11, false, true,  false, 780, 780,  false, false, false, false, false, 0,   false, 255, 0,   0, 60,   6, 0, true,  false},
                                      {12, false, true,  true,  780, 780,  false, false, false, false, false, 0,   false, 255, 255, 0, 600,  6, 0, true,  true },
                                      {13, false, false, true,  0,   0,    false, false, false, false, false, 0,   false, 255, 0,   0, 150,  4, 0, true,  false},
                                      {14, false, false, false, 0,   1000, false, false, false, false, false, 0,   false, 0,   0,   0, 300,  6, 3, false, false},
                                      {15, false, false, true,  0,   1000, false, false, false, false, false, 0,   false, 255, 0,   0, 150,  4, 3, true,  false},
                                      {16, false, false, false, 0,   1000, false, false, false, false, false, 0,   false, 0,   0,   0, 300,  6, 3, false, false},
                                      {17, false, false, true,  0,   1000, false, false, false, false, false, 0,   false, 255, 0,   0, 150,  4, 3, true,  false},
                                      {18, false, false, false, 0,   1000, false, false, false, false, false, 0,   false, 0,   0,   0, 0,    3, 3, false, false},
                                      {19, false, false, false, 0,   1000, false, false, false, false, false, 0,   false, 0,   0,   0, 3600, 6, 3, false, false},
                                      
                                      //{16, false, false,false,  0,   1000, true,  true,  false, false, false, 0,   false, 0,   255, 0, 900,  6, 3, false, true },
                                      //{17, false, false,false,  0,   1000, true,  true,  true,  false, false, 0,   false, 0,   255, 0, 900,  6, 3, false, true },
                                      //{18, false, false,false,  0,   1000, true,  true,  true,  true,  false, 0,   false, 0,   255, 0, 900,  6, 3, false, true },
                                      {20, false, false, false, 0,   0,    false, false, false, false, true,  255, false, 0,   255, 0, 3600, 6, 0, false, true },
                                      {21, false, false, false, 0,   0,    false, false, false, false, false, 0,   false, 0,   0,   0, 0,    8, 0, false, false}
                                      /*{0,  false, false, false, 0,   370,  false, false, false, false, false, 0,   false, 0,   0,   0, 0,    3, 0, false, false},
                                      {1,  false, true,  false, 370, 0,    false, false, false, false, false, 0,   false, 0,   255, 0, 1800, 6, 0, false, true},
                                      {2,  false, true,  false, 500, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 1200, 2, 0, true,  false},
                                      {3,  false, true,  false, 630, 770,  false, false, false, false, false, 0,   false, 255, 0,   0, 1800, 6, 0, true,  false},
                                      {4, false, true,  false, 780, 780,  false, false, false, false, false, 0,   false, 255, 0,   0, 600,   2, 0, true,  false},
                                      {5, false, true,  true,  780, 780,  false, false, false, false, false, 0,   false, 255, 255, 0, 600,  6, 0, true,  true },
                                      {6, false, false, true,  0,   0,    false, false, false, false, false, 0,   false, 255, 0,   0, 150,  6, 0, true,  false},
                                      {7, false, false, false, 0,   940, false, false, false, false, false, 0,   false, 0,   0,   0, 0,    3, 3, false, false},
                                      {8, false, false, false, 0,   1000, false, false, false, false, false, 0,   false, 0,   0,   0, 150,  6, 3, false, false},
                                      {9, false, false, false, 0,   0,    false, false, false, false, true,  255, false, 0,   255, 0, 150,  6, 0, false, true },
                                      {10, false, false, false, 0,   0,    false, false, false, false, false, 0,   false, 0,   0,   0, 0,    8, 0, false, false}
                                      /*{4,  false, true,  false, 620, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {5,  false, true,  false, 620, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 150,  6, 0, true,  false},
                                      {6,  false, true,  false, 680, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {7,  false, true,  false, 680, 780,  false, false, false, false, false, 0,   false, 255, 0,   0, 150,  6, 0, true,  false},
                                      {8,  false, true,  false, 720, 780,  false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {9,  false, true,  false, 720, 780,  false, false, false, false, false, 0,   false, 255, 0,   0, 150,  6, 0, true,  false},
                                      {10, false, true,  false, 780, 780,  false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {11, false, true,  true,  780, 780,  false, false, false, false, false, 0,   false, 255, 255, 0, 150,  6, 0, true,  true },
                                      {12, false, false, true,  0,   0,    false, false, false, false, false, 0,   false, 255, 0,   0, 150,  6, 0, true,  false},
                                      {13, false, false, false, 0,   1000, false, false, false, false, false, 0,   false, 0,   0,   0, 0,    3, 0, false, false},
                                      {14, false, false, false, 0,   1000, false, false, false, false, false, 0,   false, 0,   0,   0, 150,  6, 0, false, false},
                                      {15, false, false, false, 0,   0,    false, false, false, false, true,  255, false, 0,   255, 0, 150,  6, 0, false, true },
                                      {16, false, false, false, 0,   0,    false, false, false, false, false, 0,   false, 0,   0,   0, 0,    8, 0, false, false}
                                    /*{0,  false, false, false, 0,   520,  false, false, false, false, false, 0,   false, 0,   0,   0, 0,    3, 0, false, false},
                                      {1,  false, true,  false, 0,   0,    false, false, false, false, false, 0,   false, 0,   255, 0, 150,  6, 0, false, true},
                                      {2,  false, true,  false, 520, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {3,  false, true,  false, 520, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 900,  6, 0, true,  false},
                                      {4,  false, true,  false, 620, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {5,  false, true,  false, 620, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 2700, 6, 0, true,  false},
                                      {6,  false, true,  false, 680, 0,    false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {7,  false, true,  false, 680, 780,  false, false, false, false, false, 0,   false, 255, 0,   0, 2700, 6, 0, true,  false},
                                      {8,  false, true,  false, 720, 780,  false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {9,  false, true,  false, 720, 780,  false, false, false, false, false, 0,   false, 255, 0,   0, 1200, 6, 0, true,  false},
                                      {10, false, true,  false, 780, 780,  false, false, false, false, false, 0,   false, 255, 0,   0, 0,    2, 0, true,  false},
                                      {11, false, true,  true,  780, 780,  false, false, false, false, false, 0,   false, 255, 255, 0, 600,  6, 0, true,  true },
                                      {12, false, false, true,  0,   0,    false, false, false, false, false, 0,   false, 255, 0,   0, 150,  6, 0, true,  false},
                                      {13, false, false, false, 0,   1000, false, false, false, false, false, 0,   false, 0,   0,   0, 0,    3, 0, false, false},
                                      {14, false, false, false, 0,   1000, false, false, false, false, false, 0,   false, 0,   0,   0, 3600, 6, 0, false, false},
                                      {15, false, false, false, 0,   0,    false, false, false, false, true,  255, false, 0,   255, 0, 3600, 6, 0, false, true },
                                      {16, false, false, false, 0,   0,    false, false, false, false, false, 0,   false, 0,   0,   0, 0,    8, 0, false, false}
                                      /*1, true, false, true, 0, 0, false, false, false, false, false, 0, false, 0, 0, 190, 0, 1, 0},\
                                      {2, false, false, false, 52, 0, false, false, false, false, false, 0, false, 0, 0, 0, 0, 2, 0},\
                                      {3, false, true, false, 0, 52, false, false, false, false, false, 0, false, 255, 0, 0, 0, 4, 0},\
                                      {4, true, false, true, 0, 52, false, false, false, false, false, 0, false, 0, 0, 110, 0, 1, 0},\
                                      {5, false, true, false, 0, 52, false, false, false, false, false, 0, false, 0, 255, 0, 900, 6, 0},
                                      {6, false, true, false, 0, 62, false, false, false, false, false, 0, false, 0, 255, 0, 0, 3, 0},\
                                      {7, false, true, false, 0, 62, false, false, false, false, false, 0, false, 0, 255, 0, 2700, 6, 0},\
                                      {8, false, true, false, 78, 64, false, false, false, false, false, 0, false, 0, 255, 0, 0, 3, 0},\
                                      {9, false, true, false, 78, 64, false, false, false, false, false, 0, false, 0, 255, 0, 2700, 6, 0},\
                                      {10, false, true, false, 78, 68, false, false, false, false, false, 0, false, 0, 255, 0, 0, 3, 0},\
                                      {11, false, true, false, 78, 68, false, false, false, false, false, 0, false, 0, 255, 0, 1200, 6, 0},\
                                      {12, false, true, false, 78, 72, false, false, false, false, false, 0, false, 0, 255, 0, 0, 3, 0},\
                                      {13, false, true, false, 78, 72, false, false, false, false, false, 0, false, 0, 255, 0, 300, 6, 0},\
                                      {14, false, true, true, 78, 78, false, false, false, false, false, 0, false, 125, 125, 180, 1200, 6, 2},\
                                      {15, false, false, true, 100, 0, false, false, false, false, false, 100, false, 0, 255, 0, 0, 5, 0},\
                                      {16, false, false, false, 100, 0, false, false, false, false, false, 100, false, 0, 0, 0, 0, 7, 3},\
                                      {17, false, false, false, 100, 0, true, false, false, false, false, 100, false, 255, 0, 0, 0, 6, 3},\
                                      {18, false, false, false, 100, 0, true, true, false, false, false, 100, false, 255, 0, 0, 3600, 6, 3},\
                                      {19, false, false, false, 100, 0, true, true, true, false, false, 100, false, 255, 0, 0, 3900, 6, 3},\
                                      {20, false, false, false, 100, 0, true, true, true, true, false, 100, false, 255, 0, 0, 4200, 6, 3},\
                                      {21, false, false, false, 0, 0, false, false, false, false, true, 255, false, 255, 0, 0, 0, 2, 1},\
                                      {22, false, false, false, 0, 0, false, false, false, false, false, 0, false, 0, 0, 0, 0, 8, 0}\*/
                                    };

//BrewingSteps[] = {{1, true, false, true, 0, 0, false, false, false, false, false, 0, false, 0, 0, 190, 0, 1, 0}}

void Brewing()
{
  seconds=millis()/1000-startseconds;
  currentseconds=millis()/1000-currentstartseconds; 
  //BrewingSteps BrewingStep[20];
  if (newstepstarted==true)
  {  
    CurrentStep = BrewingSteps[i].number; Serial.print(CurrentStep); Serial.println(". step");
    CurrentStepTime = BrewingSteps[i].time*1000; Serial.print(BrewingSteps[i].time*1000); Serial.println(" s");
    
    if (BrewingSteps[i].inletvalve==false && Valve_inletstate == true) {digitalWrite(Valve_inlet, LOW); Valve_inletstate = false; Serial1.println("Inlet valve off");}
    if (BrewingSteps[i].oneway1==true  && Valve_pump1state == false) {openvalve(Valve_pump1);  Valve_pump1state = true;  Serial1.println("One way valve 1 on");}
    if (BrewingSteps[i].oneway1==false && Valve_pump1state == true ) {closevalve(Valve_pump1); Valve_pump1state = false; Serial1.println("One way valve 1 off");}
    if (BrewingSteps[i].oneway2==true  && Valve_pump2state == false) {openvalve(Valve_pump2);  Valve_pump2state = true;  Serial1.println("One way valve 2 on");}
    if (BrewingSteps[i].oneway2==false && Valve_pump2state == true ) {closevalve(Valve_pump2); Valve_pump2state = false; Serial1.println("One way valve 2 off");}
    digitalWrite(Pump_A, LOW);
    digitalWrite(Pump_B, LOW);
    if (BrewingSteps[i].mashingvalve==true  && Valve_mashoutstate==false) {Valve_mashoutstate = true;  openvalve(Valve_mash);  Serial1.println("Mashing valve on");}
    if (BrewingSteps[i].mashingvalve==false && Valve_mashoutstate==true ) {Valve_mashoutstate = false; closevalve(Valve_mash); Serial1.println("Mashing valve off");}
    if (BrewingSteps[i].boilingvalve==true  && Valve_boilstate==false) {Valve_boilstate = true;  openvalve(Valve_boil);  Serial1.println("Boiling valve on");}
    if (BrewingSteps[i].boilingvalve==false && Valve_boilstate==true ) {Valve_boilstate = false; closevalve(Valve_boil); Serial1.println("Boiling valve off");}
    if (BrewingSteps[i].hop1==true  && Valve_hop1state == false) {Valve_hop1state = true;  openvalve(Valve_hop1);  Serial1.println("Hop valve 1 on");}
    if (BrewingSteps[i].hop1==false && Valve_hop1state == true ) {Valve_hop1state = false; closevalve(Valve_hop1); Serial1.println("Hop valve 1 off");}
    if (BrewingSteps[i].hop2==true  && Valve_hop2state == false) {Valve_hop2state = true;  openvalve(Valve_hop2);  Serial1.println("Hop valve 2 on");}
    if (BrewingSteps[i].hop2==false && Valve_hop2state == true ) {Valve_hop2state = false; closevalve(Valve_hop2); Serial1.println("Hop valve 2 off");}
    if (BrewingSteps[i].hop3==true  && Valve_hop3state == false) {Valve_hop3state = true;  openvalve(Valve_hop3);  Serial1.println("Hop valve 3 on");}
    if (BrewingSteps[i].hop3==false && Valve_hop3state == true ) {Valve_hop3state = false; closevalve(Valve_hop3); Serial1.println("Hop valve 3 off");}
    if (BrewingSteps[i].hop4==true  && Valve_hop4state == false) {Valve_hop4state = true;  openvalve(Valve_hop4);  Serial1.println("Hop valve 4 on");}
    if (BrewingSteps[i].hop4==false && Valve_hop4state == true ) {Valve_hop4state = false; closevalve(Valve_hop4); Serial1.println("Hop valve 4 off");}
    if (BrewingSteps[i].coolingvalve==true  && Valve_coolstate == false) {openvalve(Valve_cool);  Valve_coolstate = true;  Serial1.println("Cooling valve on");}
    if (BrewingSteps[i].coolingvalve==false && Valve_coolstate == true ) {closevalve(Valve_cool); Valve_coolstate = false; Serial1.println("Cooling valve off");}
    if (BrewingSteps[i].outletvalve==true  && Valve_outletstate == false) {openvalve(Valve_outlet);  Valve_outletstate = true;  Serial1.println("Outlet valve on");}
    if (BrewingSteps[i].outletvalve==false && Valve_outletstate == true ) {closevalve(Valve_outlet); Valve_outletstate = false; Serial1.println("Outlet valve off");}
    if (BrewingSteps[i].inletvalve==true  && Valve_inletstate == false) {digitalWrite(Valve_inlet, HIGH); Valve_inletstate=true; Serial1.println("Inlet valve on");}
    
    Waterlevelsetpoint=BrewingSteps[i].waterlevel/10.0; Serial.print("Water level setpoint: "); Serial.println(Waterlevelsetpoint);
    Serial1.print("Time: "); Serial1.println(BrewingSteps[i].time);
    Setpoint1 = BrewingSteps[i].temperature1; Serial1.print("Setpoint 1: "); Serial1.println(Setpoint1);
    Setpoint2 = BrewingSteps[i].temperature2; Serial1.print("Setpoint 2: "); Serial1.println(Setpoint2);
    analogWrite(Pump_A, BrewingSteps[i].pump1); Serial1.print("Pump 1: "); Serial1.println(BrewingSteps[i].pump1);
    analogWrite(Pump_B, BrewingSteps[i].pump2); Serial1.print("Pump 2: "); Serial1.println(BrewingSteps[i].pump2);
    analogWrite(Fan2, BrewingSteps[i].fan); Serial1.print("Fan: "); Serial1.println(BrewingSteps[i].fan); delay(500);
    analogWrite(Fan3, BrewingSteps[i].fan); delay(500);
    analogWrite(Fan4, BrewingSteps[i].fan); 
    //if (BrewingSteps[i].fan > 125) digitalWrite(Fan3, HIGH);
    //else digitalWrite(Fan3, LOW);
    waterlevelcondition = false;
    temperaturecondition1 = false;
    temperaturecondition2 = false;
    tankemptycondition1 = false;
    tankemptycondition2 = false;
    timercondition = false;
    boilingreached = false;
    userinteraction = false;
    maxtime = false;
    holdwaterlevel = false;
    maxpower = false;
    
    switch (BrewingSteps[i].condition)
    {
      case 0: Serial1.println("Faulty condition"); break;
      case 1: waterlevelcondition=true; Serial1.println("Water level condition"); break;
      case 2: temperaturecondition1=true; Serial1.println("Temperature 1 condition"); break;
      case 3: temperaturecondition2=true; Serial1.println("Temperature 2 condition"); break;
      case 4: tankemptycondition1=true; Serial1.println("Tank 1 empty condition"); break;
      case 5: tankemptycondition2=true; Serial1.println("Tank 2 empty condition"); break;
      case 6: timercondition=true; Serial1.println("Timer condition"); break;
      case 7: boilingreached=true; Serial1.println("Boiling condition"); break;
      case 8: userinteraction=true; Serial1.println("Interaction condition"); break;
    }
    //short auxcondition = BrewingSteps[i, 18];
    maxtime = holdwaterlevel = boilingreached = maxpower = false;
    switch (BrewingSteps[i].auxcondition)
    {
      case 0: Serial1.println("No aux condition"); break;
      case 1: maxtime=true; Serial1.println("Max time aux condition"); break;
      case 2: holdwaterlevel=true; Serial1.println("Hold water level aux condition"); break;
      case 3: maxpower=true; Serial1.println("Max power aux condition"); break;
    }
    newstepstarted = false;
    brewingstarted = false;
    Serial1.print("i: ");
    Serial1.println(i);
    i++;
    /*else
    {    
        brewing = false;
        switchoffeverything();
        resetvariables();
        Setpoint1 = 0;
        Setpoint2 = 0;
        CurrentStep = 0;
        //brewingstarted = false;
        newstepstarted = false;
        i = 0;
        Serial.println("R110");
        Serial.readString();
        Serial1.println("Ready");
    }*/
    Serial1.println();
  }
  if (waterlevelcondition == true)
  {
    if (waterlevelcalibrated > (Waterlevelsetpoint-1))
    {
      newstepstarted = true;
    }
  }
  if (temperaturecondition1 == true)
  {
    if (CalibratedTemperature1 >= Setpoint1)
    {
      newstepstarted = true;
      currentstartseconds = millis()/1000;
      Serial1.println("Temp 1 reached");
    }
  }
  else if (temperaturecondition2 == true)
  {
    if (CalibratedTemperature2 >= Setpoint2)
    {
      newstepstarted = true;
      currentstartseconds = millis()/1000;
      Serial1.println("Temp 2 reached");
    }
  }
  else if (tankemptycondition1 == true)
  {
    if (Mashingtankempty()==true)
    {
      newstepstarted = true;
      currentstartseconds = millis()/1000;
      Serial1.println("Mashing tank empty");
    }
  }
  else if (tankemptycondition2 == true)
  {
    if (Boilingtankempty()==true)
    {
      newstepstarted = true;
      currentstartseconds = millis()/1000;
      Serial1.println("Boiling tank empty");
    }
  }
  //else 
  if (timercondition == true)
  {
    if (currentseconds >= BrewingSteps[i-1].time)
    {
      newstepstarted = true;
      currentstartseconds = millis()/1000;
      Serial1.print("Time's up ");
      Serial1.println(BrewingSteps[i-1].time);
    }
  }
}

 


