void addGlitter( fract8 chanceOfGlitter) {                                      // Let's add some glitter, thanks to Mark
  
  if( random8() < chanceOfGlitter) {
    leds[random16(N_PIXELS)] += CRGB::White;
  }

} // addGlitter()
// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList qPatterns = {vu, vu1, vu2, Vu3, Vu4, Vu5, Vu6, vu7,  vu9, vu10, vu11, vu12, vu13};
uint8_t qCurrentPatternNumber = 0; // Index number of which pattern is current
