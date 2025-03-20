void sndwave() {
  
  leds[N_PIXELS/2] = ColorFromPalette(currentPalette, sample, sample*2, currentBlending); // Put the sample into the center
  
  for (int i = N_PIXELS - 1; i > N_PIXELS/2; i--) {       //move to the left      // Copy to the left, and let the fade do the rest.
    leds[i] = leds[i - 1];
  }

  for (int i = 0; i < N_PIXELS/2; i++) {                  // move to the right    // Copy to the right, and let the fade to the rest.
    leds[i] = leds[i + 1];
  }
  addGlitter(sampleavg);
}
