// NAV PRO PHA TOR SHE MAP DAM COM
// REP SRS LRS MAP PHA TOR NAV

// engene
// LR sensor
// SR eensor
// Phaser
// torpedo
// computer
// probe

//compute quadrant
//compute sector
//torpedo attack
//self repair
//quit game

// 複数のクリンゴン
// 途中がenergy==0になっても、quadrantから引いてはいけない。
// 透明のklingon


void warpQuadrant( byte x, byte y, int deg ){
  deg += 180;
  arduboy.fillRect(0,0,60,56,BLACK);
  point dot[16];
  for(int i=0; i<16; i++){
    dot[i].x=random(56)+4;
    dot[i].y=random(56);
  }
  for(int j=0; j<30; j++){
    for(int i=0; i<16; i++){
      arduboy.drawPixel( dot[i].x + j*cos(2*3.1415*deg/360), dot[i].y + j*sin(2*3.1415*deg/360), WHITE);
    }
    arduboy.display();
    delay(20);
  }
  delay(200);
  for(int j=29; j>0; j--){
    for(int i=0; i<16; i++){
      arduboy.drawPixel( dot[i].x + j*cos(2*3.1415*deg/360), dot[i].y + j*sin(2*3.1415*deg/360), BLACK);
    }
    arduboy.display();
    delay(20);
  }
    
  gdock = 0;
  
  if(random(5)==0) damageMechanism();
  
  quadrant[enterprise.quadrant.x][enterprise.quadrant.y] =
         (quadrant[enterprise.quadrant.x][enterprise.quadrant.y] & 0b10011111) + 32*gKlingon;
  enterprise.quadrant.x = x;
  enterprise.quadrant.y = y;
  initSector(enterprise.quadrant.x, enterprise.quadrant.y);
   
  longRangeSensor(enterprise.quadrant.x, enterprise.quadrant.y);
  
}

void waitA(){
  while (1) {
    arduboy.pollButtons();
    if (arduboy.justPressed(A_BUTTON)) {
      break;
    }
  }
}
