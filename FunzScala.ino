void cambiaStatus(byte rif) {
  // 0-AeN  1-KEY  2-MAN  3-PEN  4-INF
  char *labels = "AeNKEYMANPENINF";
  statusMode = (statusMode + rif) % 5;
  arduboy.clear();

  if (statusMode != 4) {
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

  if (statusMode == 0) printScalaMode0();
  else if (statusMode == 1) printScalaMode1();
  else if (statusMode == 2) printScalaMode2(99, rootNote);
  else if (statusMode == 3) showPenta();
  else if (statusMode == 4) printInfo();
}

void drawTitle() {
  arduboy.fillRect(0, 0, 104, 8, WHITE);
  arduboy.setTextColor(BLACK);
  arduboy.setCursor(1, 0);
  printScaleNameAt(scaleIdx);
  arduboy.print(' ');
  arduboy.print(scoreb[rootNote]);
  arduboy.setTextColor(WHITE);
}

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

void printCompactScale(uint8_t idx, uint8_t y) {
  tinyfont.setCursor(1, y);
  char buf[12];
  strncpy_P(buf, scaleNames[idx], 11);
  buf[11] = 0;
  tinyfont.print(buf);
  tinyfont.print(' ');
  tinyfont.print(scoreb[rootNote]);
  printNotesAt(idx, y + 6, false);
}

void printScalaMode0() {
  uint8_t n = scaleLen(scaleIdx);
  bool big = (n <= 7);
  drawTitle();
  arduboy.fillRect(0, 11, WIDTH, 53, BLACK);
  printNotesAt(scaleIdx, 12, big);
  printSyllabicAt(scaleIdx, big ? 22 : 20);
  arduboy.drawFastHLine(0, 32, WIDTH, WHITE);
  printCompactScale((scaleIdx + 1) % NUM_SCALES, 35);
  printCompactScale((scaleIdx + 2) % NUM_SCALES, 49);
}

void printScalaMode1() {
  uint8_t n = scaleLen(scaleIdx);
  drawTitle();
  arduboy.fillRect(0, 11, WIDTH, 53, BLACK);
  printNotesAt(scaleIdx, 13, n <= 7);
  arduboy.drawFastHLine(0, 24, WIDTH, WHITE);
  printCompactScale((scaleIdx + 1) % NUM_SCALES, 28);
  printCompactScale((scaleIdx + 2) % NUM_SCALES, 46);
}

void playScala() {
  uint8_t n = scaleLen(scaleIdx);
  bool big = (n <= 7);
  uint8_t step = big ? 18 : ((n <= 8) ? 15 : 10);
  uint8_t y = (statusMode == 0) ? 11 : 12;
  uint8_t h = big ? 10 : 8;
  int durata = (n > 8) ? 420 : 800;
  int first = pgm_read_word(&allNotes[scaleNote(scaleIdx, 0)]);

  if (!mute) arduboy.audio.on();
  for (uint8_t i = 0; i < n; i++) {
    int nota = pgm_read_word(&allNotes[scaleNote(scaleIdx, i)]);
    if (nota < first) nota *= 2;
    sound.tone(nota, durata);
    arduboy.drawRect(i * step, y, step - 1, h, WHITE);
    arduboy.display();
    while (sound.playing()) {}
    arduboy.drawRect(i * step, y, step - 1, h, BLACK);
    arduboy.display();
  }
  arduboy.audio.off();
}

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

void playScalaMod2() {
  if (!mute) arduboy.audio.on();
  int nota = pgm_read_word(&allNotes[rootNote]);
  sound.tone(nota, 2000);
  arduboy.display();
  while (sound.playing()) {}
  arduboy.audio.off();
}

void playScalaMod3() {
  uint8_t n = scaleLen(scaleIdx);
  int durata = (n > 8) ? 380 : 700;
  int first = pgm_read_word(&allNotes[scaleNote(scaleIdx, 0)]);
  if (!mute) arduboy.audio.on();
  for (uint8_t i = 0; i < n; i++) {
    int nota = pgm_read_word(&allNotes[scaleNote(scaleIdx, i)]);
    if (nota < first) nota *= 2;
    sound.tone(nota, durata);
    arduboy.drawCircle(pnotes[i].x + 2, pnotes[i].y, 5, WHITE);
    arduboy.display();
    while (sound.playing()) {}
    arduboy.drawCircle(pnotes[i].x + 2, pnotes[i].y, 5, BLACK);
    redrawPentaNote(i);
    arduboy.display();
  }
  arduboy.audio.off();
}

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
