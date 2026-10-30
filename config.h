#ifndef config_H
#define config_H

#include <Arduino.h>

struct PNote {
  uint8_t x, y, st, flat;
};

String scoreb[] = {"C", "Db", "D", "Eb",
                   "E", "F", "Gb", "G",
                   "Ab", "A", "Bb", "B"};

String scoreN[] = {"Do", "Reb", "Re", "Mib",
                   "Mi", "Fa", "Sob", "Sol",
                   "Lab", "La", "Sib", "Si"};

const uint16_t allNotes[] PROGMEM = {262, 277, 294, 311,
                                     330, 349, 370, 392,
                                     415, 440, 466, 494};

PROGMEM const uint16_t scaleMod[][13] = {
  {0, 2, 4, 5, 7, 9, 11, 99},                // 0 Maggiore
  {0, 2, 3, 5, 7, 8, 10, 99},                // 1 Minore
  {0, 1, 3, 4, 6, 8, 10, 99},                // 2 Alterata
  {0, 3, 4, 7, 8, 11, 99},                   // 3 Aumentata
  {0, 2, 4, 5, 7, 9, 10, 11, 99},            // 4 Bebop dom
  {0, 2, 4, 5, 7, 8, 9, 11, 99},             // 5 Bebop mag
  {0, 3, 5, 6, 7, 10, 99},                   // 6 Blues
  {0, 2, 3, 4, 7, 9, 99},                    // 7 Blues mag
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 99},// 8 Cromatica
  {0, 1, 3, 4, 6, 7, 9, 10, 99},             // 9 Dim mezzo
  {0, 2, 3, 5, 6, 8, 9, 11, 99},             // 10 Diminuita
  {0, 2, 3, 5, 7, 9, 10, 99},                // 11 Dorico
  {0, 1, 4, 6, 8, 10, 11, 99},               // 12 Enigmatica
  {0, 2, 3, 5, 7, 8, 10, 99},                // 13 Eolio
  {0, 1, 3, 5, 7, 8, 10, 99},                // 14 Frigio
  {0, 1, 4, 5, 7, 8, 10, 99},                // 15 Frigio Dom
  {0, 1, 5, 7, 10, 99},                      // 16 Giapponese
  {0, 2, 3, 7, 8, 99},                       // 17 Hirajoshi
  {0, 1, 5, 6, 10, 99},                      // 18 Iwato
  {0, 2, 4, 6, 7, 9, 10, 99},                // 19 Lidia dom
  {0, 2, 4, 6, 7, 9, 11, 99},                // 20 Lidio
  {0, 1, 3, 5, 6, 8, 10, 99},                // 21 Locrio
  {0, 2, 4, 5, 7, 8, 11, 99},                // 22 Mag armon
  {0, 2, 3, 5, 7, 8, 11, 99},                // 23 Min armon
  {0, 2, 3, 5, 7, 9, 11, 99},                // 24 Min melod
  {0, 2, 4, 5, 7, 9, 10, 99},                // 25 Misolidio
  {0, 1, 3, 5, 7, 8, 11, 99},                // 26 Nap minore
  {0, 1, 3, 5, 7, 9, 11, 99},                // 27 Napoletana
  {0, 1, 4, 5, 7, 8, 11, 99},                // 28 Orientale
  {0, 2, 4, 7, 9, 99},                       // 29 Penta mag
  {0, 3, 5, 7, 10, 99},                      // 30 Penta min
  {0, 1, 4, 5, 6, 8, 11, 99},                // 31 Persiana
  {0, 2, 4, 6, 9, 10, 99},                   // 32 Prometheus
  {0, 2, 4, 6, 8, 10, 99},                   // 33 Toni interi
  {0, 2, 3, 6, 7, 8, 11, 99},                // 34 Ungh min
  {0, 3, 4, 6, 7, 9, 10, 99},                // 35 Ungherese
};

const char scaleNames[][12] PROGMEM = {
  "Maggiore",
  "Minore",
  "Alterata",
  "Aumentata",
  "Bebop dom",
  "Bebop mag",
  "Blues",
  "Blues mag",
  "Cromatica",
  "Dim mezzo",
  "Diminuita",
  "Dorico",
  "Enigmatica",
  "Eolio",
  "Frigio",
  "Frigio Dom",
  "Giapponese",
  "Hirajoshi",
  "Iwato",
  "Lidia dom",
  "Lidio",
  "Locrio",
  "Mag armon",
  "Min armon",
  "Min melod",
  "Misolidio",
  "Nap minore",
  "Napoletana",
  "Orientale",
  "Penta mag",
  "Penta min",
  "Persiana",
  "Prometheus",
  "Toni interi",
  "Ungh min",
  "Ungherese",
};

const uint8_t NUM_SCALES = sizeof(scaleMod) / sizeof(scaleMod[0]);

const char chordNames[][12] PROGMEM = {
  "",
  "Maj/Min",
  "Sesta",
  "6/9",
  "7a Magg",
  "Min 7a Mag",
  "Settima",
  "Minore 7a",
  "Dim7",
  "m7b5",
  "9a Agg",
  "Magg.9a",
  "Nona",
  "9a aum",
  "9a min",
  "11a",
  "11a aum",
  "Maj7 #11",
  "Lidia Dom",
  "13a",
  "Sus2",
  "Sus4",
  "7sus4",
  "5a aum",
  "Dim",
};

// Alterazioni speciali, non sono semitoni diretti:
// 9 settima minore (abbassa solo se la scala ha la 7a maggiore)
// 8 settima maggiore (alza solo se la scala ha la 7a minore)
// 7 terza minore (abbassa solo se la terza di scala e' maggiore)
// 6 quinta diminuita (abbassa solo se la quinta e' giusta)
// 4 settima diminuita (abbassa di 2 se 7a maggiore, di 1 se 7a minore)
PROGMEM const char accMod[][13] = {
  {99},
  {0,0, 2,0, 4,0, 99},                           // 1 Maj/Min
  {0,0, 2,0, 4,0, 5,0, 99},                      // 2 Sesta
  {0,0, 2,0, 4,0, 5,0, 8,0, 99},                 // 3 6/9
  {0,0, 2,0, 4,0, 6,8, 99},                      // 4 7a Magg
  {0,0, 2,7, 4,0, 6,8, 99},                      // 5 Min 7a Mag
  {0,0, 2,0, 4,0, 6,9, 99},                      // 6 Settima
  {0,0, 2,7, 4,0, 6,9, 99},                      // 7 Minore 7a
  {0,0, 2,7, 4,6, 6,4, 99},                      // 8 Dim7
  {0,0, 2,7, 4,6, 6,9, 99},                      // 9 m7b5
  {0,0, 2,0, 4,0, 8,0, 99},                      // 10 9a Agg
  {0,0, 2,0, 4,0, 6,8, 8,0, 99},                 // 11 Magg.9a
  {0,0, 2,0, 4,0, 6,9, 8,0, 99},                 // 12 Nona
  {0,0, 2,0, 4,0, 6,9, 8,1, 99},                 // 13 9a aum
  {0,0, 2,0, 4,0, 6,9, 8,-1, 99},                // 14 9a min
  {0,0, 2,0, 4,0, 6,9, 8,0, 10,0, 99},           // 15 11a
  {0,0, 2,0, 4,0, 6,9, 8,0, 10,1, 99},           // 16 11a aum
  {0,0, 2,0, 4,0, 6,8, 10,1, 99},                // 17 Maj7 #11
  {0,0, 2,0, 4,0, 6,9, 8,0, 10,1, 99},           // 18 Lidia Dom
  {0,0, 2,0, 4,0, 6,9, 8,0, 12,0, 99},           // 19 13a
  {0,0, 1,0, 4,0, 99},                           // 20 Sus2
  {0,0, 3,0, 4,0, 99},                           // 21 Sus4
  {0,0, 3,0, 4,0, 6,9, 99},                      // 22 7sus4
  {0,0, 2,0, 4,1, 99},                           // 23 5a aum
  {0,0, 2,7, 4,6, 99},                           // 24 Dim
};

const uint8_t NUM_CHORDS = sizeof(accMod) / sizeof(accMod[0]);


#endif
