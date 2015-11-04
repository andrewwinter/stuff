void readserial()
{
  int Incoming;
  int speed = 0;
  char startbyte;
  startbyte = Serial.read();
  if (startbyte == 'P')
  {
    Incoming = Serial.parseInt();
    switch (Incoming)
    {
      
      //New Recipe
      case 101:
      {
        Serial1.println("New Recipe");
        numberofsteps = Serial.parseInt();
        Serial1.print("Number of steps: ");
        Serial1.println(numberofsteps);
        delete BrewingSteps;
        struct BrewingStep BrewingSteps[numberofsteps+1];
        break;
      }
      case 102: Serial.println("P102");
        break;
      //Parse Recipe
      case 103:
      {
        int j = Serial.parseInt();
        BrewingSteps[j].number = j;
        BrewingSteps[j].inletvalve = Serial.parseInt();        
        BrewingSteps[j].mashingvalve = Serial.parseInt();
        BrewingSteps[j].boilingvalve = Serial.parseInt();
        BrewingSteps[j].temperature1 = Serial.parseInt();
        BrewingSteps[j].temperature2 = Serial.parseInt();
        BrewingSteps[j].hop1 = Serial.parseInt();
        BrewingSteps[j].hop2 = Serial.parseInt();
        BrewingSteps[j].hop3 = Serial.parseInt();
        BrewingSteps[j].hop4 = Serial.parseInt();
        BrewingSteps[j].coolingvalve = Serial.parseInt();
        BrewingSteps[j].fan = Serial.parseInt();
        BrewingSteps[j].outletvalve = Serial.parseInt();
        BrewingSteps[j].pump1 = Serial.parseInt();
        BrewingSteps[j].pump2 = Serial.parseInt();
        BrewingSteps[j].waterlevel = Serial.parseInt();
        BrewingSteps[j].time = Serial.parseInt();
        BrewingSteps[j].condition = Serial.parseInt();
        BrewingSteps[j].auxcondition = Serial.parseInt();
        BrewingSteps[j].oneway1= Serial.parseInt();
        BrewingSteps[j].oneway2 = Serial.parseInt();
        
        Serial1.print("No: ");
        Serial1.print(BrewingSteps[j].number);
        Serial1.print(" Inlet valve: ");
        Serial1.print(BrewingSteps[j].inletvalve);
        Serial1.print(" Mashing valve: ");
        Serial1.print(BrewingSteps[j].mashingvalve);
        Serial1.print(" Boiling valve: ");
        Serial1.print(BrewingSteps[j].boilingvalve);
        Serial1.print(" Setpoint 1: ");
        Serial1.print(BrewingSteps[j].temperature1);
        Serial1.print(" Setpoint 2: ");
        Serial1.print(BrewingSteps[j].temperature2);
        Serial1.print(" Hop1: ");
        Serial1.print(BrewingSteps[j].hop1);
        Serial1.print(" Hop2: ");
        Serial1.print(BrewingSteps[j].hop2);
        Serial1.print(" Hop3: ");
        Serial1.print(BrewingSteps[j].hop3);
        Serial1.print(" Hop4: ");
        Serial1.print(BrewingSteps[j].hop4);
        Serial1.print(" Cooling valve: ");
        Serial1.print(BrewingSteps[j].coolingvalve);
        Serial1.print(" Fan: ");
        Serial1.print(BrewingSteps[j].fan);
        Serial1.print(" Outlet valve: ");
        Serial1.print(BrewingSteps[j].outletvalve);
        Serial1.print(" Pump1: ");
        Serial1.print(BrewingSteps[j].pump1);
        Serial1.print(" Pump2: ");
        Serial1.print(BrewingSteps[j].pump2);
        Serial1.print(" Water level: ");
        Serial1.print(BrewingSteps[j].waterlevel);
        Serial1.print(" Time: ");
        Serial1.print(BrewingSteps[j].time);
        Serial1.print(" Primary condition: ");
        Serial1.print(BrewingSteps[j].condition);
        Serial1.print(" Secondary condition: ");
        Serial1.print(BrewingSteps[j].auxcondition);
        Serial1.print(" One Way 1: ");
        Serial1.print(BrewingSteps[j].oneway1);
        Serial1.print(" One Way 2: ");
        Serial1.println(BrewingSteps[j].oneway2);
        
        Serial.println("P103");
        break;
      }
      //Parse UBL
      case 104: {
        int UBLStep = 0;
        int inletNeeded = Serial.parseInt();
        int mashingWaterAmount = Serial.parseInt();
        int spargingWaterNeeded = Serial.parseInt();
        if (inletNeeded == 1)
        {
          BrewingSteps[UBLStep] = {UBLStep, true, false, true, 0, 0, false, false, false, false, false, 0, false, 0, 0, mashingWaterAmount, 0, 1, 0};
          UBLStep++;
          Serial.print("Inlet needed, mashing water amount: "); Serial.println(mashingWaterAmount);
        }
        int mashingSteps = Serial.parseInt();
        Serial.print("Number of mashing steps: "); Serial.println(mashingSteps);
        int mashingStepTime[10];
        int mashingStepTemp[10];
        for (int j = 0; j < mashingSteps; j++)
        {
          mashingStepTime[j] = Serial.parseInt();
          mashingStepTemp[j] = Serial.parseInt();
          Serial.print(j); Serial.print(" step temperature "); Serial.print(mashingStepTemp[j]); Serial.print(" time "); Serial.println(mashingStepTime[j]);
          if (j == 0) {
            BrewingSteps[UBLStep++]= {UBLStep, false, false, false, 0, mashingStepTemp[j], false, false, false, false, false, 0, false, 0, 0, 0, mashingStepTemp[j]-Temperature2, 3, 0, false, false};
            BrewingSteps[UBLStep++]= {UBLStep, false, true,  false, 0,   0,    false, false, false, false, false, 0,   false, 0,   255, 0, 120,   5, 0, false, true };
          }
          BrewingSteps[UBLStep++]= {UBLStep,  false, true,  false, mashingStepTemp[j], 0,    false, false, false, false, false, 0,   false, 255, 0,   0, mashingStepTemp[j]-Temperature1, 2, 0, true,  false};
          BrewingSteps[UBLStep++]= {UBLStep,  false, true,  false, mashingStepTemp[j], 0,    false, false, false, false, false, 0,   false, 255, 0,   0, mashingStepTime[j],              6, 0, true,  false};
        }
        int spargingNeeded = Serial.parseInt();
        int spargingTemp   = Serial.parseInt();
        int spargingTime   = Serial.parseInt();
        if (spargingNeeded == 1) {
          BrewingSteps[UBLStep++]= {UBLStep, false, true,  true,  spargingTemp, spargingTemp,  false, false, false, false, false, 0,   false, 255, 255, 0, spargingTime,   6, 0, true,  true };
        }
        BrewingSteps[UBLStep++]= {UBLStep, false, false, true,  0,   0,    false, false, false, false, false, 0,   false, 255, 0,   0, 150,  4, 0, true,  false};
        BrewingSteps[UBLStep++]= {UBLStep, false, false, false, 0,   1000, false, false, false, false, false, 0,   false, 0,   0,   0, 0,    3, 3, false, false};
        int hoppingSteps = Serial.parseInt();
        int hoppingTime[4];
        for (int j = 0; j < hoppingSteps; j++) {
          hoppingTime[j] = Serial.parseInt();
        }
        if (hoppingSteps > 0) {
          BrewingSteps[UBLStep++]= {UBLStep, false, false, true,  0,   1000, true,  false, false, false, false, 0,   false, 0,   255, 0, hoppingTime[0],  6, 3, false, true };
        }
        if (hoppingSteps > 1) {
          BrewingSteps[UBLStep++]= {UBLStep, false, false, true,  0,   1000, true,  true,  false, false, false, 0,   false, 0,   255, 0, hoppingTime[1],  6, 3, false, true };
        }
        if (hoppingSteps > 2) {
          BrewingSteps[UBLStep++]= {UBLStep, false, false, true,  0,   1000, true,  true,  true,  false, false, 0,   false, 0,   255, 0, hoppingTime[2],  6, 3, false, true };
        }
        if (hoppingSteps > 3) {
          BrewingSteps[UBLStep++]= {UBLStep, false, false, true,  0,   1000, true,  true,  true,  true,  false, 0,   false, 0,   255, 0, hoppingTime[3],  6, 3, false, true };
        }
        BrewingSteps[UBLStep++]= {UBLStep, false, false, false, 0,   0,    false, false, false, false, true,  255, false, 0,   255, 0, 1800 , 6, 0, false, true };
        BrewingSteps[UBLStep++]= {UBLStep, false, false, false, 0,   0,    false, false, false, false, false, 0,   false, 0,   0,   0, 0,    8, 0, false, false};
        break;
      }
      //Drain everything
      case 105: Serial.println("P105");
        Serial1.println("Drain down everything");
        BrewingSteps[0] = {0, false, false,  false, 0,   0,    false, false, false, false, false, 0,   true,  0,   255, 0, 90,   5, 0, false, true  };
        BrewingSteps[1] = {1, false, false,  false, 0,   0,    false, false, false, false, false, 0,   true,  255, 0,   0, 90,   4, 0, true,  false };
        BrewingSteps[2] = {2, false, false,  false, 0,   0,    true,  true,  true,  true,  false, 0,   true,  0,   0,   0, 45,   6, 0, false, false };
        BrewingSteps[3] = {3, false, false,  false, 0,   0,    false, false, false, false, false, 0,   false, 0,   0,   0, 0,    8, 0, false, false };
        break;
      //Drain boiling tank (after brewing)
      case 106: Serial.println("P106");
        Serial1.println("Drain down boiling tank");
        BrewingSteps[0] = {0, false, false,  false, 0,   0,    false, false, false, false, false, 0,   true,  0,   255, 0, 90,   5, 0, false, true  };
        BrewingSteps[1] = {1, false, false,  false, 0,   0,    true,  true,  true,  true,  false, 0,   true,  0,   0,   0, 45,   6, 0, false, false };
        BrewingSteps[2] = {2, false, false,  false, 0,   0,    false, false, false, false, false, 0,   false, 0,   0,   0, 0,    8, 0, false, false };
        break;
      //Cleaning program
      case 107: Serial.println("P107");
        Serial1.println("Short cleaning program");
        //                 #  inlet  mash   boil   SP1  SP2   1st h. 2nd h. 3rd h. 4th h. cool   fan  outlet P1   P2   WL time  MC SC OV1    OV2
        BrewingSteps[0] = {0, false, true,  false, 0,   0,    false, false, false, false, false, 0,   false, 0,   255, 0, 90,   5, 0, false, true };
        BrewingSteps[1] = {1, false, true,  false, 0,   0,    false, false, false, false, false, 0,   false, 255, 0,   0, 90,   6, 0, true,  false};
        BrewingSteps[2] = {2, false, true,  true,  0,   0,    false, false, false, false, false, 0,   false, 255, 255, 0, 90,   6, 0, true,  true };
        BrewingSteps[3] = {3, false, false, true,  0,   0,    false, false, false, false, false, 0,   false, 255, 0,   0, 90,   4, 0, true,  false};
        BrewingSteps[4] = {4, false, false, true,  0,   0,    true,  false, false, false, false, 0,   false, 0,   125, 0, 60,   6, 0, false, true };
        BrewingSteps[5] = {5, false, false, true,  0,   0,    false, true,  false, false, false, 0,   false, 0,   125, 0, 60,   6, 0, false, true };
        BrewingSteps[6] = {6, false, false, true,  0,   0,    false, false, true,  false, false, 0,   false, 0,   125, 0, 60,   6, 0, false, true };
        BrewingSteps[7] = {7, false, false, true,  0,   0,    false, false, false, true,  false, 0,   false, 0,   125, 0, 60,   6, 0, false, true };
        BrewingSteps[8] = {8, false, false, false, 0,   0,    false, false, false, false, true,  0,   false, 0,   255, 0, 60,   6, 0, false, true };
        BrewingSteps[9] = {9, false, false, false, 0,   0,    false, false, false, false, false, 0,   false, 0,   0,   0, 0,    8, 0, false, false};
        break;
      //Automatic water inlet  
      case 108: wlsetpoint = Serial.parseInt();
        Serial.println("P108");
        BrewingSteps[0] = {0, true,  false, true,  0, 0, false, false, false, false, false, 0, false, 0, 0, wlsetpoint, 0, 1, 0, false, false};
        BrewingSteps[1] = {1, false, false, false, 0, 0, false, false, false, false, false, 0, false, 0, 0,  0, 0, 8, 0, false, false};
        break;
      //Inlet valve
      case 110: Serial.println("P110");
        Serial1.println("Inlet valve on");
        digitalWrite(Valve_inlet, HIGH);
        Valve_inletstate = true;
        break;
      case 111: Serial.println("P111");
        Serial1.println("Inlet valve off");
        digitalWrite(Valve_inlet, LOW);
        Valve_inletstate = false;
        break;
      //Mashout valve
      case 112: Serial.println("P112");
        Serial1.println("Mashing valve on");
        Valve_mashoutstate = true;
        openvalve(Valve_mash);
        break;
      case 113: Serial.println("P113");
        Serial1.println("Mashing valve off");
        Valve_mashoutstate = false;
        closevalve(Valve_mash);
        break;
      //Lautering valve
      case 114: Serial.println("P114");
        Serial1.println("Boiling valve on");
        Valve_boilstate = true;
        openvalve(Valve_boil);
        break;
      case 115: Serial.println("P115");
        Serial1.println("Boiling valve off");
        Valve_boilstate = false;
        closevalve(Valve_boil);
        break;
      //Hop 1
      case 116: Serial.println("P116");
        Serial1.println("Hop 1 valve on");
        Valve_hop1state = true;
        openvalve(Valve_hop1);
        break;
      case 117: Serial.println("P117");
        Serial1.println("Hop 1 valve off");
        Valve_hop1state = false;
        closevalve(Valve_hop1);
        break;
      //Hop 2
      case 118: Serial.println("P118");
        Serial1.println("Hop 2 valve on");
        Valve_hop2state = true;
        openvalve(Valve_hop2);
        break;
      case 119: Serial.println("P119");
        Serial1.println("Hop 2 valve off");
        Valve_hop2state = false;
        closevalve(Valve_hop2);
        break;
      //Hop3
      case 120: Serial.println("P120");
        Serial1.println("Hop 3 valve on");
        Valve_hop3state = true;
        openvalve(Valve_hop3);
        break;
      case 121: Serial.println("P121");
        Serial1.println("Hop 3 valve off");
        Valve_hop3state = false;
        closevalve(Valve_hop3);
        break;
      //Hop 4
      case 122: Serial.println("P122");
        Serial1.println("Hop 4 valve on");
        Valve_hop4state = true;
        openvalve(Valve_hop4);
        break;
      case 123: Serial.println("P123");
        Serial1.println("Hop 4 valve off");
        Valve_hop4state = false;
        closevalve(Valve_hop4);
        break;
      //Mashout pump
      case 124: Serial.println("P124");
        Serial1.println("Mashing pump on");
        digitalWrite(Pump_A, HIGH);
        Pump_Astate = true;
        break;
      case 125: Serial.println("P125");
        Serial1.println("Mashing pump off");
        digitalWrite(Pump_A, LOW);
        Pump_Astate = false;
        break;
      //Boiling pump
      case 126: Serial.println("P126");
        Serial1.println("Boiling pump off");
        digitalWrite(Pump_B, HIGH);
        Pump_Bstate = true;
        break;
      case 127: Serial.println("P127");
        Serial1.println("Boiling pump off");
        digitalWrite(Pump_B, LOW);
        Pump_Bstate = false;
        break;
      //Fan
      case 128: Serial.println("P128");
        Serial1.println("Fan on");
        digitalWrite(Fan2, HIGH);
        delay(500);
        digitalWrite(Fan3, HIGH);
        delay(500);
        digitalWrite(Fan4, HIGH);
        Ventilatorstate = true;
        break;
      case 129: Serial.println("P129");
        Serial1.println("Fan off");
        digitalWrite(Fan2, LOW);
        digitalWrite(Fan3, LOW);
        digitalWrite(Fan4, LOW);
        Ventilatorstate = false;
        break;
      //Cooling valve
      case 130: Serial.println("P130");
        Serial1.println("Cooling valve on");
        openvalve(Valve_cool);
        Valve_coolstate = true;
        break;
      case 131: Serial.println("P131");
        Serial1.println("Cooling valve off");
        closevalve(Valve_cool);
        Valve_coolstate = false;
        break;
      //Outlet valve  
      case 132: Serial.println("P132");
        Serial1.println("Outlet valve on");
        openvalve(Valve_outlet);
        Valve_outletstate = true;
        break;
      case 133: Serial.println("P133");
        Serial1.println("Outlet valve off");
        closevalve(Valve_outlet);
        Valve_outletstate = false;
        break;
      //One way valve 1
      case 134: Serial.println("P134");
        Serial1.println("One way valve 1 on");
        openvalve(Valve_pump1);
        Valve_pump1state = true;
        break;
      case 135: Serial.println("P135");
        Serial1.println("One way valve 1 off");
        closevalve(Valve_pump1);
        Valve_pump1state = false;
        break;
      case 136: Serial.println("P136");
        Serial1.println("One way valve 2 on");
        openvalve(Valve_pump2);
        Valve_pump2state = true;
        break;
      case 137: Serial.println("P137");
        Serial1.println("One way valve 2 off");
        closevalve(Valve_pump2);
        Valve_pump2state = false;
        break;
      case 150: Setpoint1 = Serial.parseInt();
        Serial.println("P150");
        Serial1.print("Setpoint 1: ");
        Serial1.println(Setpoint1);
        break;
      case 151: Setpoint2 = Serial.parseInt();
        Serial.println("P151");
        Serial1.print("Setpoint 2: ");
        Serial1.println(Setpoint2);
        break;
      case 152:
        controlValve(Serial.parseInt(), Valve_mash);
        Serial.println("P152");
        Serial1.println("Control valve");
        break;
      case 153:
        controlValve(Serial.parseInt(), Valve_boil);
        Serial.println("P153");
        Serial1.println("Control valve");
        break;
      case 154:
        controlValve(Serial.parseInt(), Valve_hop1);
        Serial.println("P154");
        Serial1.println("Control valve");
        break;
      case 155:
        controlValve(Serial.parseInt(), Valve_hop2);
        Serial.println("P155");
        Serial1.println("Control valve");
        break;
      case 156:
        controlValve(Serial.parseInt(), Valve_hop3);
        Serial.println("P156");
        Serial1.println("Control valve");
        break;
      case 157:
        controlValve(Serial.parseInt(), Valve_hop4);
        Serial.println("P157");
        Serial1.println("Control valve");
        break;
      case 158:
        currentPWM1 = Serial.parseInt();
        analogWrite(Pump_A, currentPWM1);
        Serial.println("P158");
        Serial1.println("Control pump");
        break;
      case 159:
        analogWrite(Pump_B, Serial.parseInt());
        Serial.println("P159");
        Serial1.println("Control pump");
        break;
      case 160:
        speed = Serial.parseInt();
        analogWrite(Fan2, speed);
        delay(500);
        analogWrite(Fan3, speed);
        delay(500);
        analogWrite(Fan4, speed);
        Serial.println("P160");
        Serial1.println("Control fan");
        break;
      case 161:
        controlValve(Serial.parseInt(), Valve_cool);
        Serial.println("P161");
        Serial1.println("Control valve");
        break;
      case 162:
        controlValve(Serial.parseInt(), Valve_outlet);
        Serial.println("P162");
        Serial1.println("Control valve");
        break;
      case 163:
        Waterlevelsetpoint = Serial.parseInt();
        Serial.println("P163");
        Serial1.println("Control water level");
        break;
      case 164:
        speed = Serial.parseInt();
        analogWrite(Fan1, speed);
        analogWrite(Fan5, speed);
        Serial.println("P164");
        Serial1.println("Control fan speed");
        break;
      //Start recipe signal
      case 200: Serial.println("P200");
        Serial1.println("Start");
        switchoffeverything();
        brewing = true;
        //mashout = true;
        startseconds = millis()/1000;
        currentstartseconds = millis()/1000;
        brewingstarted = true;
        newstepstarted = true;
        break;
      //Pause sugnal
      case 201: Serial.println("P201");
        Serial1.println("Pause");
        brewing = false;
        pausedatcurrentseconds = currentseconds;
        pausedatseconds = seconds;
        break;
      //Continue
      case 202: Serial.println("P202");
        Serial1.println("Continue");
        brewing = true;
        currentstartseconds = pausedatcurrentseconds;
        startseconds = pausedatseconds;
        break;
      //Stop
      case 203: Serial.println("P203");
        Serial1.println("Stop");
        brewing = false;
        switchoffeverything();
        resetvariables();
        Setpoint1 = 0;
        Setpoint2 = 0;
        i=0;
        CurrentStep = 0;
        newstepstarted = false;
        break;
      //ID
      case 300: Serial.print("P300 ");
        Serial.println(ID);
        Serial1.print("ID: ");
        Serial1.println(ID);
        break;
      //Current of valve
      case 301: Serial.println("P301 ");
        Serial.println("0");
        break;
      //Water level
      case 302: Serial.println("P302 ");
        Serial.println("0"); //Waterlevel();)
        break;
      //Fan speed
      case 303: Serial.println("P303 ");
        Serial.println("0");
        break;
      //Current step
      case 304: Serial.println("P304 ");
        Serial.println(CurrentStep);
        break;
      //Firmware version
      case 310: Serial.println("P310 ");
        Serial.println("0.2");
        break;
      //Number of brews
      case 311: Serial.println("P311 ");
        Serial.println("11");
        break;
      //Number of working hours
      case 312: Serial.println("P312 ");
        Serial.println("8");
        break;
      //Stop signal
      case 999: Serial.println("P999");
        Serial1.println("Stop");
        brewing = false;
        switchoffeverything();
        resetvariables();
        i=0;
        newstepstarted = false;
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
        counter = 0;
        break;
      //else Serial.println("Unknown command");
    }
  }
  else if (startbyte == 'M')
  {
    Serial.println("Incoming M");
  }
  else if (startbyte == ' ' || startbyte == '\r' || startbyte == '\n' || startbyte == 'P');
  else
  {
    Serial.print("E010 ");
    Serial.println(startbyte);
  }
    
}

boolean toBool(int number)
{
  if (number==1)
    return true;
  else if (number==0)
    return false;
}
