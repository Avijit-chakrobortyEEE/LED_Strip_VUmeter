
    #include <Adafruit_NeoPixel.h>
    #include <FastLED.h>
    #include <math.h>
    #include <SoftwareSerial.h>
    #define N_PIXELS  30    // Number of pixels in strand
    #define N_PIXELS_HALF (N_PIXELS/2)
    #define MIC_PIN   A0  // Microphone is attached to this analog pin
    #define LED_PIN    3  // NeoPixel LED strand is connected to this pin
    #define SAMPLE_WINDOW   10  // Sample window for average level
    #define PEAK_HANG 24 //Time of pause before peak dot falls
    #define PEAK_FALL 20 //Rate of falling peak dot
    #define PEAK_FALL2 8 //Rate of falling peak dot
    #define INPUT_FLOOR 10 //Lower range of analogRead input
    #define INPUT_CEILING 300 //Max range of analogRead input, the lower the value the more sensitive (1023 = max)300 (150)
    #define DC_OFFSET  0  // DC offset in mic signal - if unusure, leave 0
    #define NOISE     195  // Noise/hum/interference in mic signal
    #define SAMPLES   60  // Length of buffer for dynamic level adjustment
    #define TOP       (N_PIXELS + 2) // Allow dot to go slightly off scale
    #define SPEED .20       // Amount to increment RGB color by each cycle
    #define TOP2      (N_PIXELS + 1) // Allow dot to go slightly off scale
    #define LAST_PIXEL_OFFSET N_PIXELS-1
    #define PEAK_FALL_MILLIS 10  // Rate of peak falling dot
    #define POT_PIN    4
    #define BG 0
    #define LAST_PIXEL_OFFSET N_PIXELS-1
    #if FASTLED_VERSION < 3001000
    #error "Requires FastLED 3.1 or later; check github for latest code."
    #endif
    #define BRIGHTNESS  255
    #define LED_TYPE    WS2812B     // Only use the LED_PIN for WS2812's
    #define COLOR_ORDER GRB
    #define COLOR_MIN           0
    #define COLOR_MAX         255
    #define DRAW_MAX          100
    #define SEGMENTS            4  // Number of segments to carve amplitude bar into
    #define COLOR_WAIT_CYCLES  10  // Loop cycles to wait between advancing pixel origin
    #define qsubd(x, b)  ((x>b)?b:0)     
    #define qsuba(x, b)  ((x>b)?x-b:0)                                              // Analog Unsigned subtraction macro. if result <0, then => 0. By Andrew Tuline.
    #define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
    
    
    struct CRGB leds[N_PIXELS];

    Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
 
    static uint16_t dist;         // A random number for noise generator.
    uint16_t scale = 30;          // Wouldn't recommend changing this on the fly, or the animation will be really blocky.
    uint8_t maxChanges = 48;      // Value for blending between palettes.
 
    CRGBPalette16 currentPalette(OceanColors_p);
    CRGBPalette16 targetPalette(CloudColors_p);


//new ripple vu
uint8_t timeval = 20;                                                           
uint16_t loops = 0;                                                            
bool     samplepeak = 0;                                                        
uint16_t oldsample = 0;                                                         
bool thisdir = 0;         
//new ripple vu

// Modes
enum 
{
} MODE;
bool reverse = true;
int BRIGHTNESS_MAX = 80;
int brightness = 20;


byte
//  peak      = 0,     
//  dotCount  = 0,     
  volCount  = 0;      
int
  reading,
  vol[SAMPLES],       
  lvl       = 10,      
  minLvlAvg = 0,      
  maxLvlAvg = 512;    
float
  greenOffset = 30,
  blueOffset = 150;
// cycle variables

int CYCLE_MIN_MILLIS = 2;
int CYCLE_MAX_MILLIS = 1000;
int cycleMillis = 20;
bool paused = false;
long lastTime = 0;
bool boring = true;
bool gReverseDirection = false;
int          myhue =   0;
//vu ripple
uint8_t colour; 
uint8_t myfade = 255;                                        
#define maxsteps 16                                           
int peakspersec = 0;
int peakcount = 0;
uint8_t bgcol = 0;   
int thisdelay = 20; 
uint8_t max_bright = 255;


  unsigned int sample;

//Samples
#define NSAMPLES 64
unsigned int samplearray[NSAMPLES];
unsigned long samplesum = 0;
unsigned int sampleavg = 0;
int samplecount = 0;
//unsigned int sample = 0;
unsigned long oldtime = 0;
unsigned long newtime = 0;

//Ripple variables
int color;
int center = 0;
int step = -1;
int maxSteps = 16;
float fadeRate = 0.80;
int diff;

//vu 8 variables
int
  origin = 0,
  color_wait_count = 0,
  scroll_color = COLOR_MIN,
  last_intensity = 0,
  intensity_max = 0,
  origin_at_flip = 0;
uint32_t
    draw[DRAW_MAX];
boolean
  growing = false,
  fall_from_left = true;



//background color
uint32_t currentBg = random(256);
uint32_t nextBg = currentBg;
TBlendType    currentBlending;  
     



    
    byte peak = 16;      // Peak level of column; used for falling dots
//    unsigned int sample;
     
    byte dotCount = 0;  //Frame counter for peak dot
    byte dotHangCount = 0; //Frame counter for holding peak dot
     
void setup() {
      
     //analogReference(EXTERNAL);
 
      // Serial.begin(9600);
      strip.begin();
      strip.show(); // all pixels to 'off'

      Serial.begin(57600);
      delay(3000);
 
  LEDS.addLeds<LED_TYPE,LED_PIN,COLOR_ORDER>(leds,N_PIXELS).setCorrection(TypicalLEDStrip); 
  LEDS.setBrightness(BRIGHTNESS);
  dist = random16(12345);          // A semi-random number for our noise generator

 }


float fscale( float originalMin, float originalMax, float newBegin, float newEnd, float inputValue, float curve){

  float OriginalRange = 0;
  float NewRange = 0;
  float zeroRefCurVal = 0;
  float normalizedCurVal = 0;
  float rangedValue = 0;
  boolean invFlag = 0;


  // condition curve parameter
  // limit range

  if (curve > 10) curve = 10;
  if (curve < -10) curve = -10;

  curve = (curve * -.1) ; // - invert and scale - this seems more intuitive - postive numbers give more weight to high end on output
  curve = pow(10, curve); // convert linear scale into lograthimic exponent for other pow function

  
  // Check for out of range inputValues
  if (inputValue < originalMin) {
    inputValue = originalMin;
  }
  if (inputValue > originalMax) {
    inputValue = originalMax;
  }

  // Zero Refference the values
  OriginalRange = originalMax - originalMin;

  if (newEnd > newBegin){
    NewRange = newEnd - newBegin;
  }
  else
  {
    NewRange = newBegin - newEnd;
    invFlag = 1;
  }

  zeroRefCurVal = inputValue - originalMin;
  normalizedCurVal  =  zeroRefCurVal / OriginalRange;   // normalize to 0 - 1 float

 
  // Check for originalMin > originalMax  - the math for all other cases i.e. negative numbers seems to work out fine
  if (originalMin > originalMax ) {
    return 0;
  }

  if (invFlag == 0){
    rangedValue =  (pow(normalizedCurVal, curve) * NewRange) + newBegin;

  }
  else     // invert the ranges
  { 
    rangedValue =  newBegin - (pow(normalizedCurVal, curve) * NewRange);
  }

  return rangedValue;
  
  }
    
  void loop() {
  
   //for mic
  uint8_t  i;
  uint16_t minLvl, maxLvl;
  int      n, height;
  while (1){
    void vu();
  }
  // end mic
 // read the pushbutton input pin:
 
}


         
















































  
// soundmems()
