// Passa alla schermata successiva e la disegna.
// rif: di quanto avanzare (di solito 1). 0 ridisegna senza cambiare.
void cambiaStatus(byte rif) {
  // 0-KEY  1-ACC  2-ITA  3-MAN  4-PEN  5-INF
  const char *labels = "KEYACCITAMANPENINF";
  statusMode = (statusMode + rif) % 6;
  arduboy.clear();

  if (statusMode != 5) {
    for (int i = 0; i < 3; i++) {
      arduboy.drawChar(110 + (6 * i), 0, labels[(statusMode * 3) + i], BLACK, WHITE, 1);
    }
    arduboy.drawFastHLine(0, 9, WIDTH, WHITE);
    tinyfont.setCursor(105, 5);
    tinyfont.print(mute ? "M" : " ");
  }
  else {
    arduboy.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
    arduboy.drawRect(2, 2, WIDTH - 4, HEIGHT - 4, WHITE);
  }

  if (statusMode == 0) printScalaMode1();
  else if (statusMode == 1) printAcc();
  else if (statusMode == 2) printScalaIta();
  else if (statusMode == 3) printScalaMode2(99, rootNote);
  else if (statusMode == 4) showPenta();
  else if (statusMode == 5) printInfo();
}

// Testata invertita: nome scala e tonica.
void drawTitle() {
  arduboy.fillRect(0, 0, 104, 8, WHITE);
  arduboy.setTextColor(BLACK);
  arduboy.setCursor(1, 0);
  printScaleNameAt(scaleIdx);
  arduboy.print(' ');
  arduboy.print(scoreb[rootNote]);
  arduboy.setTextColor(WHITE);
}

// Note alfabetiche della scala.
// idx: scala. y: riga in pixel. big: true font normale, false tinyfont.
void printNotesAt(uint8_t idx, uint8_t y, bool big) {
  uint8_t n = scaleLen(idx);
  uint8_t step = big ? 18 : ((n <= 8) ? 15 : 10);
  for (uint8_t i = 0; i < n; i++) {
    uint8_t ni = scaleNote(idx, i);
    if (big) {
      arduboy.setCursor(1 + i * step, y);
      arduboy.print(scoreb[ni]);
    }
    else {
      tinyfont.setCursor(1 + i * step, y);
      tinyfont.print(scoreb[ni]);
    }
  }
}

// Note sillabiche (Do Re Mi) della scala.
// idx: scala. y: riga in pixel.
void printSyllabicAt(uint8_t idx, uint8_t y) {
  uint8_t n = scaleLen(idx);
  if (n <= 7) {
    for (uint8_t i = 0; i < n; i++) {
      arduboy.setCursor(1 + i * 18, y);
      arduboy.print(scoreN[scaleNote(idx, i)]);
    }
  }
  else {
    uint8_t x = 1;
    for (uint8_t i = 0; i < n; i++) {
      String s = scoreN[scaleNote(idx, i)];
      uint8_t w = s.length() * 4 + 2;
      if (x + w > WIDTH) break;
      tinyfont.setCursor(x, y);
      tinyfont.print(s);
      x += w;
    }
  }
}

// Nome e note della scala successiva, font normale.
// idx: scala. y: riga del nome. Le note stanno 10 pixel sotto.
void printCompactScale(uint8_t idx, uint8_t y) {
  char buf[12];
  strncpy_P(buf, scaleNames[idx], 11);
  buf[11] = 0;
  uint8_t bar = strlen(buf) * 6 + 6 + scoreb[rootNote].length() * 6 + 2;
  if (bar > WIDTH) bar = WIDTH;
  arduboy.fillRect(0, y, bar, 8, WHITE);
  arduboy.setTextColor(BLACK);
  arduboy.setCursor(1, y);
  arduboy.print(buf);
  arduboy.print(' ');
  arduboy.print(scoreb[rootNote]);
  arduboy.setTextColor(WHITE);
  uint8_t n = scaleLen(idx);
  uint8_t x = 1;
  for (uint8_t i = 0; i < n; i++) {
    String s = scoreb[scaleNote(idx, i)];
    uint8_t w = s.length() * 6 + 2;
    if (x + w > WIDTH) break;
    arduboy.setCursor(x, y + 10);
    arduboy.print(s);
    x += w;
  }
}

// Note a font normale, con spazio fra una e l'altra se ci sta.
// idx: scala. y: riga. italian: Do Re Mi, altrimenti C Db.
// record: salva noteX/noteY per il play (solo la scala in evidenza).
void printSpacedNotes(uint8_t idx, uint8_t y, bool italian, bool record) {
  uint8_t n = scaleLen(idx);
  uint8_t w[12];
  uint16_t total = 0;
  if (record) {
    for (uint8_t i = 0; i < 12; i++) noteX[i] = 255;
  }
  for (uint8_t i = 0; i < n; i++) {
    uint8_t ni = scaleNote(idx, i);
    w[i] = (italian ? scoreN[ni].length() : scoreb[ni].length()) * 6;
    total += w[i];
  }
  uint8_t gap = 0;
  if (n > 1) {
    if (total + (uint16_t)(n - 1) * 3 <= WIDTH) gap = 3;
    else if (total + (uint16_t)(n - 1) * 2 <= WIDTH) gap = 2;
    else if (total + (uint16_t)(n - 1) <= WIDTH) gap = 1;
  }
  uint8_t x = 1;
  for (uint8_t i = 0; i < n; i++) {
    if ((uint16_t)x + w[i] > WIDTH) break;
    if (record) {
      noteX[i] = x;
      noteY[i] = y;
    }
    arduboy.setCursor(x, y);
    if (italian) arduboy.print(scoreN[scaleNote(idx, i)]);
    else arduboy.print(scoreb[scaleNote(idx, i)]);
    x += w[i] + gap;
  }
}

// Schermata ITA: scala in Do Re Mi e le due scale successive.
void printScalaIta() {
  drawTitle();
  arduboy.fillRect(0, 11, WIDTH, 53, BLACK);
  printSpacedNotes(scaleIdx, 12, true, true);
  arduboy.drawFastHLine(0, 22, WIDTH, WHITE);
  for (uint8_t k = 1; k <= 2; k++) {
    uint8_t idx = (scaleIdx + k) % NUM_SCALES;
    uint8_t y = (k == 1) ? 24 : 44;
    char buf[12];
    strncpy_P(buf, scaleNames[idx], 11);
    buf[11] = 0;
    arduboy.setCursor(1, y);
    arduboy.print(buf);
    printSpacedNotes(idx, y + 10, true, false);
  }
}

// Schermata KEY: note della scala e le due successive, font normale.
void printScalaMode1() {
  uint8_t n = scaleLen(scaleIdx);
  drawTitle();
  arduboy.fillRect(0, 11, WIDTH, 53, BLACK);
  printNotesAt(scaleIdx, 12, n <= 7);
  arduboy.drawFastHLine(0, 22, WIDTH, WHITE);
  printCompactScale((scaleIdx + 1) % NUM_SCALES, 24);
  printCompactScale((scaleIdx + 2) % NUM_SCALES, 44);
}

// Suona la scala di KEY o ITA ed evidenzia la nota corrente.
void playScala() {
  uint8_t n = scaleLen(scaleIdx);
  bool big = (n <= 7);
  uint8_t step = big ? 18 : ((n <= 8) ? 15 : 10);
  int durata = (n > 8) ? 420 : 800;
  int first = pgm_read_word(&allNotes[scaleNote(scaleIdx, 0)]);

  if (!mute) arduboy.audio.on();
  for (uint8_t i = 0; i < n; i++) {
    int nota = pgm_read_word(&allNotes[scaleNote(scaleIdx, i)]);
    if (nota < first) nota *= 2;
    sound.tone(nota, durata);
    if (statusMode == 2) {
      if (noteX[i] < WIDTH) {
        uint8_t pc = scaleNote(scaleIdx, i);
        arduboy.drawRect(noteX[i], noteY[i], scoreN[pc].length() * 6 + 1, 8, WHITE);
      }
    }
    else {
      arduboy.drawRect(i * step, 12, step - 1, 10, WHITE);
    }
    arduboy.display();
    while (sound.playing()) {}
    if (statusMode == 2) printScalaIta();
    else printScalaMode1();
    arduboy.display();
  }
  arduboy.audio.off();
}

// Schermata MAN: griglia cromatica con la tonica incorniciata.
// oldpos: nota prima, 0..11, oppure 99 per disegnare tutta la griglia.
// newpos: nota nuova, 0..11.
void printScalaMode2(byte oldpos, byte newpos) {
  arduboy.fillRect(0, 0, 104, 8, BLACK);
  arduboy.setCursor(1, 0);
  arduboy.print(F("Nota "));
  arduboy.print(scoreb[rootNote]);
  arduboy.print(F(" "));
  arduboy.print(scoreN[rootNote]);

  if (oldpos == 99) {
    for (uint8_t i = 0; i < 12; i++) {
      arduboy.setCursor(10 + (i % 6) * 20, 13 + (i / 6) * 10);
      arduboy.print(scoreb[i]);
    }
    arduboy.drawRect(7 + (rootNote % 6) * 20, 11 + (rootNote / 6) * 10, 20, 11, WHITE);
  }
  else {
    arduboy.drawRect(7 + (oldpos % 6) * 20, 11 + (oldpos / 6) * 10, 20, 11, BLACK);
    arduboy.drawRect(7 + (newpos % 6) * 20, 11 + (newpos / 6) * 10, 20, 11, WHITE);
  }
}

// Suona la singola nota scelta in MAN.
void playScalaMod2() {
  if (!mute) arduboy.audio.on();
  int nota = pgm_read_word(&allNotes[rootNote]);
  sound.tone(nota, 2000);
  arduboy.display();
  while (sound.playing()) {}
  arduboy.audio.off();
}

// Suona la scala sul pentagramma. A ogni nota cancella e ridisegna il rigo.
void playScalaMod3() {
  uint8_t n = scaleLen(scaleIdx);
  int durata = (n > 8) ? 380 : 700;
  int first = pgm_read_word(&allNotes[scaleNote(scaleIdx, 0)]);
  if (!mute) arduboy.audio.on();
  for (uint8_t i = 0; i < n; i++) {
    int nota = pgm_read_word(&allNotes[scaleNote(scaleIdx, i)]);
    if (nota < first) nota *= 2;
    sound.tone(nota, durata);
    showPenta();
    if (i < pentaN) arduboy.drawCircle(pnotes[i].x + 3, pnotes[i].y, 6, WHITE);
    arduboy.display();
    while (sound.playing()) {}
  }
  showPenta();
  arduboy.display();
  arduboy.audio.off();
}

// Schermata INF: nome, autore, anno.
void printInfo() {
  arduboy.setCursor(10, 8);
  arduboy.setTextSize(2);
  arduboy.print(F("ScaleShow"));
  arduboy.setTextSize(1);
  arduboy.setCursor(8, 28);
  arduboy.print(F("Max Scordamaglia"));
  arduboy.setCursor(8, 38);
  arduboy.print(F("maxscorda@gmail.com"));
  arduboy.setCursor(8, 50);
  arduboy.print(F("(c) 2026"));
}

// Quante note ha l'accordo, si ferma al 99.
// c: indice in accMod (0 e' vuoto).
uint8_t chordLen(uint8_t c) {
  uint8_t n = 0;
  while (n < 6 && pgm_read_byte(&accMod[c][n * 2]) != 99) n++;
  return n;
}

// Alterazione in semitoni della nota i.
// c: accordo. i: indice nota nell'accordo.
// 9 settima minore, 8 settima maggiore, 7 terza minore,
// 6 quinta diminuita, 4 settima diminuita. Vedi config.h.
int8_t chordAlt(uint8_t c, uint8_t i) {
  int8_t alt = (int8_t)pgm_read_byte(&accMod[c][i * 2 + 1]);
  uint8_t n = scaleLen(scaleIdx);
  uint8_t grado = pgm_read_byte(&accMod[c][i * 2]);
  int iv = (int)pgm_read_word(&scaleMod[scaleIdx][grado % n]);
  if (alt == 8 || alt == 9) {
    if (n < 7) return 0;
    uint8_t sev = pgm_read_word(&scaleMod[scaleIdx][6]);
    if (alt == 9) return (sev == 11) ? -1 : 0;
    return (sev == 10) ? 1 : 0;
  }
  if (alt == 7) return (iv == 4) ? -1 : 0;
  if (alt == 6) return (iv == 7) ? -1 : 0;
  if (alt == 4) {
    if (iv == 11) return -2;
    if (iv == 10) return -1;
    return 0;
  }
  return alt;
}

// Grado di scala della nota i (0 tonica, 2 terza, 4 quinta...).
// c: accordo. i: indice nota.
uint8_t chordGrado(uint8_t c, uint8_t i) {
  return pgm_read_byte(&accMod[c][i * 2]);
}

// Pitch class della nota d'accordo.
// grado: indice nella scala. alt: semitoni da sommare, puo' essere negativo.
uint8_t chordPc(uint8_t grado, int8_t alt) {
  uint8_t n = scaleLen(scaleIdx);
  uint8_t idx = grado % n;
  int semis = (int)pgm_read_word(&scaleMod[scaleIdx][idx]) + alt;
  int pc = ((int)rootNote + semis) % 12;
  if (pc < 0) pc += 12;
  return pc;
}

// Distanza in semitoni dalla tonica, ottave comprese. Serve al play.
// grado: indice nella scala. alt: semitoni da sommare.
int chordSemis(uint8_t grado, int8_t alt) {
  uint8_t n = scaleLen(scaleIdx);
  return (int)pgm_read_word(&scaleMod[scaleIdx][grado % n]) + alt + (grado / n) * 12;
}

// Schermata ACC: titolo e note della scala, poi nome e note dell'accordo.
void printAcc() {
  char buf[12];
  drawTitle();
  arduboy.fillRect(0, 11, WIDTH, 53, BLACK);

  printSpacedNotes(scaleIdx, 12, false, false);
  arduboy.drawFastHLine(0, 22, WIDTH, WHITE);

  arduboy.setCursor(1, 26);
  if (chordIdx < NUM_CHORDS) {
    strncpy_P(buf, chordNames[chordIdx], 11);
    buf[11] = 0;
    arduboy.print(buf);
  }

  uint8_t n = chordLen(chordIdx);
  for (uint8_t i = 0; i < n; i++) {
    uint8_t pc = chordPc(chordGrado(chordIdx, i), chordAlt(chordIdx, i));
    arduboy.setCursor(1 + i * 18, 40);
    arduboy.print(scoreb[pc]);
  }
}

// Suona le note dell'accordo corrente.
void playAcc() {
  uint8_t n = chordLen(chordIdx);
  if (n == 0) return;
  int first = chordSemis(chordGrado(chordIdx, 0), chordAlt(chordIdx, 0));
  if (!mute) arduboy.audio.on();
  for (uint8_t i = 0; i < n; i++) {
    uint8_t g = chordGrado(chordIdx, i);
    int8_t alt = chordAlt(chordIdx, i);
    int semis = chordSemis(g, alt);
    int nota = pgm_read_word(&allNotes[chordPc(g, alt)]);
    while (semis - first >= 12) {
      nota *= 2;
      semis -= 12;
    }
    sound.tone(nota, 700);
    arduboy.drawRect(i * 18, 38, 17, 12, WHITE);
    arduboy.display();
    while (sound.playing()) {}
    arduboy.drawRect(i * 18, 38, 17, 12, BLACK);
    arduboy.display();
  }
  arduboy.audio.off();
}
