void drawGalaxy() {
  int k,b,s,n;
  byte color;

  arduboy.fillRect(enterprise.quadrant.x*16+1, (enterprise.quadrant.y+1)*7, 13, 7, WHITE);
  if(damage[1]>0){
    for ( byte i = 0; i < 8; i++) {
      for ( byte j = 0; j < 8; j++) {
        if( quadrant[i][j] > 128 ){
          quadrant[i][j] -= 128;
        }
      }
    }
    if(damage[2]==0) quadrant[enterprise.quadrant.x][enterprise.quadrant.y] += 128;
  }
  
  for ( byte i = 0; i < 8; i++) {
    for ( byte j = 0; j < 8; j++) {
      font3x5.setCursor(i*16+2, (j+1)*7);
      if (((quadrant[i][j] & 0b10000000) >> 7) == 0) {
        font3x5.print(F("   "));
      } else {
        if((enterprise.quadrant.x==i) && (enterprise.quadrant.y==j)){
          font3x5.setTextColor(BLACK);
        } else {
          font3x5.setTextColor(WHITE);
        }
        font3x5.print(numOfKlingon(quadrant[i][j]));
        font3x5.print(numOfBase(quadrant[i][j]));
        font3x5.print(numOfStar(quadrant[i][j]));
      }
    }
  }
  arduboy.fillRect(0, 0, 127, 7, WHITE);
  prints(8, 0, "GALAXY MAP  Q", 1);
  font3x5.setTextColor(BLACK);
  font3x5.print(enterprise.quadrant.x);
  font3x5.print('-');
  font3x5.print(enterprise.quadrant.y);
  font3x5.setTextColor(WHITE);
}

void drawMenu(){
  for (int i = 0; i < 8; i++) {
    prints(i * 4, 8, command[i], (gcurs == i));
  }
}

void drawSRS(byte dx) {
  char c;
  int xs, xe, ys, ye;
  font3x5.setTextColor(WHITE);
  if(damage[2]>0){
    xs = enterprise.sector.x -1; if(xs<0) xs=0;
    xe = enterprise.sector.x +1; if(xe>7) xe=7;
    ys = enterprise.sector.y -1; if(ys<0) ys=0;
    ye = enterprise.sector.y +1; if(ye>7) ye=7;
  } else {
    xs = 0;
    xe = 7;
    ys = 0;
    ye = 7;
  }
  for (int x = xs; x <= xe; x++) {
    for (int y = ys; y <= ye; y++) {
      switch ( sector[x][y] ) {
        case 0:
          c = ' ';
          break;
        case 1:
          c = 'E';
          break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
          c = 'K';
          break;
        case 10:
          c = 'B';
          break;
        case 11:
          c = '*';
          break;
      }
      font3x5.setCursor(x * 7 + 4 + dx, y * 7);
      font3x5.print( c );
      font3x5.print( ' ' );
    }
  }
}

void drawStatus() {
  prints(16, 0, "DAYS LEFT:", 0);
  font3x5.print( days );
  prints(16, 1, "CONDITION:", 0);
  if ( gdock == 1){
    font3x5.print(F("DOCKED"));
  } else if( gKlingon > 0){
    font3x5.print(F("RED"));
  } else if ( enterprise.energy < 1000){
    font3x5.print(F("YELLOW"));    
  } else {
    font3x5.print(F("GREEN"));    
  }
  prints(16, 2, " QUADRANT:", 0);
  font3x5.print(enterprise.quadrant.x);
  font3x5.print('-');
  font3x5.print(enterprise.quadrant.y);
  prints(16, 3, "   SECTOR:", 0);
  font3x5.print(enterprise.sector.x);
  font3x5.print('-');
  font3x5.print(enterprise.sector.y);
  prints(16, 4, "TORPEDOES:", 0);
  font3x5.print(enterprise.torpedo);
  prints(16, 5, "   ENERGY:", 0);
  font3x5.print(enterprise.energy);
  prints(16, 6, "  SHIELDS:", 0);
  font3x5.print(enterprise.shield);
  prints(16, 7, " KLINGONS:", 0);
  font3x5.print(totalKlingon);
}

void bombAnimation( byte x, byte y ) {
  point bomb[3];
  for (int i = 0; i < 3; i++) {
    bomb[i].x = x * 7 + random(5) + 3;  //arduboy.drawFastVLine(sectorCurs.x * 8 + 5, 0, 55, WHITE);
    bomb[i].y = y * 7 + random(5) + 1;  //arduboy.drawFastHLine(1, sectorCurs.y * 7 + 3, 66, WHITE);
  }
  for (int i = 0; i < 6; i++) {
    for ( int j = 0; j < 3; j++) {
      drawSRS(0);
      drawMenu();
      arduboy.drawCircle(bomb[j].x, bomb[j].y, i, WHITE);
    }
    
    arduboy.display();
    delay(100);
  }
  for (int i = 0; i < 6; i++) {
    for ( int j = 0; j < 3; j++) {
      drawSRS(0);
      drawMenu();
      arduboy.drawCircle(bomb[j].x, bomb[j].y, 6 - i, BLACK);
    }
    arduboy.display();
    delay(100);
  }
}

void phaserAnimation( byte x, byte y ) {
  for (int i = 4; i > 0; i--) {
    drawSRS(0);
    drawMenu();
    drawStatus();
    arduboy.drawRect(x*7+4+1-i*2, y*7+3-i*2, i*4,i*4, WHITE);
    arduboy.display();
    delay(100);
    arduboy.clear();
  }
  drawSRS(0);
  drawMenu();
  drawStatus();
  arduboy.display();
}

void crashAnimation(){
  for( int i=0; i<20; i++){
    drawSRS(random(8)-4);
    arduboy.display();
    delay(20);
    arduboy.fillRect(0,0,65,56,BLACK);
  }
}

int askAmount( int minimum, int maximum, char* message, int def, int m ){
  int result = def;
  int delta = 0;

  openWindow();

  while(1){
    arduboy.clear();
    drawSRS(0);
    drawStatus();
    drawMenu();
    arduboy.fillRect( 16, 14, 96, 36, WHITE );
    arduboy.fillRect( 17, 15, 94, 34, BLACK );
    font3x5.setTextColor(WHITE);
    font3x5.setCursor( 20, 20);
    font3x5.print( message );
    
    arduboy.pollButtons();
    if (arduboy.pressed(LEFT_BUTTON)) {
      result = (result + (maximum-1)) % maximum;
      delta++;
    }
    if (arduboy.pressed(RIGHT_BUTTON)) {
      result = (result + 1 ) % maximum;
      delta++;
    }
    if (arduboy.justReleased(LEFT_BUTTON)) {
      delta = 0;
    }
    if (arduboy.justReleased(RIGHT_BUTTON)) {
      delta = 0;
    }
    if (arduboy.justPressed(A_BUTTON)) {
      closeWindow();
      return result;
    }
    if(m==0){
      arduboy.drawRect(30, 30, 68, 5, WHITE);
      arduboy.fillRect(32, 32, result*64/(maximum-1), 1, WHITE);
      arduboy.fillRect(32 + result*64/(maximum-1), 32, (maximum-1-result)*64/(maximum-1), 1, BLACK);
      font3x5.setCursor( 30, 38);
      font3x5.print( minimum );
      font3x5.setCursor( 60, 38);
      font3x5.print( result );
      font3x5.setCursor( 90, 38);
      font3x5.print( maximum-1 );
    } else {
      arduboy.drawFastVLine(64, 20, 24, WHITE);
      arduboy.drawFastHLine(52, 32, 24, WHITE);
      arduboy.fillRect( 64 + 10*cos(2*3.1415*result/360)-1,32 + 10*sin(2*3.1415*result/360)-1,3,3,WHITE);
      font3x5.setCursor( 90, 38);
      font3x5.print( result );
    }  
    arduboy.display();
    if (delta < 5) {
      delay(250);
    } else {
      delay(20);
    }
  }
}

void windowAnimation( char *mess){
  for(int i=1; i<10; i++){
    arduboy.fillRect( 16, 32-i*2, 96, i*4, WHITE );
    arduboy.fillRect( 17, 32-i*2+1, 96-2, i*4-2, BLACK );
    arduboy.display();
    delay(20);
  }
  font3x5.setCursor(20,20);
  font3x5.print( mess );
  arduboy.display();
  while (1) {
    arduboy.pollButtons();
    if (arduboy.justPressed(A_BUTTON)) {
      break;
    }
  }
  for(int i=9; i>0; i--){
    arduboy.clear();
    drawSRS(0);
    drawStatus();
    drawMenu();
    arduboy.fillRect( 16, 32-i*2, 96, i*4, WHITE );
    arduboy.fillRect( 17, 32-i*2+1, 96-2, i*4-2, BLACK );
    arduboy.display();
    delay(20);
  }
  arduboy.clear();
  drawSRS(0);
  drawStatus();
  drawMenu();
  arduboy.display();
}

void openWindow(){
  for(int i=1; i<10; i++){
    arduboy.fillRect( 16, 32-i*2, 96, i*4, WHITE );
    arduboy.fillRect( 17, 32-i*2+1, 96-2, i*4-2, BLACK );
    arduboy.display();
    delay(10);
  }
  font3x5.setTextColor(WHITE);
}

void closeWindow(){
  for(int i=9; i>0; i--){
    arduboy.clear();
    drawSRS(0);
    drawStatus();
    drawMenu();
    arduboy.fillRect( 16, 32-i*2, 96, i*4, WHITE );
    arduboy.fillRect( 17, 32-i*2+1, 96-2, i*4-2, BLACK );
    arduboy.display();
    delay(10);
  }
  arduboy.clear();
  drawSRS(0);
  drawStatus();
  drawMenu();
  arduboy.display();
}
