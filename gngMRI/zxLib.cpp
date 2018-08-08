#include <LiquidCrystal.h>
#include "TimerOne.h"
#include "commons.h"
#include "zxLib.h"

LiquidCrystal lcd(46,45,44,43,42,41,40);

boolean isLicking=false;
boolean hasLicked=false;
int triggerCount=0;
int hasTriggered=1;
int loopT=0;
const int lickBound = 100; //Larger is sensitive
unsigned long targetTime;
unsigned long timerI=millis();//serial send interval control to 5ms
unsigned long timerJ=millis();//serial send interval control to 5ms

unsigned int laserSessionType = LASER_EVERY_TRIAL;
unsigned int taskType = DNMS_TASK;

unsigned int highLevelShuffleLength = 12u;

const char* odorTypes[] = {" ","W","B","Y", "L", "R", "Q", "H", "N", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

STIM_T stims = {.stim1Length = 1000u, .stim2Length = 1000u, .distractorLength = 500u, .currentDistractor = 7u, .distractorJudgingPair = 8u};
LASER_T laser = {.timer = 0u, .onTime = 65535u, .offTime = 0u, .ramp = 0u, .ramping = 0u, .on = 0u, .side = 1u}; //1L,2R,3LR
typedef unsigned int _delayT;


void callReset(){
	Timer1.detachInterrupt();
//	Serial.read();
	delay(100);
	//serialSend(SpSess,0);
	delay(100);
	pinMode(52,OUTPUT);
	pinMode(53,OUTPUT);
	digitalWrite(52,LOW);
	digitalWrite(53,HIGH);
}

void zxTimer1(){
    if(millis()-timerI>25){
        if(loopT%2){
  if ((analogRead(6)<600)
          &&!isLicking){ //Low is lick
    isLicking=true;
    serialSend(0,1);
    timerI=millis();
  }else if (analogRead(6)>700)
  {
    isLicking=false;
  }
        }
        else{
//////////////////////////////////////
    if((analogRead(4)<500)&&!hasTriggered){
        hasTriggered=1;
        timerJ=millis();
       triggerCount=triggerCount+1;
       serialSend(16,triggerCount);
    }  
  else if(analogRead(4)>500){ 
   hasTriggered=0;}
        }
    loopT++;}
  if(Serial.peek()==0x2a){
	  callReset(); }
   }


int getFuncNumber(int targetDigits){
    int bitSet[targetDigits];
    int bitValue[targetDigits];
    unsigned int n;
    int iter;
    int iter1;

    for (iter = 0; iter < targetDigits; iter++) {
        bitSet[iter] = 0;
        bitValue[iter] = -6;
    }
	

	
    for (iter = 0; iter < targetDigits; iter++) {
        while (!bitSet[iter]) {
            if (Serial.peek() > 0) {

//				if(Serial.peek()==0x2a){
//				  callReset();
//				} 
                bitValue[iter] = Serial.read() - 0x30;
                bitSet[iter] = 1;
            } 
        }
        serialSend(SpCome, bitValue[iter]);
		


	
    }
    n = 0;
    for (iter1 = 0; iter1 < targetDigits; iter1++) {
        n = n * 10 + bitValue[iter1];
    }
    return n;
}

void serialSend(int type, int value){
  byte toSend[]= {85, (byte) type, (byte) value,170};
  if(type){timerI=millis()-40;}//do not send lick in future 10 mili seconds
  Serial.write(toSend,4);
  if(type){timerI=millis()-40;}//do not send lick in future 10 mili seconds
}




void waitTrial(){
	
}



void wait_ms(int ms){
  unsigned long base=millis();
  while(((unsigned long)ms+base)>millis()){
  }
}








