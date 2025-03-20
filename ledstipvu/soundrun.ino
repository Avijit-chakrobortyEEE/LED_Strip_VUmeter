
void soundtun() {

  int n;
  n = analogRead(MIC_PIN);                                    // Raw reading from mic
  n = qsuba(abs(n-512), 10);                                  // Center on zero and get rid of low level noise
  CRGB newcolour = ColorFromPalette(currentPalette, constrain(n,0,255), constrain(n,0,255), currentBlending);
  nblend(leds[0], newcolour, 128);
  
  for (int i = N_PIXELS-1; i>0; i--) {
    leds[i] = leds[i-1];
  }
  
} // soundmems()
