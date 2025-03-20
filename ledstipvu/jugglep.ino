void jugglep() {                                                                // Use the juggle routine, but adjust the timebase based on sampleavg for some randomness.

// Persistent local variables
  static uint8_t thishue=0;

  timeval = 40;                                                                 // Our EVERY_N_MILLIS_I timer value.

  leds[0] = ColorFromPalette(currentPalette, thishue++, sampleavg, LINEARBLEND);
  
  for (int i = N_PIXELS-1; i >0 ; i-- ) leds[i] = leds[i-1];

  addGlitter(sampleavg/2);                                                      // Add glitter based on sampleavg. By Andrew Tuline.
  
} // matrix()



 
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos, float opacity) {
  
  if(WheelPos < 85) {
    return strip.Color((WheelPos * 3) * opacity, (255 - WheelPos * 3) * opacity, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color((255 - WheelPos * 3) * opacity, 0, (WheelPos * 3) * opacity);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, (WheelPos * 3) * opacity, (255 - WheelPos * 3) * opacity);
  }
}
