void vu1() 
    {
      unsigned long startMillis= millis();  // Start of sample window
      float peakToPeak = 0;   // peak-to-peak level
     
      unsigned int signalMax = 0;
      unsigned int signalMin = 1023;
      unsigned int c, y;
      
      while (millis() - startMillis < SAMPLE_WINDOW)
      {
        sample = analogRead(MIC_PIN);
        if (sample < 1024)  
        {
          if (sample > signalMax)
          {
            signalMax = sample;  
          }
          else if (sample < signalMin)
          {
            signalMin = sample;  
          }
        }
      }
      peakToPeak = signalMax - signalMin;  
     
      // Serial.println(peakToPeak);
     
     
      
      for (int i=0;i<=N_PIXELS_HALF-1;i++){
        uint32_t color = Wheel(map(i,0,N_PIXELS_HALF-1,30,150));
        strip.setPixelColor(N_PIXELS-i,color);
        strip.setPixelColor(0+i,color);
      }

      
      c = fscale(INPUT_FLOOR, INPUT_CEILING, N_PIXELS_HALF, 0, peakToPeak, 2);
     
      if(c < peak) {
        peak = c;        // Keep dot on top
        dotHangCount = 0;    // make the dot hang before falling
      }
      if (c <= strip.numPixels()) { // Fill partial column with off pixels
        drawLine(N_PIXELS_HALF, N_PIXELS_HALF-c, strip.Color(0, 0, 0));
        drawLine(N_PIXELS_HALF, N_PIXELS_HALF+c, strip.Color(0, 0, 0));
      }
     
      


      y = N_PIXELS_HALF - peak;
      uint32_t color1 = Wheel(map(y,0,N_PIXELS_HALF-1,30,150));
      strip.setPixelColor(y-1,color1);
      //strip.setPixelColor(y-1,Wheel(map(y,0,N_PIXELS_HALF-1,30,150)));

      y = N_PIXELS_HALF + peak;
      strip.setPixelColor(y,color1);
      //strip.setPixelColor(y+1,Wheel(map(y,0,N_PIXELS_HALF+1,30,150)));
     
      strip.show();
     
      // Frame based peak dot animation
      if(dotHangCount > PEAK_HANG) { //Peak pause length
        if(++dotCount >= PEAK_FALL2) { //Fall rate 
          peak++;
          dotCount = 0;
        }
      } 
      else {
        dotHangCount++; 
      }
    }
