#include <Arduino.h>
#include <FastLED.h>
#include <WiFi.h>
#include <HTTPClient.h>
//***************************************************************************************************************************************************
//Wifi
const char* ssid = "ZIM3/5+";
const char* password = "Juventus1234.";
WiFiServer server(80);
WiFiClient client;



//LED
#define NUM_LEDS 54 
CRGB leds[NUM_LEDS];
#define PIN 18
#define BRT 100 //Jasnosc 
#define FRAMES_PER_SECOND  100
typedef void (*SimplePatternList[])();


uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  



//***************************************************************************************************************************************************
//                                                     Funkcje pomocnicze 
//***************************************************************************************************************************************************
void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}
byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}
//***************************************************************************************************************************************************
//                                                                efekty
//***************************************************************************************************************************************************
//Tęcza 

void rainbowCycle() {
  int SpeedDelay = 20;
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

//***************************************************************************************************************************************************
//  Theater Chase 

void theaterChaseRainbow() {
  int SpeedDelay = 20;
  byte *c;
  
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < NUM_LEDS; i=i+3) {
          c = Wheel( (i+j) % 255);
          setPixel(i+q, *c, *(c+1), *(c+2));    //turn every third pixel on
        }
        showStrip();
       
        delay(SpeedDelay);
       
        for (int i=0; i < NUM_LEDS; i=i+3) {
          setPixel(i+q, 0,0,0);        //turn every third pixel off
        }
    }
  }
}

//***************************************************************************************************************************************************
//  Ogień  
void setPixelHeatColor (int Pixel, byte temperature) {
    // Scale 'heat' down from 0-255 to 0-191
    byte t192 = round((temperature/255.0)*191);
  
    // calculate ramp up from
    byte heatramp = t192 & 0x3F; // 0..63
    heatramp <<= 2; // scale up to 0..252
  
    // figure out which third of the spectrum we're in:
    if( t192 > 0x80) {                     // hottest
      setPixel(Pixel, 255, 255, heatramp);
    } else if( t192 > 0x40 ) {             // middle
      setPixel(Pixel, 255, heatramp, 0);
    } else {                               // coolest
      setPixel(Pixel, heatramp, 0, 0);
    }
  }
void Fire() {
  int Cooling = 15;
  int Sparking = 120;
  int SpeedDelay = 15;
  static byte heat[NUM_LEDS];
  int cooldown;
  
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);
    
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
  
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
    
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }
  
  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  showStrip();
  delay(SpeedDelay);
}
//***************************************************************************************************************************************************
//  Meteor
void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
    
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
    
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}
void meteorRain() { 
  byte red = 0x6D; byte green=0x00; byte blue=0xC1; 
  byte meteorSize=10; byte meteorTrailDecay=64;
  boolean meteorRandomDecay=true; int SpeedDelay=30;
  setAll(0,0,0);
  
  for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<NUM_LEDS; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      } 
    }
   
    showStrip();
    delay(SpeedDelay);
  }
}
//***************************************************************************************************************************************************
//  RGBLoop
void RGBLoop(){
  for(int j = 0; j < 3; j++ ) { 
    // Fade IN
    for(int k = 0; k < 256; k++) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
    // Fade OUT
    for(int k = 255; k >= 0; k--) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
  }
}
//***************************************************************************************************************************************************
//  Z Demo wheel
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}
void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}
void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}



void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}





SimplePatternList gPatterns = {rainbowCycle, theaterChaseRainbow, meteorRain, Fire, rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm, RGBLoop};
String myresultat;
String ClientRequest;
int task;
String ReadIncomingRequest(){
while(client.available()) {
    ClientRequest = (client.readStringUntil('\r'));
    if ((ClientRequest.indexOf("HTTP/1.1")>0)&&(ClientRequest.indexOf("/favicon.ico")<0)){
      myresultat = ClientRequest;
    }
}
return myresultat;
}


//***************************************************************************************************************************************************
//                                              Glowny program 
//***************************************************************************************************************************************************
void setup() {
Serial.begin(9600);
WiFi.disconnect();
delay(3000);
Serial.println("START");
WiFi.begin(ssid,password);
while ((!(WiFi.status() == WL_CONNECTED))){
  delay(300);
  Serial.print("..");
}
Serial.println("Connected");
Serial.println("WiFi connected.");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
server.begin();

//LED
FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
FastLED.setBrightness(BRT);
}
 
void loop() {
    client = server.available();
    if (client.available() > 0) {
      ClientRequest = ReadIncomingRequest();
      ClientRequest.remove(0, 5);
      ClientRequest.remove(ClientRequest.length()-9,9);
      if (ClientRequest == "rainbowCycle")          { task = 0;}
      if (ClientRequest == "theaterChaseRainbow")   { task = 1;}
      if (ClientRequest == "meteorRain")            { task = 2;}
      if (ClientRequest == "fire")                  { task = 3;}
      if (ClientRequest == "rainbow")               { task = 4;}
      if (ClientRequest == "rainbowWithGlitter")    { task = 5;}
      if (ClientRequest == "confetti")              { task = 6;}
      if (ClientRequest == "sinelon")               { task = 7;}
      if (ClientRequest == "juggle")                { task = 8;}
      if (ClientRequest == "bpm")                   { task = 9;}
      if (ClientRequest == "RGBLoop")               { task = 10;}
    }
    gPatterns[task]();
    FastLED.show();  
    
    EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow

}