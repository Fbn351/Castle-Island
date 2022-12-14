#include <FastLED.h>

#define LED_PIN 3
#define NUM_LEDS 14
#define LED_MAGICAN_PIN 5
#define NUM_MAGICAN_LEDS 5

class Torch {
  int ticks_left = 0;
  int max_ticks_per_cycle = 0;
  CRGB* led;
  float transition_vector[3];

 public:
  Torch() {};
  
  void init(int max_ticks, CRGB* led_ptr) {
      led = led_ptr;
      max_ticks_per_cycle = max_ticks;
      led->r = 120;
      led->g = 50;
    }

  void tick() {
    if (ticks_left <= 0) {
      ticks_left = random(10, max_ticks_per_cycle);
      compute_new_transition_vector(ticks_left);
      
    }
    apply_transition_vector();
    ticks_left--;
  }
  
 void apply_transition_vector() {
  (led->r + transition_vector[0] > 255) ? led->r = 255 : (led->r + transition_vector[0] < 0) ? led->r = 0 : led->r += transition_vector[0];
  (led->g + transition_vector[1] > 255) ? led->g = 255 : (led->g + transition_vector[1] < 0) ? led->g = 0 : led->g += transition_vector[1];
 }
 
 void compute_new_transition_vector(int steps) {
  float r;
  float brightness = (float)random(25, 100) / 100.0;
  float g = 50 * brightness;
  r = 205 * brightness;
  transition_vector[0] = (r - led->r) / ticks_left;
  transition_vector[1] = (g - led->g) / ticks_left;
  transition_vector[2] = 0;
 }
 
};

class Magic_Spell {
  int ticks_left = 0;
  int max_ticks_per_cycle = 0;
  CRGB* led;
  float transition_vector[3];

 public:
  Magic_Spell() {};
  
 //Initalisierung des Strips und anzeigen der LED´s in der Farbe beim Start
  void init(int max_ticks, CRGB* led_ptr) {
      led = led_ptr;
      max_ticks_per_cycle = max_ticks;
      led->r = 0;
      led->g = 120;
      led->b = 50;
    }

  void tick() {
    if (ticks_left <= 0) {
      ticks_left = random(20, max_ticks_per_cycle);
      compute_new_transition_vector(ticks_left);
      
    }
    apply_transition_vector();
    ticks_left--;
  }
  
 void apply_transition_vector() {
  (led->r + transition_vector[0] > 255) ? led->r = 255 : (led->r + transition_vector[0] < 0) ? led->r = 0 : led->r += transition_vector[0];
  (led->g + transition_vector[1] > 255) ? led->g = 255 : (led->g + transition_vector[1] < 0) ? led->g = 0 : led->g += transition_vector[1];
  (led->b + transition_vector[2] > 255) ? led->b = 255 : (led->b + transition_vector[2] < 0) ? led->b = 0 : led->b += transition_vector[2];
 }
 
 void compute_new_transition_vector(int steps) {
  float r;
  float brightness = (float)random(25, 100) / 100.0;
  float g = 200 * brightness;
  float b = 40 * brightness;
  //r = 205 * brightness;
  transition_vector[0] = (r - led->r) / ticks_left;
  transition_vector[1] = (g - led->g) / ticks_left;
  transition_vector[2] = (b - led->b) / ticks_left;
 }
 
};

CRGB leds[NUM_LEDS];
Torch torches[NUM_LEDS];

CRGB MAGIC_leds[NUM_MAGICAN_LEDS];
Magic_Spell spells[NUM_MAGICAN_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
      torches[i].init(15, &leds[i]);
  }
  FastLED.addLeds<NEOPIXEL, LED_MAGICAN_PIN>(MAGIC_leds, NUM_MAGICAN_LEDS);
  for (int i = 0; i < NUM_MAGICAN_LEDS; i++) {
      spells[i].init(15, &MAGIC_leds[i]);
  }
  Serial.begin(9600);
  FastLED.show();
  delay(2000);
}

int randomflash = 0;
void loop() {
    for (int i = 0; i < NUM_LEDS; i++) {
      torches[i].tick();
    }
    for (int i = 0; i < NUM_MAGICAN_LEDS; i++) {
      spells[i].tick();
    }
randomflash = random(100);
if(randomflash > 98){
Serial.println("FLASH");
    for (int i = 0; i < NUM_MAGICAN_LEDS; i++) {
      MAGIC_leds[i]= CRGB( 255, 0, 0);
    }
};
    FastLED.show();
    delay(20);
}
