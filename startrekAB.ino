#include <Arduboy2.h>
#include "src/fonts/Font3x5.h"

#define numOfKlingon(q) (q & 0b01100000)>>5
#define numOfBase(q)    (q & 0b00010000)>>4
#define numOfStar(q)    (q & 0b00001111)

#define SPEED 10
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
const char string_1[] PROGMEM = "DISTANCE?";
const char string_2[] PROGMEM = "ENERGY?";
const char string_3[] PROGMEM = "PERCENTAGE?";
const char string_4[] PROGMEM = "NUMBER OF?";

const char string_5[] PROGMEM = //order
    "TO ENTERPRISE:\n\n"
    "  DESTROY %d KLINGONS IN\n"
    "  250 DAYS. THERE ARE %d\n"
    "  BASES.";

const char string_6[] PROGMEM = //time is out
    "TO ENTERPRISE:\n\n"
    "  \n"
    "  TIME IS OVER...\n"
    "  ";

const char string_7[] PROGMEM = //destroyed
    "TO ENTERPRISE:\n\n"
    "  YOU HAVE BEEN DESTROYED.\n"
    "  THE FEDERATION WILL BE\n"
    "  CONQUERED.";

const char string_8[] PROGMEM = //win
    "TO ENTERPRISE:\n\n"
    "  THE LAST KLINGON HAS BEEN\n"
    "  DESTROYED. THE FEDERATION\n"
    "  HAS BEEN SAVED !";

const char string_9[] PROGMEM = 
  "                ,------*------,\n"
  ",-------------   '---  ------'\n"
  " '-------- --'      / /\n"
  "     ,---' '-------/ /--,\n"
  "      '----------------'";

const char * const string_table[] PROGMEM = {
  string_0,
  string_1,
  string_2,
  string_3,
  string_4,
  string_5,
  string_6,
  string_7,
  string_8,
  string_9
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

const char menu_0[] PROGMEM = "MAP";
const char menu_1[] PROGMEM = "NAV";
const char menu_2[] PROGMEM = "TOR";
const char menu_3[] PROGMEM = "PHA";
const char menu_4[] PROGMEM = "SHI";
const char menu_5[] PROGMEM = "DAM";
const char menu_6[] PROGMEM = "PRO";
const char menu_7[] PROGMEM = "COM";
const char * const menu_table[] PROGMEM = {
  menu_0, menu_1, menu_2, menu_3,
  menu_4, menu_5, menu_6, menu_7
};

const char computer_0[] PROGMEM = "COMPUTE TRAJECTORY";
const char computer_1[] PROGMEM = " COMPUTE QUADRANT ";
const char computer_2[] PROGMEM = "   LOCK TORPEDO   ";
const char computer_3[] PROGMEM = "    SELF REPAIR   ";
const char computer_4[] PROGMEM = "      RETURN      ";
const char computer_5[] PROGMEM = " GIVE UP MISSION  ";
const char * const computer_table[] PROGMEM = {
  computer_0, computer_1, computer_2, computer_3,
  computer_4, computer_5
};

const char mechanism_0[] PROGMEM = "WARP ENGINES";
const char mechanism_1[] PROGMEM = "L.R. SENSORS";
const char mechanism_2[] PROGMEM = "S.R. SENSORS";
const char mechanism_3[] PROGMEM = "PHOTON TUBES";
const char mechanism_4[] PROGMEM = "PHASER CNTRL";
const char mechanism_5[] PROGMEM = "SHIELD CNTRL";
const char mechanism_6[] PROGMEM = "PROBE SENSOR";
const char mechanism_7[] PROGMEM = "LIB COMPUTER";
const char * const mechanism_table[] PROGMEM = {
  mechanism_0, mechanism_1, mechanism_2, mechanism_3,
  mechanism_4, mechanism_5, mechanism_6, mechanism_7
};

const char config_0[] PROGMEM = " NUM OF ENEMY";
const char config_1[] PROGMEM = "  NUM OF BASE";
const char config_2[] PROGMEM = "  BASE SUPPLY";
const char config_3[] PROGMEM = "   BLACK HOLE";
const char config_4[] PROGMEM = "      JAMMING";
const char config_5[] PROGMEM = "START MISSION";
const char * const config_table[] PROGMEM = {
  config_0, config_1, config_2, config_3,
  config_4, config_5
};

const char confItem_0[] PROGMEM = "MANY";
const char confItem_1[] PROGMEM = "ONCE";
const char confItem_2[] PROGMEM = "NOT EXIST";
const char confItem_3[] PROGMEM = "EXIST";
const char confItem_4[] PROGMEM = "DON'T";
const char confItem_5[] PROGMEM = "DO";
const char * const confItem_table[] PROGMEM = {
  confItem_0, confItem_1, confItem_2, confItem_3,
  confItem_4, confItem_5
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
byte totalKlingon = 25, totalBase = 3;
byte gcurs=0, gKlingon=0;
int days=250;
bool gdock = 0;
int gloop=0;
int damage[8]={0,0,0,0,0,0,0,0};

bool supply = 0;
bool existBlackhole = 0;
bool sBlackhole = 0;
bool jamming = 0;
bool sectorJamming = 0;

ship klingon[3];
point base;
player enterprise;

point blackhole;

//ARDUBOY_NO_USB

void setup() {
  arduboy.boot();
  arduboy.setFrameRate(15);
  arduboy.initRandomSeed();
}

void loop() {
  days = 250;
  totalKlingon = 25;
  totalBase = 3;
  title();
  configuration();
  toEnterprise(1);
  dispMain();
  toEnterprise( gloop + 1 );
  gloop=0;
}
