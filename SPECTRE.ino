/*
 * SPECTRE INDUSTRIES
 * WRITED BY JATUPON HONGWEING.
*/

//--- CONFIGURATION -----------

short pulsePin = 6;                 
short serial_rx = 10;
short serial_tx = 11;

int NormalHeartrateRange_Threshold = 0;
int OutsideHeartRateRange_Threshold = 0;
int LowerHeartRateRange_Threshold  = 0;

const short normal_threshold = 7;
const int outside_threshold = 10;
const int lower_threshold = 20;

unsigned long update_heartrate_to_ubidots_threshold = 3600000;
unsigned long inv = 30000; //Initial Heartrate Time Threshold.
unsigned long unconcious_t = 120000;
 
void(* resetFunc) (void) = 0; //declare reset function @ address 0

//#define PRINT
#define DEVELOPER
