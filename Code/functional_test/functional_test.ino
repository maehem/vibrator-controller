// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define N_PINGS_1 30
#define N_PINGS_2 15
#define N_PINGS_3 5


// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    12

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 30

#define LED_ENABLE 4

#define MOT_1  A0
#define MOT_2  A1

#define MOT_MAX 80

int ch1Value = 0;
int ch2Value = 0;
int modeValue = 0;

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------

void setup() {
  // Power to LEDs must be enabled
  pinMode(LED_ENABLE, OUTPUT);
  digitalWrite(LED_ENABLE, HIGH);

  pinMode(MOT_1, OUTPUT);
  analogWrite(MOT_1, 0);
  pinMode(MOT_2, OUTPUT);
  analogWrite(MOT_2, 0);

  initChannels();

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(5); // Set BRIGHTNESS to about 1/5 (max = 255)
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  updateChannelState();
  updateBars(
    strip.Color(120, 0, 0), ch1Value,
    strip.Color(0, 200, 0), ch2Value,
    strip.Color(0, 0, 255), modeValue
  );
  updateMotors();
  delay(20);
}

void updateBars(
  uint32_t color1, int value1,
  uint32_t color2, int value2,
  uint32_t color3, int value3
) {
  int i = 0;
  for (; i <= value1; i++) {
    strip.setPixelColor(i, color1);
  }
  // Finish the strip with blanks.
  for (; i < 10; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0) );
  }
  for (; i <= 10 + value2; i++) {
    strip.setPixelColor(i, color2);
  }
  // Finish the strip with blanks.
  for (; i < 20; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0) );
  }

  // This will be different to show which mode.
  // Fill blank up to value
  for (; i <= 20 + value3 - 1; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.setPixelColor(i, color3);
  i++;

  // Finish the strip with blanks.
  for (; i < 30; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0) );
  }

  strip.show();                          //  Update strip to match
  delay(20);
}

void updateMotors() {
  switch ( modeValue ) {
    case 0: setVibes(ch1Value, ch2Value); break; // Individual vibe channels
    case 1: pingPong(N_PINGS_1, ch1Value, ch2Value); break;  // Alternating left-right vibes slow
    case 2: pingPong(N_PINGS_2, ch1Value, ch2Value); break;  // Alternating left-right vibes med
    case 3: pingPong(N_PINGS_3, ch1Value, ch2Value); break;  // Alternating left-right vibes fast
    default: motorsOff(); break;
  }
}


void motorsOff() {
  analogWrite(MOT_2, 0);
  analogWrite(MOT_1, 0);
}

void blankLEDs() {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, strip.Color(0, 0, 0));       //  Set pixel's color (in RAM)
  }
  strip.show();                          //  Update strip to match
}
