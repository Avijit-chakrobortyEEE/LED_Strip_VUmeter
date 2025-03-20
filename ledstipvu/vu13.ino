void vu13() {                                                                   // The >>>>>>>>>> L-O-O-P <<<<<<<<<<<<<<<<<<<<<<<<<<<<  is buried here!!!11!1!

 
  EVERY_N_MILLISECONDS(1000) {
    peakspersec = peakcount;                                  // Count the peaks per second. This value will become the foreground hue.
    peakcount = 0;                                            // Reset the counter every second.
  }

  soundripper();

  EVERY_N_MILLISECONDS(20) {
  jugglep();
  }

   FastLED.show();

} // loop()
