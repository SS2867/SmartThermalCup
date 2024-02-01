#ifndef __SEVENSEGMENT_H
#define __SEVENSEGMENT_H
#include <Arduino.h>



void sevenSegmentInit(void){
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

void displaySegment(int sevenSegmentIdx, int disp){
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(2, HIGH); digitalWrite(3, HIGH); digitalWrite(4, HIGH); digitalWrite(5, HIGH); digitalWrite(6, HIGH); digitalWrite(7, HIGH); digitalWrite(8, HIGH);
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
}
#endif

