

void setVibes(int val1, int val2) {
  int mot1Val = val1 * MOT_MAX/10;
  if (val1 == 1) { // Kick the motor
    analogWrite(MOT_1, mot1Val + 80);
    delay(2);
  }
  analogWrite(MOT_1, mot1Val);

  int mot2Val = val2 * MOT_MAX/10;
  if (val2 == 1) { // Kick the motor
    analogWrite(MOT_2, mot2Val + 80);
    delay(2);
  }
  analogWrite(MOT_2, mot2Val);
}


long periodCount = 0;
int pp = 0;
void pingPong( long nPings, int val1, int val2) {
  if ( periodCount > 0 ) {
    periodCount--;
    return;
  } else {
    pp = 1 - pp; // Toggle pp
    periodCount = nPings;
  }
  if ( pp < 1 ) { // ping
    setVibes(val1, 0);
  } else {        // pong
    setVibes(0, val2);
  }
}

void pendulum( long period, int val1, int val2 ) {
  if ( periodCount > 0 ) {
    periodCount--;
  } else {
    pp = 1 - pp; // Toggle pp
    periodCount = period;
  }
  double valChange1 = val1/(double)period;
  double valChange2 = val2/(double)period;
  if ( pp < 1 ) { // ping
    setVibes(periodCount*valChange1, val2-periodCount*valChange2);
  } else {        // pong
    setVibes(val1-periodCount*valChange1, periodCount*valChange2);
  }
}

void triangle( long period, int val1, int val2 ) {
  if ( periodCount > 0 ) {
    periodCount--;
  } else {
    pp = 1 - pp; // Toggle pp
    periodCount = period;
  }
  double valChange1 = val1/(double)period;
  double valChange2 = val2/(double)period;
  if ( pp < 1 ) { // attack
    setVibes(periodCount*valChange1, periodCount*valChange2);
  } else {        // release
    setVibes(val1-periodCount*valChange1, val2-periodCount*valChange2);
  }
}

void saw( long period, int val1, int val2 ) {
  if ( periodCount > 0 ) {
    periodCount--;
  } else {
    //pp = 1 - pp; // Toggle pp
    periodCount = period;
  }
  double valChange1 = val1/(double)period;
  double valChange2 = val2/(double)period;
  setVibes(periodCount*valChange1, periodCount*valChange2);
}
