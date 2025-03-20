//Used to draw a line between two points of a given color
    void drawLine(uint8_t from, uint8_t to, uint32_t c) {
      uint8_t fromTemp;
      if (from > to) {
        fromTemp = from;
        from = to;
        to = fromTemp;
      }
      for(int i=from; i<=to; i++){
        strip.setPixelColor(i, c);
      }
    }
