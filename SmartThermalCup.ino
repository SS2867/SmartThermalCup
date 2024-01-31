int RELAY_PIN = 9;
void setup() {
  // put your setup code here, to run once:
  noInterrupts();
  TIMSK1 = (1<<OCIE1A);
  TCCR1A |= (1 << CS12)|(1<<WGM12);
  OCR1A = 3125 - 1;
  interrupts();

  pinMode(RELAY_PIN, OUTPUT);
  
  Serial.begin(9600);

}

int temperatureList[10] = {1023,1023,1023,1023,1023,1023,1023,1023,1023,1023};
float avgTemperature = 0.;
int heat = 0;
int targetTemperature = 28;

ISR(TIMER1_COMPA_vect){
  for(int i=0; i<10; i++){  
        temperatureList[i] = temperatureList[i+1];
    }
  temperatureList[9] = analogRead(A0);

  float avgTemperature_shadow = 0.;
  for(int i=0; i<10; i++){avgTemperature_shadow+=(temperatureList[i]*0.1);}
  avgTemperature = 0.3615*avgTemperature_shadow-38.011 - 3.8*heat - 5; 
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println(avgTemperature);

  
  if (avgTemperature>targetTemperature+1 && heat==1){
    heat=0;
    digitalWrite(RELAY_PIN, LOW);
    delay(550);    
  }else if(avgTemperature<targetTemperature-1 && heat==0){
    heat=1;
    digitalWrite(RELAY_PIN, HIGH);
    delay(550);
  }

  delay(100);
}
