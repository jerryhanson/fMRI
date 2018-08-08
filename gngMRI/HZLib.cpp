#include "commons.h"
#include "math.h"
#include "zxLib.h"
//Mixture_Nonmatch:DualTask_Nonmatch+DNMS; Mixture_Match:DualTask_match+DNMS; HZ_Go2:????SpHit3; HZ_DNMS_Match:Match-go??DualTask2:Go/no-go????Reward,reward??????
//////////////HZ functions/////////////
void licksend(float timelen);
void HZ_gng(int trialNum,int waterLen,int threeOdor,int autoWater,int triggerDelay2);
void motor(int protoL, int protoR, int type, int yesLeft, int yesRight);
void feedWater(int waterLength);
void feedWaterNew(void);
void testPort(void);


static int waterSize[]={110,90,90,60,110,120,130,120};
int motorYes = 0;
void FuncID(int n) {
    switch (n) {
        case 1:{
            Valve_ON(1);}
            break;
        case 2:{
            int waterSizeInd= getFuncNumber(1)-1;
            feedWater(waterSize[waterSizeInd]);
            int calidir = getFuncNumber(1 );
            calidir=1;}
            break;
        case 3:{
            testPort();}
            break;
        case 4:
        {
            int sessionNum=(getFuncNumber(1)+1)*6;
            int triggerDelay=0;
            int trialNum=2;
            //////////////////////
            int waterSizeInd= 4;
            int autoWater= getFuncNumber(1)-1;
            int sessionID=0,sessionNumC=0,sessionNumD=0,threeOdor;
            while(sessionID<sessionNum){
            serialSend(SpSess, 1);
                srand(millis());
                if(rand()%2&sessionNumC<sessionNum/2){threeOdor=odor_C;
                sessionNumC++;}
                else{if(sessionNumD<sessionNum/2){threeOdor=odor_C;
                sessionNumD++;}
                else{threeOdor=odor_C;sessionNumC++; }}
            HZ_gng(trialNum,waterSize[waterSizeInd],threeOdor,autoWater,triggerDelay);
            sessionID++;
            serialSend(SpSess, 0);
            }
            break;
        }
        case 5:{
            Valve_ON(2);
            Valve_ON(3);
            Valve_ON(5);
            Valve_ON(6);}
            break;
        case 6:
        {
            unsigned int a = 0;
            int waterSizeInd= getFuncNumber(1)-1;
            while (a < 20) {
                wait_ms(1000);
                Valve_ON(1);
                wait_ms(waterSize[waterSizeInd]);
                Valve_OFF(1);
                a++;
            }}
            break;
        case 7:
        {
            while (1) {
                serialSend(17,analogRead(6)/10);
                delay(1000);
            }
           break;
        }
    }
}
    



void HZ_gng(int trialNum,int waterLen,int threeOdor,int autoWater,int triggerDelay2) {
    //waitTrial();
    int odorLen=1000;
    //////////////////////
//    Valve_ON(threeOdor);
//    wait_ms(odorLen);
//    Valve_OFF(threeOdor);
//    wait_ms(4000);
    /////////////////////////
    int trialNumA=0,trialNumB=0,trialID=0,odorIn;
    while(trialID<trialNum){
    while((triggerCount%8)|(triggerCount==0)){delay(20);}
    srand(millis());
    if(rand()%2&trialNumA<trialNum/2){odorIn=odor_A;trialNumA++;}
    else{if(trialNumB<trialNum/2){odorIn=odor_B;trialNumB++;}
    else{odorIn=odor_A;trialNumA++;}}
    /////////////////////////
    if(autoWater){odorIn=odor_A;}
    Valve_ON(odorIn);
    serialSend(SpOdor,odorIn);
    wait_ms(odorLen);
    Valve_OFF(odorIn);
    serialSend(SpOdor,odorIn);
    ///////////////////////////
    hasLicked = 0;
    if(threeOdor==odor_C){
        /////////////////
    if (odorIn==odor_A) {
    if(autoWater){
            Valve_ON(1);
            wait_ms(waterLen);
            Valve_OFF(1);
            }
    unsigned long millisT=millis();
        while (millis()-millisT < 1000 && !hasLicked) {
            hasLicked = isLicking;
        }
        if (!hasLicked) {
            currentMiss++;
            serialSend(SpMiss, 1);
        } else { //nonmatchLickLeft
            Valve_ON(1);
            wait_ms(waterLen);
            Valve_OFF(1);
            currentMiss = 0;
            serialSend(SpHit, 1);
        }
    } else 
    /////////////////////
    {
        unsigned long millisT=millis();
        while (millis()-millisT < 1000 && !hasLicked) {
            hasLicked = isLicking;
        }
        if (!hasLicked) {
            serialSend(SpCorrectRejection, 1);
        } else {
            currentMiss = 0;
            serialSend(SpFalseAlarm, 1);
            wait_ms(waterLen);
        }
    }}
    ////////////////////////////
    else{
    if (odorIn==odor_B) {
    if(autoWater){
        srand(millis());
        int rewardYes = rand() % 10;
        if (rewardYes < 5) {
            Valve_ON(1);
            wait_ms(waterLen);
            Valve_OFF(1);
        }
    }
    unsigned long millisT=millis();
        while (millis()-millisT < 1000 && !hasLicked) {
            hasLicked = isLicking;
        }
        if (!hasLicked) {
            currentMiss++;
            serialSend(SpMiss, 3);
        } else { //nonmatchLickLeft
            Valve_ON(1);
            wait_ms(waterLen);
            Valve_OFF(1);
            currentMiss = 0;
            serialSend(SpHit, 3);
        }
    } else {
        unsigned long millisT=millis();
        while (millis()-millisT < 1000 && !hasLicked) {
            hasLicked = isLicking;
        }
        if (!hasLicked) {
            serialSend(SpCorrectRejection, 3);
        } else {
            currentMiss = 0;
            serialSend(SpFalseAlarm, 3);
            wait_ms(waterLen);
        }
    }
    }
    trialID++;
    }
    
    }
void motor(int protoL, int protoR, int type, int yesLeft, int yesRight) {
    int motorLShort = protoL, motorRShort = protoR,
            motorLLong = protoL + 100, motorRLong = protoR + 100,
            motorL, motorR;
    if (yesLeft + yesRight > 0) {
        if (type == 1) { //1 shortForward 2 shortBackward
            motorL = motorLShort;
            motorR = motorRShort;
            if (motorL <= motorR) {
                if (yesLeft) {
                    digitalWrite(46,HIGH);
                }
                if (yesRight) {
                    digitalWrite(48,HIGH);
                }
                wait_ms(motorL);
                digitalWrite(46,LOW);
                wait_ms(motorR - motorL);
                digitalWrite(48,LOW);
            } else {
                if (yesLeft) {
                    digitalWrite(46,HIGH);
                }
                if (yesRight) {
                    digitalWrite(48,HIGH);
                }
                wait_ms(motorR);
                digitalWrite(48,LOW);
                wait_ms(motorL - motorR);
                digitalWrite(46,LOW);
            }
        } else if (type == 2) { //1 shortForward 2 shortBackward
            motorL = motorLShort;
            motorR = motorRShort;
            if (motorL <= motorR) {
                if (yesLeft) {
                    digitalWrite(47,HIGH);
                }
                if (yesRight) {
                    digitalWrite(49,HIGH);
                }
                wait_ms(motorL + 10);
                digitalWrite(47,LOW);
                wait_ms(motorR - motorL + 10);
                digitalWrite(49,LOW);
            } else {
                if (yesLeft) {
                    digitalWrite(47,HIGH);
                }
                if (yesRight) {
                    digitalWrite(49,HIGH);
                }
                wait_ms(motorR + 10);
                digitalWrite(49,LOW);
                wait_ms(motorL - motorR + 10);
                digitalWrite(47,LOW);
            }
        } else if (type == 3) {//3 longForward 4 longBackward
            motorL = motorLLong;
            motorR = motorRLong;
            if (motorL <= motorR) {
                if (yesLeft) {
                    digitalWrite(46,HIGH);
                }
                if (yesRight) {
                    digitalWrite(48,HIGH);
                }
                wait_ms(motorL);
                digitalWrite(46,LOW);
                wait_ms(motorR - motorL);
                digitalWrite(48,LOW);
            } else {
                if (yesLeft) {
                    digitalWrite(46,HIGH);
                }
                if (yesRight) {
                    digitalWrite(48,HIGH);
                }
                wait_ms(motorR);
                digitalWrite(48,LOW);
                wait_ms(motorL - motorR);
                digitalWrite(46,LOW);
            }
        } else if (type == 4) {//3 longForward 4 longBackward
            motorL = motorLLong;
            motorR = motorRLong;
            if (motorL <= motorR) {
                if (yesLeft) {
                    digitalWrite(47,HIGH);
                }
                if (yesRight) {
                    digitalWrite(49,HIGH);
                }
                wait_ms(motorL + 10);
                digitalWrite(47,LOW);
                wait_ms(motorR - motorL + 10);
                digitalWrite(49,LOW);
            } else {
                if (yesLeft) {
                    digitalWrite(47,HIGH);
                }
                if (yesRight) {
                    digitalWrite(49,HIGH);
                }
                wait_ms(motorR + 10);
                digitalWrite(49,LOW);
                wait_ms(motorL - motorR + 10);
                digitalWrite(47,LOW);
            }
        }
    }
}
void feedWater(int waterLength) {
    int wasLicking = 0;
    int lickCounter = 0;
    int interWater = 20000;
    int stopLoop=0,numLoop=0;
    unsigned int timerAll = 0;
    while(!stopLoop&&numLoop<2){
    motor(500+100*numLoop,500+100*numLoop,1,0,1);
    Valve_ON(1);
    wait_ms(200);
    Valve_OFF(1);
    wait_ms(1000);
    motor(600+100*numLoop,600+100*numLoop,4,0,1);
    Valve_ON(1);
    wait_ms(100);
    Valve_OFF(1);
    unsigned long millisT=millis();
   // while (timerAll < 20000 && millis()-millisT < interWater) {
    while(1){
        if (isLicking && !wasLicking) {
            if (lickCounter % 3 == 0) {
                Valve_ON(1);
            timerAll = timerAll + millis()-millisT;
            millisT=millis();
                interWater = 10000;
                serialSend(SpHit, 1);
            }
            wasLicking = 1;
            lickCounter++;
            if(lickCounter>10){
            stopLoop=1;}
        }
        else if (wasLicking && !isLicking) {
            wasLicking = 0;
        }
        if (millis()-millisT > waterLength) {
            Valve_OFF(1);
        }
    }numLoop++;
            Valve_OFF(1);
    }
            Valve_OFF(1);}
void feedWaterNew(void) {
    int waterLength = 40;
    int wasLicking = 0;
    int lickCounter = 0;
    unsigned long millisT=millis();
    Valve_ON(1);
    wait_ms(200);
    Valve_OFF(1);
    while (lickCounter < 5) {
        if (isLicking && !wasLicking) {
            millisT=millis();
            if (lickCounter % 3 == 0) {
                Valve_ON(1);
            }
            wasLicking = 1;
            lickCounter++;
        } else if (wasLicking && !isLicking) {
            wasLicking = 0;
        }
        if (millis()-millisT > waterLength) {
            Valve_OFF(1);
        }
    }
    Valve_OFF(1);
}
void testPort(void) {
    int i = 1;
    i = getFuncNumber(1);
    while(i){
        // i = getFuncNumber(1, "Port:1-8");
        Valve_ON(i);
        serialSend(SpOdor, i);
        digitalWrite(38,HIGH);
        //DelayNmSecNew(4000);
        if(i==4){
        wait_ms(20000u);}
        else{
        wait_ms(1000u);}
        Valve_OFF(i);
        serialSend(SpOdor, i);
        digitalWrite(38,LOW);
        wait_ms(4000u);
    }
}



