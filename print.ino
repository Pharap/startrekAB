void prints(int x, int y, char *message, bool inv) {
  font3x5.setCursor( x*4+1, y*7 );
  if(inv == 0){
    font3x5.setTextColor(WHITE);
    font3x5.print( message );
  } else {
    arduboy.fillRect( x*4, y*7, strlen(message)*4+1, 7,WHITE);
    font3x5.setTextColor(BLACK);
    font3x5.print( message );
  }
}
/*
void printd(int x, int y, int number, bool inv) {
  char buf[3];
  sprintf(buf,"%03d",number);
  font3x5.setCursor( x*4+1, y*7 );
  if(inv == 0){
    font3x5.setTextColor(WHITE);
    font3x5.print( buf );
  } else {
    arduboy.fillRect( x*4, y*7, strlen(buf)*4+1, 7,WHITE);
    font3x5.setTextColor(BLACK);
    font3x5.print( buf );
  }
}
*/
