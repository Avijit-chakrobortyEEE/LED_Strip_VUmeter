void All2()
{
  // Call the current pattern function once, updating the 'leds' array
//  qPatterns[qCurrentPatternNumber]();
  EVERY_N_SECONDS( 30 ) { nextPattern2(); } // change patterns periodically
}
