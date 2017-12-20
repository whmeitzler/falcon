#include <Arduino.h>
#include "FastLED.h"


#define NUM_LEDS 120
#define DATA_PIN 11
#define BRIGHTNESS          1000
#define BLUE  0xA9B8DD
#define PULSE_PERIOD 2000

#define ANIM_FADE(t) (32 * (0.5 + sin(t)))
#define RIPPLE_FADE(p) (-32*(0.5+cos(p)))
// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];


void addColor(int i, double r, double g, double b){
  r = leds[i].r + r;
  if(r > 0xFF){r = 0xFF;} else if(r < 0){r = 0;}
  leds[i].r = (int)r;
  
  g = leds[i].g + g;
  if(g > 0xFF){g = 0xFF;} else if(g < 0){g = 0;}
  leds[i].g = (int)g;
  
  b = leds[i].b + b;
  if(b > 0xFF){b = 0xFF;} else if(b < 0){b = 0;}
  leds[i].b = (int)b;
}
void animateEngines(){
  double t = 2 * PI * millis()/PULSE_PERIOD;
  //All are a nice cool blue
  for(int i = 0; i < NUM_LEDS;i++){
    leds[i] = BLUE;
  }
  //Add the pulse
  for(int x = 0; x < 30; x++){
    double p = (2*PI/17*x)*t - (2*PI/16*x);
    addColor(30+x,
      ANIM_FADE(t), ANIM_FADE(t), ANIM_FADE(t)
    );
    addColor(30+x,
      RIPPLE_FADE(p), RIPPLE_FADE(p),RIPPLE_FADE(p)
    );
    addColor(30-x,
      ANIM_FADE(t),ANIM_FADE(t), ANIM_FADE(t)
    );
    addColor(30-x,
      RIPPLE_FADE(p), RIPPLE_FADE(p),RIPPLE_FADE(p)
    );
    addColor(90+x,
      ANIM_FADE(t), ANIM_FADE(t), ANIM_FADE(t)
    );
    addColor(90+x,
      RIPPLE_FADE(p), RIPPLE_FADE(p),RIPPLE_FADE(p)
    );
    addColor(90-x,
      RIPPLE_FADE(p), RIPPLE_FADE(p),RIPPLE_FADE(p)
    );
    addColor(90-x,
      ANIM_FADE(t), ANIM_FADE(t), ANIM_FADE(t)
    );
    
  }
  //Add a wave
  
}

// This function sets up the ledsand tells the controller about them
void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,750); 
  FastLED.setBrightness(BRIGHTNESS);
  for(int i = 0; i < NUM_LEDS; i+=3){
    leds[i] = 0xFF0000;
    leds[i+1] = 0x00FF00;
    leds[i+2] = 0x0000FF;
  }
}

// This function runs over and over, and is where you do the magic to light
// your leds.
byte tick = 0;

void loop() {
  
  animateEngines();
  
  FastLED.show();
}
