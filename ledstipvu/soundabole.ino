void soundble() {                                            // Quick and dirty sampling of the microphone.
  
  int tmp = analogRead(MIC_PIN) - 512 - DC_OFFSET;
  sample = abs(tmp);
  
}  // soundmems()
