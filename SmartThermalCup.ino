#include "SevenSegment.h"
#include <stdlib.h>
#include <avr/interrupt.h>

int RELAY_PIN = 9;

int sevenSegmentIdx = 0;
int sevenSegmentDisplay[3] = {12, 8, 8};
int temperatureList[10] = {1023,1023,1023,1023,1023,1023,1023,1023,1023,1023};
float avgTemperature = 0.;
int heat = 0;
int targetTemperature = 28;

int temperatureAdjust = 500;
int temperatureAdjust_shadow = 500;
int temperatureAdjust_ticks = 30;

void setup() {
  // put your setup code here, to run once:
  noInterrupts();
  TIMSK1 = (1<<OCIE1A); 
  TCCR1A = 0;
  TCCR1B = (1 << CS12)|(1<<WGM12);
  OCR1A=3125-1;

  
  TIMSK2 = (1<<OCIE2A);
  TCCR2A = 0;
  TCCR2B |= (1 << CS22)| (1 << CS20)|(1<<WGM22);
  OCR2A = 255 - 1;
  interrupts();

  sevenSegmentInit();
  
  pinMode(RELAY_PIN, OUTPUT);
  
  Serial.begin(9600);

}





ISR(TIMER1_COMPA_vect){  //Activated every 50 ms
  for(int i=0; i<10; i++){  
        temperatureList[i] = temperatureList[i+1];
    }
  temperatureList[9] = analogRead(A0);

  float avgTemperature_shadow = 0.;
  for(int i=0; i<10; i++){avgTemperature_shadow+=(temperatureList[i]*0.1);}
  avgTemperature = 0.3615*avgTemperature_shadow-38.011 - 3.8*heat - 5; //When 5V

  temperatureAdjust_shadow = analogRead(A1);
  if (temperatureAdjust_ticks){temperatureAdjust_ticks--;}
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

  if (abs(temperatureAdjust-temperatureAdjust_shadow)>=8){
    temperatureAdjust = temperatureAdjust_shadow;
    temperatureAdjust_ticks = 30;
    targetTemperature = int(temperatureAdjust/22.53) + 15;
  }

  if(temperatureAdjust_ticks){
    sevenSegmentDisplay[0] = 11;
    sevenSegmentDisplay[1] = (int)targetTemperature%100/10;
    sevenSegmentDisplay[2] = (int)targetTemperature%10;
  }else{
    sevenSegmentDisplay[0] = 12;
    sevenSegmentDisplay[1] = (int)avgTemperature%100/10;
    sevenSegmentDisplay[2] = (int)avgTemperature%10;
  }



  delay(100);
}


