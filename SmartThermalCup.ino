#include "SevenSegment.h"

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
  displaySegment(sevenSegmentIdx, sevenSegmentDisplay[sevenSegmentIdx]);
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


