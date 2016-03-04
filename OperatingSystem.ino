MotionAndEnergy ME;
Heartrate HR;
Wireless Wireless;
Button Button;
Storage Storage;

void help(void);
void UpdateHR(void);
void ubidots_heartrate(void);
void alarm(void);

bool sent_hr = 0;
bool sent_hr2 = 0;
bool impacted = 0;
bool conc = 0;
bool pressed = 0;

void setup() {
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);
  ME.Initial();
  Button.Initial();
  Wireless.Initial();
  Storage.Initial();
  HR.Initial();

  delay(10000);
  Wireless.Send(5,1); //reset dashboard.
}

void loop() {
  HR.Compute();
  UpdateHR();
  ubidots_heartrate(); //Update heart rate to ubidots every 1hr.
  Storage.Configuration();

  if(Button.state())
  {
      if(pressed == 0)
      {
          #ifdef DEVELOPER
            Serial.println("User used a help button.");
          #endif
          Wireless.Send(2,1);
          pressed = 1;
      }
  }

  if(NormalHeartrateRange_Threshold != 0)
  {         
      if(HR.getBPM() > OutsideHeartRateRange_Threshold)
      {
        if(sent_hr == 0)
        {
          #ifdef DEVELOPER
           Serial.println("The heart rate is higher than the normal.");
          #endif
          Wireless.Send(1,HR.getBPM()); 
          sent_hr = 1;
        }       
      }
    
      if(HR.getBPM() < LowerHeartRateRange_Threshold)
      {
        if(sent_hr2 == 0)
        {
          #ifdef DEVELOPER
           Serial.println("Warning! the heart rate is too slow.");
          #endif
          Wireless.Send(1,HR.getBPM());
          sent_hr2 = 1;
        }
      }
    
  } 
  
  if(ME.IMPACTED())
  {
    if(impacted == 0)
    {
      #ifdef DEVELOPER
      Serial.println("Impacted!");
      #endif
      Wireless.Send(4,0);
      impacted = 1;
    }
  }

  if(ME.UNCONCIOUS())
  {
    if(conc == 0)
    {
      #ifdef DEVELOPER
      Serial.println("Unconcious!");
      #endif
      Wireless.Send(3,0);
      conc = 1;
    }
  }

  help(); 
  alarm();
}

unsigned long p_mil = 0;
int last_hr = 0;
void UpdateHR()
{
    unsigned long c_mil = millis();

    if ((unsigned long)(c_mil - p_mil) >= inv) {
      if(NormalHeartrateRange_Threshold == 0 || abs(HR.getBPM() - NormalHeartrateRange_Threshold) < normal_threshold)
      {
        if(NormalHeartrateRange_Threshold == 0)
        {
            Wireless.Send(1,HR.getBPM());  //Initial Heartrate
        }
        
        NormalHeartrateRange_Threshold = HR.getBPM();
        LowerHeartRateRange_Threshold = NormalHeartrateRange_Threshold - lower_threshold;
        OutsideHeartRateRange_Threshold = NormalHeartrateRange_Threshold + outside_threshold;
      }  
       p_mil = c_mil;
    }   
}

unsigned long ubi_p_mil = 0;
int ubi_last_hr = 0;
void ubidots_heartrate()
{
    unsigned long ubi_c_mil = millis();
    
    if ((unsigned long)(ubi_c_mil - ubi_p_mil) >= update_heartrate_to_ubidots_threshold) {  //every 1 hr.
       
       Wireless.Send(1,HR.getBPM());
       #ifdef DEVELOPER
       Serial.println("Updated Heart rate to ubidots.");
       #endif
       sent_hr = 0;
       sent_hr2 = 0;
       impacted = 0;
       pressed = 0;
       conc = 0;
       ubi_p_mil = ubi_c_mil;
    }   
}


void help()
{
  #ifdef DEVELOPER
    Serial.print(Wireless.Receive());
    Serial.print("\t");    
    Serial.print(NormalHeartrateRange_Threshold);
    Serial.print("\t");
    Serial.print(LowerHeartRateRange_Threshold);
    Serial.print("\t");
    Serial.print(OutsideHeartRateRange_Threshold);
    Serial.print("\t");    
    Serial.println(HR.getBPM());
  #endif
}

void alarm()
{
    if(impacted || conc || sent_hr2 || sent_hr || pressed)
    {
      digitalWrite(13,HIGH);
    }else{
      digitalWrite(13,LOW);
    }
}

