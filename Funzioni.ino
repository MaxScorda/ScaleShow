// Prima schermata: frame rate e disegna il modo corrente.
void initDisplay() {
  arduboy.setFrameRate(30);
  cambiaStatus(0);
  arduboy.display();
}

// Legge i tasti. A breve cambia schermata, A tenuto 3s mute, B play.
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

    if (statusMode != 5) {
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
        if (statusMode == 1) {
          chordIdx = (chordIdx <= 1) ? (NUM_CHORDS - 1) : (chordIdx - 1);
          printAcc();
        }
        else {
          scaleIdx = (scaleIdx + NUM_SCALES - 1) % NUM_SCALES;
          onScaleChanged();
        }
      }
      if (butpres == DOWN_BUTTON) {
        if (statusMode == 1) {
          chordIdx = (chordIdx + 1) % NUM_CHORDS;
          if (chordIdx == 0) chordIdx = 1;
          printAcc();
        }
        else {
          scaleIdx = (scaleIdx + 1) % NUM_SCALES;
          onScaleChanged();
        }
      }
    }

    if (butpres == B_BUTTON) {
      if (statusMode == 0 || statusMode == 2) playScala();
      else if (statusMode == 1) playAcc();
      else if (statusMode == 3) playScalaMod2();
      else if (statusMode == 4) playScalaMod3();
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

// Ridisegna dopo un cambio di tonica.
// oldNote: tonica precedente, 0..11, serve solo a MAN per spostare il riquadro.
void onRootChanged(uint8_t oldNote) {
  if (statusMode == 0) printScalaMode1();
  else if (statusMode == 1) printAcc();
  else if (statusMode == 2) printScalaIta();
  else if (statusMode == 3) printScalaMode2(oldNote, rootNote);
  else if (statusMode == 4) showPenta();
}

// Ridisegna dopo un cambio di scala (non in ACC: li' su/giu cambiano l'accordo).
void onScaleChanged() {
  if (statusMode == 0) printScalaMode1();
  else if (statusMode == 2) printScalaIta();
  else if (statusMode == 4) showPenta();
}

// Quante note ha la scala, si ferma al 99.
// idx: indice in scaleMod.
uint8_t scaleLen(uint8_t idx) {
  uint8_t n = 0;
  while (n < 13 && pgm_read_word(&scaleMod[idx][n]) != 99) n++;
  return n;
}

// Pitch class della nota di grado deg.
// idx: indice scala. deg: 0 = tonica.
uint8_t scaleNote(uint8_t idx, uint8_t deg) {
  return (rootNote + pgm_read_word(&scaleMod[idx][deg])) % 12;
}

// Stampa il nome flash della scala.
// idx: indice in scaleNames.
void printScaleNameAt(uint8_t idx) {
  char buf[12];
  strncpy_P(buf, scaleNames[idx], 11);
  buf[11] = 0;
  arduboy.print(buf);
}
