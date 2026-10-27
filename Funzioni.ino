void initDisplay() {
  arduboy.setFrameRate(30);
  cambiaStatus(0);
  arduboy.display();
}

void LeggiPulsanti() {
  int static lastpressed = 0;
  boolean static cambio;
  int butpres = arduboy.buttonsState();

  if ((butpres == lastpressed) && (butpres == A_BUTTON)) {
    if (millis() - specialcount >= 3000) {
      mute = !mute;
      tinyfont.setCursor(105, 5);
      if (mute) tinyfont.print("M");
      else arduboy.fillRect(105, 5, 4, 4, BLACK);
      arduboy.display();
      cambio = true;
      specialcount = millis();
    }
  }

  if (arduboy.justReleased(A_BUTTON)) {
    if ((millis() - specialcount < 3000) && (cambio == false)) {
      cambiaStatus(1);
      lastpressed = butpres;
      arduboy.display();
    }
  }

  if ((butpres != lastpressed) && (butpres != 0)) {
    statusInvert = false;
    arduboy.invert(statusInvert);

    if (statusMode != 4) {
      if (butpres == RIGHT_BUTTON) {
        uint8_t old = rootNote;
        rootNote = (rootNote + 1) % 12;
        onRootChanged(old);
      }
      if (butpres == LEFT_BUTTON) {
        uint8_t old = rootNote;
        rootNote = (rootNote + 11) % 12;
        onRootChanged(old);
      }
      if (butpres == UP_BUTTON) {
        scaleIdx = (scaleIdx + NUM_SCALES - 1) % NUM_SCALES;
        onScaleChanged();
      }
      if (butpres == DOWN_BUTTON) {
        scaleIdx = (scaleIdx + 1) % NUM_SCALES;
        onScaleChanged();
      }
    }

    if (butpres == B_BUTTON) {
      if (statusMode == 0 || statusMode == 1) playScala();
      else if (statusMode == 2) playScalaMod2();
      else if (statusMode == 3) playScalaMod3();
    }

    if (butpres == A_BUTTON) {
      specialcount = millis();
      cambio = false;
    }

    lastpressed = butpres;
    blinktime = millis();
    arduboy.display();
  }
  else if (arduboy.buttonsState() == 0) {
    lastpressed = 0;
  }
}

void onRootChanged(uint8_t oldNote) {
  if (statusMode == 0) printScalaMode0();
  else if (statusMode == 1) printScalaMode1();
  else if (statusMode == 2) printScalaMode2(oldNote, rootNote);
  else if (statusMode == 3) showPenta();
}

void onScaleChanged() {
  if (statusMode == 0) printScalaMode0();
  else if (statusMode == 1) printScalaMode1();
  else if (statusMode == 3) showPenta();
}

uint8_t scaleLen(uint8_t idx) {
  uint8_t n = 0;
  while (n < 13 && pgm_read_word(&scaleMod[idx][n]) != 99) n++;
  return n;
}

uint8_t scaleNote(uint8_t idx, uint8_t deg) {
  return (rootNote + pgm_read_word(&scaleMod[idx][deg])) % 12;
}

void printScaleNameAt(uint8_t idx) {
  char buf[12];
  strncpy_P(buf, scaleNames[idx], 11);
  buf[11] = 0;
  arduboy.print(buf);
}
