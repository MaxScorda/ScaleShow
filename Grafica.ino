// lettera e bemolle per C Db D Eb E F Gb G Ab A Bb B
const uint8_t letterOf[] PROGMEM = {0, 1, 1, 2, 2, 3, 4, 4, 5, 5, 6, 6};
const uint8_t isFlat[] PROGMEM = {0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0};

uint8_t staffGap = 4;
uint8_t staffBase = 62;

// Coordinata Y sul rigo.
// st: passo diatonico, 0 = Do. Sale verso l'alto.
uint8_t staffY(int st) {
  int y = (int)staffBase - st * (int)staffGap;
  if (y < 12) y = 12;
  if (y > 62) y = 62;
  return y;
}

// Chiave di sol, il ricciolo e' sulla riga del Sol.
void drawTrebleClef() {
  uint8_t yG = staffY(4);
  uint8_t yTop = staffY(10);
  uint8_t yBot = staffY(2);
  arduboy.drawLine(15, yTop - 4, 15, yBot + 6, WHITE);
  arduboy.drawCircle(11, yG, 4, WHITE);
  arduboy.drawPixel(14, yTop - 5, WHITE);
  arduboy.drawPixel(13, yTop - 6, WHITE);
  arduboy.drawPixel(12, yTop - 5, WHITE);
  arduboy.drawPixel(14, yBot + 7, WHITE);
  arduboy.drawPixel(13, yBot + 8, WHITE);
  arduboy.drawPixel(12, yBot + 7, WHITE);
}

// Testa della nota i, bemolle e taglio addizionale se serve.
// i: indice in pnotes.
void drawNoteHead(uint8_t i) {
  uint8_t x = pnotes[i].x;
  uint8_t y = pnotes[i].y;
  int st = pnotes[i].st;
  if (pnotes[i].flat) {
    arduboy.drawFastVLine(x - 4, y - 4, 6, WHITE);
    arduboy.drawPixel(x - 3, y, WHITE);
    arduboy.drawPixel(x - 3, y - 1, WHITE);
  }
  uint8_t hw = (staffGap >= 4) ? 7 : 6;
  uint8_t hh = (staffGap >= 4) ? 5 : 4;
  arduboy.fillRoundRect(x, y - (hh / 2), hw, hh, 1, WHITE);
  if ((st < 2 || st > 10) && ((st & 1) == 0)) {
    arduboy.drawFastHLine(x - 2, y, hw + 4, WHITE);
  }
}

// Ripristina righe e testa intorno alla nota i.
// i: indice in pnotes.
void redrawPentaNote(uint8_t i) {
  uint8_t x = pnotes[i].x;
  for (uint8_t s = 0; s < 5; s++) {
    arduboy.drawFastHLine(x - 5, staffY(2 + s * 2), 18, WHITE);
  }
  drawNoteHead(i);
}

// Schermata PEN: chiave di sol e tutte le note della scala scelta.
void showPenta() {
  uint8_t n = scaleLen(scaleIdx);
  if (n > 12) n = 12;
  pentaN = n;

  int prevLetter = -1;
  uint8_t oct = 0;
  uint8_t maxSt = 0;
  uint8_t steps[12];
  for (uint8_t i = 0; i < n; i++) {
    uint8_t ni = scaleNote(scaleIdx, i);
    int L = pgm_read_byte(&letterOf[ni]);
    if (i > 0 && L < prevLetter) oct++;
    prevLetter = L;
    steps[i] = L + oct * 7;
    if (steps[i] > maxSt) maxSt = steps[i];
  }
  staffGap = (maxSt > 11) ? 3 : 4;
  staffBase = 60;

  drawTitle();
  arduboy.fillRect(0, 11, WIDTH, 53, BLACK);

  uint8_t x0 = 26;
  uint8_t x1 = 118;
  uint8_t xstep = 12;
  if (n > 1) {
    xstep = (x1 - x0) / (n - 1);
    if (xstep > 14) xstep = 14;
    if (xstep < 8) xstep = 8;
  }
  for (uint8_t i = 0; i < n; i++) {
    uint8_t ni = scaleNote(scaleIdx, i);
    pnotes[i].st = steps[i];
    pnotes[i].flat = pgm_read_byte(&isFlat[ni]);
    pnotes[i].x = x0 + i * xstep;
    pnotes[i].y = staffY(steps[i]);
    drawNoteHead(i);
  }
  for (uint8_t s = 0; s < 5; s++) {
    arduboy.drawFastHLine(18, staffY(2 + s * 2), WIDTH - 20, WHITE);
  }
  drawTrebleClef();
}
