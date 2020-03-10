void title() {
  arduboy.clear();
  strcpy_P(chrBuff, (char*)pgm_read_word(&(string_table[9])));
  for(int i=0; i < 128; i++){
    arduboy.clear();
    font3x5.setCursor(i-125, 7);
    font3x5.print( chrBuff );
    arduboy.display();
    delay(i/2);
  }
  prints(12, 7, "STARTREK", 1);
  arduboy.display();

  while(1){
    arduboy.pollButtons();
    if (arduboy.justPressed(A_BUTTON)) {
      initQuadrant();
      initEnterprise();
      initSector(enterprise.quadrant.x, enterprise.quadrant.y);
      break;
    }
  }
}

void toEnterprise( int mes ){
  arduboy.clear();
  font3x5.setTextColor(WHITE);
  strcpy_P(chrBuff, (char*)pgm_read_word(&(string_table[ 4 + mes ])));
  font3x5.setCursor(12,7);
  
  for( int i=0; i < strlen(chrBuff); i++){
    font3x5.print( chrBuff[i] );
    arduboy.display();
    delay(100);
  }
  while(1){
    arduboy.pollButtons();
    if (arduboy.justPressed(A_BUTTON)) {
      break;
    }
  }
}

void longRangeSensor(byte x, byte y) {
  if(damage[1]==0){
    for (int i = x - (x > 0); i <= x + (x < 7); i++) {
      for (int j = y - (y > 0); j <= y + (y < 7); j++) {
        if (quadrant[i][j] < 128) quadrant[i][j] += 128;
      }
    }
  } else {
    quadrant[enterprise.quadrant.x][enterprise.quadrant.y] += 128;
  }
}

void hitEnterprise( int dam ){
  if( enterprise.shield > dam ){
    enterprise.shield -= dam;
  } else {
    enterprise.energy -= dam - enterprise.shield;
    enterprise.shield = 0;
    damageMechanism();
    // 故障
  }
}

void dockBase(){
  enterprise.energy = 1500;
  enterprise.shield = 1500;
  enterprise.torpedo = 10;
}
