
#include "commons.h"
#include "zxlib.h"


unsigned int hit = 0, miss = 0, falseAlarm = 0, correctRejection = 0, correctRatio = 0;
int currentMiss = 0;



void Valve_ON(int valve){
 digitalWrite(valve+21+8, HIGH);
 if(valve==3){
 digitalWrite(6+21+8, HIGH);
 digitalWrite(6+21, HIGH);
 }
 if(valve>1){
 wait_ms(1000u);}
	digitalWrite(valve+21, HIGH);
 if(valve==4){
        digitalWrite(38,HIGH);}
}

void Valve_OFF(int valve){
  digitalWrite(valve+21+8, LOW);
  digitalWrite(6+21+8, LOW);
 if(valve>1){
 wait_ms(50u);}
	digitalWrite(valve+21, LOW);
  digitalWrite(6+21, LOW);
        //digitalWrite(38,LOW);
}




