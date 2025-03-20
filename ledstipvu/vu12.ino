void vu12() {

  EVERY_N_MILLISECONDS(1000) {
    peakspersec = peakcount;                                  // Count the peaks per second. This value will become the foreground hue.
    peakcount = 0;                                            // Reset the counter every second.
  }

  soundripped();

  EVERY_N_MILLISECONDS(20) {
  rippvu();
  }

   FastLED.show();

} // loop()
