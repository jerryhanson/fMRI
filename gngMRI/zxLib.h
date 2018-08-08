#include <LiquidCrystal.h>


#ifndef ZXLIB
  #define  ZXLIB

 extern boolean  isLicking;
extern boolean  hasLicked;
extern int triggerCount;
  

  
  //laser trial type
	#define laserOff 0
	#define laserDuring3Baseline 3
	#define laserDuring4Baseline 4
	#define laserDuringBaseline 5
	#define laserDuringDelay_Odor2 6
	#define laserDuringBaseAndResponse 7
	#define laserDuringBaselineNDelay 9
	#define laserDuringDelay 10
	#define laserDuringDelayChR2 11

	#define laserRampDuringDelay 14
	//#define laserLDuringDelay 15
	//#define laserRDuringDelay 16
	#define laserDuringOdor 20
	#define laserDuring1stOdor 21
	#define laserDuring2ndOdor 22
	#define laserDuringBeginningToOneSecInITI 30
	#define laserDuringEarlyDelay 40
	#define laserDuringMidDelay 50
	#define laserDuringLateDelay 60
	#define laserNoDelayControlShort 69
	#define laserNoDelayControl 70
	#define laserDuringEarlyHalf 80
	//#define laserDuring1Terice 81
	//#define laserDuring2Terice 82
	//#define laserDuring3Terice 83
	#define laserDuringLateHalf 90
	#define laserDuring1Quarter 91
	#define laserDuring2Quarter 92
	#define laserDuring3Quarter 93
	#define laserDuring4Quarter 94
	#define laserDuringResponseDelay 95

	#define laserDuring12s1Quarter 96
	#define laserDuring12s2Quarter 97
	#define laserDuring12s3Quarter 98
	#define laserDuring12s4Quarter 99

	#define trialTypeDnmsSwitch 100
	#define trialTypeGoNogoSwitch 110
	#define laser4sRamp 121
	#define laser2sRamp 122
	#define laser1sRamp 123
	#define laser_5sRamp 124
	#define laserSufficiency 130
	#define laserBeforeDistractor 140
	#define laserCoverDistractor 145
	#define laserAfterDistractor 149






	//#define atTrialStart 10
	#define fourSecBeforeFirstOdor 4
	#define threeSecBeforeFirstOdor 5
	#define oneSecBeforeFirstOdor 10
	#define at200mSBeforeFirstOdor 18
	#define atFirstOdorBeginning 20
	#define atFirstOdorEnd 30
	#define atDelayBegin 40
	#define atDelay_5SecIn 42
	#define atDelay1SecIn 200
	#define atDelay1_5SecIn 205
	#define atDelay2SecIn 210
	#define atDelay2_5SecIn 215
	#define atDelay3SecIn 220
	#define atDelay500msToMiddle 225
	#define atDelayMiddle 230
	#define atDelayMid2Sec 235
	#define atDelayMid2_5Sec 240
	#define atDelayMid3Sec 245
	#define atDelayLast2_5SecBegin 250
	#define atDelayLast2SecBegin 255
	#define atDelayLast1_5SecBegin 61
	#define atDelayLastSecBegin 63
	#define atDelayLast500mSBegin 65
	//#define atDelayLast200mSBegin 68
	#define atSecondOdorBeginning 70
	#define atSecondOdorEnd 80
	//#define atRewardDelayBeginning 90
	#define atRewardBeginning 100
	//#define atRewardBeginning 110
	#define atRewardEnd 120
	#define atITIBeginning 130
	#define atITIOneSecIn 140
	#define atITILastSecIn 150
	#define atITIEnd 160


	//Laser Session Type, including ZJ's variety
	#define LASER_OTHER_TRIAL 1
	#define LASER_NO_TRIAL 2
	#define LASER_EVERY_TRIAL 3
	//#define laserFollowOdorA 4
	//#define laserFollowOdorB 5
	//#define laser1and2Half 6
	//#define laser3and4Quarter 10
	#define LASER_LR_EACH_QUARTER 20
	#define LASER_EACH_QUARTER 21
	#define LASER_12s_LR_EACH_QUARTER 25
	#define LASER_12s_EACH_QUARTER 26
	#define LASER_VARY_LENGTH 30
	#define LASER_LR_EVERYTRIAL 40
	#define LASER_LR_EVERY_OTHER_TRIAL 42
	#define LASER_INCONGRUENT_CATCH_TRIAL 45


	#define LICK_LEFT (PORTDbits.RD12 || !PORTDbits.RD14)
	#define LICK_RIGHT (PORTDbits.RD13 || !PORTDbits.RD15)
	#define LICK_ANY (PORTDbits.RD12 || PORTDbits.RD13 || !PORTDbits.RD14 || !PORTDbits.RD15)
	#define LICKING_LEFT 2
	#define LICKING_RIGHT 3
	#define LICKING_BOTH 127

	#define SHAPING_TASK 10
	#define DNMS_LEARNING_TASK 19
	#define DNMS_TASK 20
	//#define _ASSOCIATE_SHAPING_TASK 24
	//#define _ASSOCIATE_TASK 25
	#define GONOGO_TASK 30
	#define DNMS_2AFC_TEACH 38
	#define DNMS_LR_LEARNING_TASK 39
	#define DNMS_2AFC_TASK 40
	#define GONOGO_2AFC_TEACH 49
	#define GONOGO_LR_TASK 50
	#define NO_ODOR_CATCH_TRIAL_TASK 60
	#define VARY_ODOR_LENGTH_TASK 70
	#define OPTO_ODPA_TASK 80
	#define OPTO_ODPA_SHAPING_TASK 81
	#define DELAY_DISTRACTOR_LEARNING 90
	#define DELAY_DISTRACTOR_TASK 95
	#define ODPA_SHAPING_TASK 99
	#define ODPA_TASK 100


	#define EEP_DUTY_LOW_L_OFFSET 0
	#define EEP_DUTY_HIGH_L_OFFSET 2
	#define EEP_DUTY_LOW_R_OFFSET 4
	#define EEP_DUTY_HIGH_R_OFFSET 6



	#define PERM_INFO 21

	#define DMS_LR_Teach_LOFF 100
	#define DMS_LR_Teach_LON 101
	#define MSWOD_LR_Teach_LOFF 102
	#define DMS_LR_Teach_ONOFF 103
	#define DMS_LR_5Delay_Laser 104
	#define DMS_LR_8Delay_Laser 105
	#define DMS_LR_12Delay_Laser 106
	#define DMS_LR_1Odor_Laser 107
	#define DMS_LR_2Odor_Laser 108
	#define DMS_LR_bothOdor_Laser 109
	#define DMS_LR_baseline_Laser 110
	#define DMS_LR_response_Laser 111
	  
  
  

  
  typedef struct {
    unsigned int stim1Length;
    unsigned int stim2Length;
    unsigned int distractorLength;
    unsigned int currentDistractor;
    unsigned int distractorJudgingPair;
} STIM_T;
  
  
  
  typedef struct {
    unsigned int timer;
    unsigned int onTime;
    unsigned int offTime;
    unsigned int ramp;
    unsigned int ramping;
    unsigned int on;
    unsigned int side;
} LASER_T;
  
  
	void zxFunc(int n);
	void zxTimer1();
	int getFuncNumber(int );
	void serialSend(int type, int value);
	void wait_ms(int ms);

void FuncID(int n);

#endif






