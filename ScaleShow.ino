#include <Arduboy2.h>
#include <ArduboyTones.h>
#include <Tinyfont.h>
#include "config.h"

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());

uint8_t rootNote = 0;   // 0..11  C .. B
uint8_t scaleIdx = 0;   // indice in scaleMod

struct PNote {
  uint8_t x, y, st, flat;
};
PNote pnotes[12];
uint8_t pentaN = 0;

long blinktime;
long specialcount;
boolean statusInvert = false;
byte statusMode = 1;
boolean mute = false;

void setup() {
  arduboy.boot();
  Serial.begin(9600);
  initDisplay();
  sound.volumeMode(VOLUME_ALWAYS_HIGH);
  blinktime = millis();
}

void loop() {
  arduboy.pollButtons();
  LeggiPulsanti();
  if (millis() - blinktime > 10000) {
    statusInvert = !statusInvert;
    arduboy.invert(statusInvert);
    blinktime = millis();
  }
}
