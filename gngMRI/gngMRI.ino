
#include "TimerOne.h"
#include "commons.h"
#include "zxLib.h"


void setup() {

 // pinMode 5V+ flowmeter
 // pinMode 5V+ fan
	pinMode(22, OUTPUT); // water
	pinMode(23, OUTPUT); // odor1
	pinMode(24, OUTPUT); // odor2
	pinMode(25, OUTPUT); // 
	pinMode(26, OUTPUT); // odor3
	pinMode(27, OUTPUT); // odor4
	pinMode(28, OUTPUT); // odor5
	pinMode(29, OUTPUT); // odor6
  pinMode(30, OUTPUT); // 
  pinMode(31, OUTPUT); // odor1
  pinMode(32, OUTPUT); // odor2
	pinMode(33, OUTPUT); // 
  pinMode(34, OUTPUT); // odor3
  pinMode(35, OUTPUT); // odor4
  pinMode(36, OUTPUT); // odor5
  pinMode(37, OUTPUT); // odor6

  
	pinMode(38, OUTPUT);
	pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
	pinMode(42, OUTPUT);
	pinMode(43, OUTPUT);
	pinMode(44, OUTPUT);
	pinMode(45, OUTPUT);
	pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT);
	
	pinMode(52, OUTPUT);
	pinMode(53, OUTPUT);

  digitalWrite(50,HIGH);
	digitalWrite(52,LOW);
	digitalWrite(53,LOW);
	digitalWrite(39,LOW);
	
	Serial.begin(9600);
	//lcd.begin(16,2);
	Timer1.initialize(500);
	Timer1.attachInterrupt(zxTimer1);
	byte init[]={0,1,2,3};
	Serial.write(init,4);
// Serial.write(new byte[]{0,128},2);
}

void loop() {
  // put your main code here, to run repeatedly: 
    delay(1000); 
  int n = getFuncNumber(1);
  randomSeed(analogRead(1));
  switch(n){
            case 1 ... 9:
                FuncID(n);
                break;
  }

}




