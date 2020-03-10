#include <Arduboy2.h>
#include "src/fonts/Font3x5.h"

#define numOfKlingon(q) (q & 0b01100000)>>5
#define numOfBase(q)    (q & 0b00010000)>>4
#define numOfStar(q)    (q & 0b00001111)
/*
galaxy[x,y]=0b00000000;
              || ||
              || |Star(0-8(max 15))
              || base(0-1)
              |klingon(0-3)
              known(0-1)
*/
Arduboy2Base arduboy;
Font3x5 font3x5 = Font3x5();

//messages
const char string_0[] PROGMEM = "COURSE?";
const char string_1[] PROGMEM = "DISTANSE?";
const char string_2[] PROGMEM = "ENERGY?";
const char string_3[] PROGMEM = "PERCENTAGE?";
const char string_4[] PROGMEM = "PHASER IS DAMAGED!";
const char string_5[] PROGMEM = 
    "TO ENTERPRISE:\n\n"
    "  DESTROY 25 KLINGONS IN\n"
    "  250 DAYS. THERE ARE 4\n"
    "  BASES.";

const char * const string_table[] PROGMEM = {
  string_0,
  string_1,
  string_2,
  string_3,
  string_4,
  string_5  
};

//struct
struct point {
  byte x;
  byte y;
};

struct ship {
  point sector;
  int energy;
  int torpedo;
};

char* command[] = {
  "MAP","NAV","TOR","PHA","SHI","DAM","PRO","COM"
};

char* computer[] = {
  "COMPUTE TRAJECTORY",
  " COMPUTE QUADRAT  ",
  "   LOCK TORPEDO   ",
  "    SELF REPAIR   ",
  "      RETURN      ",
  " GIVE UP MISSION  "
};

char* mechanism[] = {
  "WARP ENGINES",
  "L.R. SONSORS",
  "S.R. SENSORS",
  "PHOTON TUBES",
  "PHASER CNTRL",
  "SHIELD CNTRL",
  "PROBE SENSOR",
  "LIB COMPUTER"
};

struct player {
  point quadrant;
  point sector;
  int energy;
  int shield;
  int torpedo;
};

// globals
byte quadrant[8][8] = {};
byte sector[8][8] = {};
byte totalKlingon = 0, totalBase = 0;
byte gcurs=0, gKlingon=0;
int days=300;
bool gdock = 0;
char chrBuff[120];
bool gloop=0;
int damage[8]={0,0,0,0,0,0,0,0};

ship klingon[3];
point base;
player enterprise;

//ARDUBOY_NO_USB

void setup() {
  arduboy.boot();
  arduboy.setFrameRate(15);
  arduboy.initRandomSeed();
}

void loop() {

  title();
  order();
  dispMain();
  gameover();

}
