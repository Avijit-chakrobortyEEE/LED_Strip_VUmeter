void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
     // if (digitalRead(buttonPin) != lastButtonState)  // <------------- add this
       return;         // <------------ and this
      delay(wait);
}}
