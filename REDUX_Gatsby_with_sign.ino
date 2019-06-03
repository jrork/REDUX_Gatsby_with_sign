//#include <noise.h>
#include <bitswap.h>
//#include <fastspi_types.h>
//#include <pixelset.h>
//#include <fastled_progmem.h>
//#include <led_sysdefs.h>
//#include <hsv2rgb.h>
#include <fastled_delay.h>
//#include <colorpalettes.h>
//#include <color.h>
//#include <fastspi_ref.h>
//#include <fastspi_bitbang.h>
//#include <controller.h>
//#include <fastled_config.h>
//#include <colorutils.h>
//#include <chipsets.h>
//#include <pixeltypes.h>
//#include <fastspi_dma.h>
//#include <fastpin.h>
//#include <fastspi_nop.h>
//#include <platforms.h>
//#include <lib8tion.h>
//#include <cpp_compat.h>
//#include <fastspi.h>
#include <FastLED.h>
//#include <dmx.h>
//#include <power_mgt.h>
#include <Keypad.h>
//#include "FastLED.h"

//setup Keypad
char hexaKeys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[4] = {9, 8, 7, 6}; 
byte colPins[4] = {5, 4, 3, 2}; 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, 4, 4); 

// How many leds in your strip?
#define NUM_LEDS 264
// How many leds per step
#define LEDS_PER_STEP 22
//How many total LEDs in stairs
#define LEDS_IN_STAIRS 176 
//How many LEDs in sign
#define LEDS_IN_SIGN 88

// DEFINE STEP BOUNDARIES
#define STAIRS_START (LEDS_IN_SIGN)
#define STEP_A_BEGIN (STAIRS_START)
#define STEP_A_END (STEP_A_BEGIN+LEDS_PER_STEP-1)
#define STEP_B_BEGIN (STEP_A_END+1)
#define STEP_B_END (STEP_B_BEGIN + LEDS_PER_STEP-1)
#define STEP_C_BEGIN (STEP_B_END+1)
#define STEP_C_END (STEP_C_BEGIN + LEDS_PER_STEP-1)
#define STEP_D_BEGIN (STEP_C_END + 1)
#define STEP_D_END (STEP_D_BEGIN + LEDS_PER_STEP-1)
#define STEP_E_BEGIN (STEP_D_END + 1)
#define STEP_E_END (STEP_E_BEGIN + LEDS_PER_STEP-1)
#define STEP_F_BEGIN (STEP_E_END+1)
#define STEP_F_END (STEP_F_BEGIN + LEDS_PER_STEP-1)
#define STEP_G_BEGIN (STEP_F_END+1)
#define STEP_G_END (STEP_G_BEGIN + LEDS_PER_STEP-1)
#define STEP_H_BEGIN (STEP_G_END + 1)
#define STEP_H_END (STEP_H_BEGIN + LEDS_PER_STEP-1)
//#define STEP_H_END NUM_LEDS

//// define sign sides
//#define SIGN_BOTTOM_SIDE_RIGHT 0
//#define SIGN_BOTTOM_SIDE_LEFT 30
//#define SIGN_LEFT_SIDE_TOP 43
//#define SIGN_LEFT_SIDE_BOTTOM 31
//#define SIGN_TOP_SIDE_LEFT 44
//#define SIGN_TOP_SIDE_RIGHT 74
//#define SIGN_RIGHT_SIDE_TOP 75
//#define SIGN_RIGHT_SIDE_BOTTOM 87
#define SIGN_START 0


//define stairs before adding sign
/*const int rows[4][LEDS_PER_STEP*2]= {
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175},
  {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153},
  {44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131},
  {66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109}
};*/

//define stairs after adding sign
const int rows[4][LEDS_PER_STEP*2]= {
  {88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263},
  {110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241},
  {132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219},
  {154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197}
};
//
////define sign
//const uint8_t sign[LEDS_IN_SIGN] {
//  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87
//};

/* I'd love to do this, but ran out of memory. */
//define sign in rows
//const int signRows[15][31]={
//  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
//  {31, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 87},
//  {32, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 86}, 
//  {33, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 85},
//  {34, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 84},
//  {35, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 83},
//  {36, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 82},
//  {37, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 81},
//  {38, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 80},
//  {39, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 79},
//  {40, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 78},
//  {41, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 77},
//  {42, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 76},
//  {43, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 265, 75},
//  {44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74}
//};//define sign in rows
//const int signRows[15][31]={
//  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
//  {31, 87},
//  {32, 86}, 
//  {33, 85},
//  {34, 84},
//  {35, 83},
//  {36, 82},
//  {37, 81},
//  {38, 80},
//  {39, 79},
//  {40, 78},
//  {41, 77},
//  {42, 76},
//  {43, 75},
//  {44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74}
//};

#define DATA_PIN 12

#define TWO_HUNDRED_PI 628
#define TWO_THIRDS_PI 2.094
#define ONE_QUARTER_PI 0.785

CRGB leds[NUM_LEDS];

uint8_t val1 = 0; //value for sineWave()
uint8_t val2 = 0; //value for sineWave()
uint8_t val3 = 0; //value for sineWave()
uint8_t val4 = 0; //value for sineWave()
uint16_t sineVal = 0;  //value for sineWave()

uint8_t stairMode = '0'; //0 turns all LEDS off, so we start there.
uint8_t signMode = 'H'; // sign has a default of off

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

const int potZero = A0;  
const int potOne = A1;  
uint8_t customKey = 0;

unsigned long gCurrentMillis = 0;
boolean bStrobe = false;
int interval = 0;
unsigned long gPrevMillis = 0;
uint8_t index = 0;


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, DATA_PIN, BRG>(leds, NUM_LEDS);
  FastLED.clear();
}

void fillRow(int n, CHSV color) {
  for (int i = 0; i < (LEDS_PER_STEP*2); i++) {
    leds[rows[n][i]]=color;
  }
}

/*Check for input from the keypad and assign to the appropriate section if it is there*/
boolean checkForInput(){

  customKey = (uint8_t)customKeypad.getKey();

  if (customKey){
    switch(customKey){
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '0':
        stairMode = customKey;
      break; //case 1-0

      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case '*':
      case '#':
        signMode = customKey;
      break; //case A-#
    }//switch
    return true;  //Key was pressed
  }
	return false;  //no key pressed
}  //checkForInput()

void loop() {
  checkForInput();
  doSign();
  doStairs();
  FastLED.show();
} //loop()

void doStairs() {
  switch (stairMode)
  {
    case '1'://1 White with brightness on pot 1
      dimOnPot(STAIRS_START, STEP_H_END, potOne, 0, 0, 100);

      break;//case 1
    
    case '2'://2 Gold fade stairs with brightness on pot 1
      dimOnPot(STAIRS_START, STEP_H_END, potOne, 34, 255, 150);
      break; //case 2
      
    case '3'://3 Pink with brightness on pot 1
      dimOnPot(STAIRS_START, STEP_H_END, potOne, 230, 255, 150);
      break; //case 3
    
    case '4':  //4 sparkle pink
      dimOnPot(STAIRS_START, STEP_H_END, potOne, 230, 255, 150);
      leds[random(NUM_LEDS)] = CRGB::White;
      break; //case 4

    case '5'://5 - Car motion to the left
          for (int i = 0; i < (LEDS_PER_STEP*2); i+=3) { //i+3
            for(int n=0; n<4; n++)  {
              leds[rows[n][i]] = CHSV(0, 0, 255);
              leds[rows[n][(i+1)%(LEDS_PER_STEP*2)]] = CHSV(0, 0, 255);
              leds[rows[n][(i+2)%(LEDS_PER_STEP*2)]] = CHSV(0, 0, 255);
              leds[rows[n][(i+21)%(LEDS_PER_STEP*2)]] = CHSV(0, 0, 255);
              leds[rows[n][(i+22)%(LEDS_PER_STEP*2)]] = CHSV(0, 0, 255);         
              leds[rows[n][(i+23)%(LEDS_PER_STEP*2)]] = CHSV(0, 0, 255);              
            }
            FastLED.show();  
          if(checkForInput()) {break;} 
            delay(27);  //20
            for(int n=0; n<4; n++)  {
              leds[rows[n][i]] = CHSV(34, 255, 150);
              leds[rows[n][(i+1)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
              leds[rows[n][(i+2)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
              leds[rows[n][(i+21)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
              leds[rows[n][(i+22)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
              leds[rows[n][(i+23)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
              //leds[rows[n][i-4]] = CHSV(34, 255, 150);
              if(checkForInput()) {break;}
            }
            FastLED.show();            
          if(checkForInput()) {break;} 
          } 
         
//          if (index < (LEDS_PER_STEP*2)) { 
//            for(int n=0; n<4; n++)  {
//              int i = index;
//              leds[rows[n][(i+0)%(LEDS_PER_STEP*2)]] = CHSV(0, 0, 255);
//              leds[rows[n][(i+1)%(LEDS_PER_STEP*2)]] = CHSV(0, 0, 255);
//              leds[rows[n][(i+2)%(LEDS_PER_STEP*2)]] = CHSV(0, 0, 255);
//              leds[rows[n][(i+21)%(LEDS_PER_STEP*2)]] = CHSV(0, 0, 255);
//              leds[rows[n][(i+22)%(LEDS_PER_STEP*2)]] = CHSV(0, 0, 255);         
//              leds[rows[n][(i+23)%(LEDS_PER_STEP*2)]] = CHSV(0, 0, 255);              
//
//              leds[rows[n][(i+3)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+4)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+5)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+6)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+7)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+8)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+9)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+10)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+11)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+12)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+13)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+14)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+15)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+16)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+17)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+18)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+19)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+20)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+24)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+25)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+26)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+27)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+28)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+29)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+30)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+31)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+32)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+33)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+35)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+35)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+36)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+37)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+38)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              leds[rows[n][(i+39)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
////              leds[rows[n][(i+40)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
////              leds[rows[n][(i+41)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
////              leds[rows[n][(i+42)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
////              leds[rows[n][(i+43)%(LEDS_PER_STEP*2)]] = CHSV(34, 255, 150);
//              index+=3;
//            }
//            
////            FastLED.show();   
//            delay(27);         
////          if(checkForInput()) {break;} 
//          }
//          else {index = 0;}

      break; //case 5

    case '6'://6 Swing swing, swing
      signMode = 'B';
      sineWave();
      break; //case 6
      
    case '7'://7 Gold Strobe sign and stairs
      signMode = 'H';  //turn off whatever mode the sign was in 
      twoColorStrobe(CHSV(34,255,255), CHSV(34,255,75), 50, 100);
      break; //case 7

    case '8'://8 Gold/Pink Strobe
      signMode = 'H';  //turn off whatever mode the sign was in 
      twoColorStrobe(CHSV(230,255,255), CHSV(34,255,255), 50, 100);
      break; //case 8
     
    case '9'://9 Everything gold to fade on pot 1
      signMode = 'H';  //turn off whatever mode the sign was in 
      dimOnPot(0, NUM_LEDS-1, potOne, 34, 255, 255);
      break; //case 9

      case '0':
        signMode = 'H';  //turn off whatever mode the sign was in 
        FastLED.showColor(CHSV(0, 0, 0));
      break; //case 0
      
      default:
      break; //default
      
  }//stair switch
} //doStairs()

void doSign(){
  switch(signMode){
      case 'A':  //dimmable gold on sign
        dimOnPot(SIGN_START, LEDS_IN_SIGN-1, potZero, 34, 255, 255);
      break;//case A

      case 'B'://B
        fadeToBlackBy( leds, LEDS_IN_SIGN, 10);  //see if this works?
        leds[random16(LEDS_IN_SIGN)] = CHSV( 34, 255, 255);
      break;//case B

      case 'C'://C
      break; //case C

      case 'D'://D
      
      break; //case D

      case '*'://* Gold pulse button
        FastLED.showColor(CHSV(34, 255, 255));
        delay(50);
        FastLED.showColor(CHSV(34,255,75));
        signMode='A';  //we want this to only happen once so set sign mode to default
      break;//case *

      case '#'://#
      break; //case #
      
      default:
      break; //default
  } //sign switch
}  //doSign()

//void showColor(){  //we don't use this function it the show but want to leave it
//      FastLED.showColor(CHSV(hue++, 255, 255));
//      delay(10);
//}

void findValues(){  //this is our value testing tool.  to use it, assign it to one of the free buttons above.
//setup values for pots
uint8_t hueValue = 0;
uint8_t satValue = 0;
uint8_t brightValue = 0;
      //Gold is at 34,255,255
      //Pink is at 0,124,255
      //better pink is at 230,255, 255
      //Teal is at 118, 124, 255
      brightValue = 128;
      hueValue = map(analogRead(potZero), 0, 1023, 0, 255);
      satValue = map(analogRead(potOne), 0, 1023, 0, 255);
      Serial.print(hueValue);
      Serial.print(" ");
      Serial.println(satValue);
      Serial.print(" ");
      Serial.print(brightValue);
      
      for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CHSV(hueValue, satValue, brightValue);
        }
        
}

void sineWave(){
  if (sineVal < TWO_HUNDRED_PI) {
        val1 = round(255 / 2.0 * (sin(sineVal / 100.0 + ONE_QUARTER_PI) + 1));
        val2 = round(255 / 2.0 * (sin(sineVal / 100.0) + 1));        
        val3 = round(255 / 2.0 * (sin(sineVal / 100.0 - ONE_QUARTER_PI) + 1));
        val4 = round(255 / 2.0 * (sin(sineVal / 100.0 - (ONE_QUARTER_PI*2)) + 1));

        fillRow(0, CHSV(34, 255, val1));
        fillRow(1, CHSV(34, 255, val2));
        fillRow(2, CHSV(34, 255, val3));        
        fillRow(3, CHSV(34, 255, val4));;
        
        sineVal++;
        
      }
  else {sineVal = 0;}
}

void dimOnPot(int ledStart, int ledStop, int lPot, uint8_t lHueVal, uint8_t lSatVal, uint8_t maxBrightValue){
  fill_solid( &(leds[ledStart]), ledStop-ledStart+1, CHSV(lHueVal, lSatVal, map(analogRead(lPot), 0, 1023, 0, maxBrightValue)));
}

void twoColorStrobe(CHSV color1, CHSV color2, int delay1, int delay2){
       gCurrentMillis = millis();
       
       if (gCurrentMillis - gPrevMillis >= interval){
         gPrevMillis = gCurrentMillis;
         bStrobe=!bStrobe;
       }

       if (bStrobe){
         fill_solid( &(leds[0]), NUM_LEDS,color2 );
         interval = delay1;
       }
       else {         
         fill_solid( &(leds[0]), NUM_LEDS, color1 );
         interval = delay2;
       }

       leds[random(NUM_LEDS)] = CRGB::White;    //Firestone - added soarkle
       
}//twoColorStrobe()


/*fill_solid(leds,3,0x00ff00); // 3 green
fill_solid(leds+3,3,0xff0000); // then 3 red
fill_gradient_RGB(leds, startpos, 0x000011, endpos, 0x110000);
fill_gradient_RGB(leds, NUM_LEDS, CRGB(50,0,200), CRGB(80,200,240)); // up to 4 of these
*/
