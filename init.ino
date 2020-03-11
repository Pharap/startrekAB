void initQuadrant2() {
  byte known, klingon, base, star;
  totalKlingon = 0;
  totalBase = 0;

  for ( int i = 0; i < 8; i++) {
    for ( int j = 0; j < 8; j++) {
      known = 0;
      int r = random(100);
      if (r > 98) {
        klingon = 3;
      } else if (r > 95) {
        klingon = 2;
      } else if (r > 80) {
        klingon = 1;
      } else {
        klingon = 0;
      }
      r = random(100);
      if (r > 96) {
        base = 1;
      } else {
        base = 0;
      }
      star = random(8) + 1;
      totalKlingon += klingon;
      totalBase += base;
      quadrant[i][j] = known * 128 + klingon * 32 + base * 16 + star;
    }
  }
}

void initQuadrant() {
  byte counter=0;
  int rx,ry;
  totalKlingon = 25;
  totalBase = 3;

  memset(&quadrant, 0, sizeof(quadrant));
  
  while( counter < totalKlingon ){
    rx = random(8);
    ry = random(8);
    if( numOfKlingon(quadrant[rx][rx]) < 3 ){
      quadrant[rx][ry] += 32;
      counter++;
    }
  }
  counter=0;
  while( counter < totalBase ){
    rx = random(8);
    ry = random(8);
    if( numOfBase(quadrant[rx][rx]) < 1 ){
      quadrant[rx][ry] += 16;
      counter++;
    }
  }
  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      quadrant[i][j] += random(8)+1;
    }
  }
}

void initEnterprise() {
  enterprise.quadrant.x = random(8);
  enterprise.quadrant.y = random(8);
  enterprise.energy = 1500;
  enterprise.shield = 1500;
  enterprise.torpedo = 10;
  for( int i=0; i<8; i++){
    damage[i]=0;
  }
  longRangeSensor( enterprise.quadrant.x, enterprise.quadrant.y );
}

void initSector(byte mx, byte my) {
  byte k = numOfKlingon(quadrant[mx][my]);
  byte b = numOfBase(quadrant[mx][my]);
  byte s = numOfStar(quadrant[mx][my]);
  int rx, ry;
  int counter = 0;
  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      sector[i][j]=0;
    }
  }
  rx = random(8);
  ry = random(8);
  sector[rx][ry] = 1;
  enterprise.sector.x = rx;
  enterprise.sector.y = ry;

  while (counter < k) {
    rx = random(8);
    ry = random(8);
    if (sector[rx][ry] == 0) {
      sector[rx][ry] = 2+counter;
      klingon[counter].sector.x = rx;
      klingon[counter].sector.y = ry;
      klingon[counter].energy = 200;
      klingon[counter].torpedo = 2;
      counter++;
    }
  }

  counter = 0;
  while (counter < b) {
    rx = random(8);
    ry = random(8);
    if (sector[rx][ry] == 0) {
      sector[rx][ry] = 10;
      base.x = rx;
      base.y = ry;
      counter++;
    }
  }

  counter = 0;
  while (counter < s) {
    rx = random(8);
    ry = random(8);
    if (sector[rx][ry] == 0) {
      sector[rx][ry] = 11;
      counter++;
    }
  }
  gKlingon = k;
}
