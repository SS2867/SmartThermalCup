int RELAY_PIN = 9;

int sevenSegmentIdx = 0;
int sevenSegmentDisplay[3] = {7, 11, 12};
int temperatureList[10] = {1023,1023,1023,1023,1023,1023,1023,1023,1023,1023};
float avgTemperature = 0.;
int heat = 0;
int targetTemperature = 28;

void setup() {
  // put your setup code here, to run once:
  noInterrupts();
  TIMSK1 = (1<<OCIE1A);
  TCCR1A |= (1 << CS12)|(1<<WGM12);
  OCR1A = 3125 - 1;

  
  TIMSK2 = (1<<OCIE2A);
  TCCR2A |= (1 << CS22)| (1 << CS20)|(1<<WGM22);
  OCR2A = 255 - 1;
  interrupts();

  sevenSegmentInit();
  
  pinMode(RELAY_PIN, OUTPUT);
  
  Serial.begin(9600);

}

void sevenSegmentInit(){
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}



ISR(TIMER1_COMPA_vect){
  for(int i=0; i<10; i++){  
        temperatureList[i] = temperatureList[i+1];
    }
  temperatureList[9] = analogRead(A0);

  float avgTemperature_shadow = 0.;
  for(int i=0; i<10; i++){avgTemperature_shadow+=(temperatureList[i]*0.1);}
  avgTemperature = 0.3615*avgTemperature_shadow-38.011 - 3.8*heat - 5; 
}

ISR(TIMER2_COMPA_vect){
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(2, HIGH); digitalWrite(3, HIGH); digitalWrite(4, HIGH); digitalWrite(5, HIGH); digitalWrite(6, HIGH); digitalWrite(7, HIGH); digitalWrite(8, HIGH);
  int disp = sevenSegmentDisplay[sevenSegmentIdx];
  switch(sevenSegmentIdx){
    case 2: digitalWrite(10, HIGH); break;
    case 1: digitalWrite(11, HIGH); break;
    case 0: digitalWrite(12, HIGH); break;
  }
  switch(disp){
    case 0: digitalWrite(2, 0); digitalWrite(3, 0); digitalWrite(4, HIGH); digitalWrite(5, 0); digitalWrite(6, 0); digitalWrite(7, 0); digitalWrite(8, 0); break;
    case 1: digitalWrite(2, HIGH); digitalWrite(3, 0); digitalWrite(4, HIGH); digitalWrite(5, HIGH); digitalWrite(6, HIGH); digitalWrite(7, 0); digitalWrite(8, HIGH); break;
    case 2: digitalWrite(2, 0); digitalWrite(3, 0); digitalWrite(4, 0); digitalWrite(5, 0); digitalWrite(6, 0); digitalWrite(7, HIGH); digitalWrite(8, HIGH); break;
    case 3: digitalWrite(2, 0); digitalWrite(3, 0); digitalWrite(4, 0); digitalWrite(5, HIGH); digitalWrite(6, 0); digitalWrite(7, 0); digitalWrite(8, HIGH); break;
    case 4: digitalWrite(2, HIGH); digitalWrite(3, 0); digitalWrite(4, 0); digitalWrite(5, HIGH); digitalWrite(6, HIGH); digitalWrite(7, 0); digitalWrite(8, 0); break;
    case 5: digitalWrite(2, 0); digitalWrite(3, HIGH); digitalWrite(4, 0); digitalWrite(5, HIGH); digitalWrite(6, 0); digitalWrite(7, 0); digitalWrite(8, 0); break;
    case 6: digitalWrite(2, 0); digitalWrite(3, HIGH); digitalWrite(4, 0); digitalWrite(5, 0); digitalWrite(6, 0); digitalWrite(7, 0); digitalWrite(8, 0); break;
    case 7: digitalWrite(2, 0); digitalWrite(3, 0); digitalWrite(4, HIGH); digitalWrite(5, HIGH); digitalWrite(6, HIGH); digitalWrite(7, 0); digitalWrite(8, HIGH); break;
    case 8: digitalWrite(2, 0); digitalWrite(3, 0); digitalWrite(4, 0); digitalWrite(5, 0); digitalWrite(6, 0); digitalWrite(7, 0); digitalWrite(8, 0); break;
    case 9: digitalWrite(2, 0); digitalWrite(3, 0); digitalWrite(4, 0); digitalWrite(5, HIGH); digitalWrite(6, 0); digitalWrite(7, 0); digitalWrite(8, 0); break;
    case 10: digitalWrite(2, HIGH); digitalWrite(3, HIGH); digitalWrite(4, HIGH); digitalWrite(5, HIGH); digitalWrite(6, HIGH); digitalWrite(7, HIGH); digitalWrite(8, HIGH); break;
    case 11: digitalWrite(2, HIGH); digitalWrite(3, HIGH); digitalWrite(4, HIGH); digitalWrite(5, HIGH); digitalWrite(6, HIGH); digitalWrite(7, HIGH); digitalWrite(8, 0); break;
    case 12: digitalWrite(2, HIGH); digitalWrite(3, HIGH); digitalWrite(4, HIGH); digitalWrite(5, 0); digitalWrite(6, HIGH); digitalWrite(7, HIGH); digitalWrite(8, HIGH); break;
  }
  sevenSegmentIdx = (sevenSegmentIdx+1)%3;
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
