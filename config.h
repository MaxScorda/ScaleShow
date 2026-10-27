#ifndef config_H
#define config_H

String scoreb[] = {"C", "Db", "D", "Eb",
                   "E", "F", "Gb", "G",
                   "Ab", "A", "Bb", "B"};

String scoreN[] = {"Do", "Reb", "Re", "Mib",
                   "Mi", "Fa", "Sob", "Sol",
                   "Lab", "La", "Sib", "Si"};

const uint16_t allNotes[] PROGMEM = {262, 277, 294, 311,
                                     330, 349, 370, 392,
                                     415, 440, 466, 494};

// intervalli assoluti dalla tonica, 99 = fine
PROGMEM const uint16_t scaleMod[][13] = {
  {0, 2, 4, 5, 7, 9, 11, 99},                // 0 maggiore (ionico)
  {0, 2, 3, 5, 7, 8, 10, 99},                // 1 minore
  {0, 2, 3, 5, 7, 9, 10, 99},                // 2 dorico
  {0, 1, 3, 5, 7, 8, 10, 99},                // 3 frigio
  {0, 2, 4, 6, 7, 9, 11, 99},                // 4 lidio
  {0, 2, 4, 5, 7, 9, 10, 99},                // 5 misolidio
  {0, 2, 3, 5, 7, 8, 10, 99},                // 6 eolio
  {0, 1, 3, 5, 6, 9, 11, 99},                // 7 locrio
  {0, 1, 3, 5, 7, 9, 11, 99},                // 8 napoletana
  {0, 1, 3, 5, 7, 8, 11, 99},                // 9 napoletana minore
  {0, 2, 3, 5, 7, 9, 11, 99},                //10 minore melodica
  {0, 2, 3, 5, 7, 8, 11, 99},                //11 minore armonica
  {0, 2, 4, 5, 7, 8, 11, 99},                //12 maggiore armonica
  {0, 1, 4, 5, 6, 9, 10, 99},                //13 orientale
  {0, 3, 4, 6, 7, 9, 10, 99},                //14 ungherese maggiore
  {0, 1, 4, 6, 8, 10, 11, 99},               //15 enigmatica
  {0, 2, 4, 7, 9, 99},                       //16 pentatonica maggiore
  {0, 2, 3, 5, 6, 8, 9, 11, 99},             //17 diminuita
  {0, 2, 4, 6, 8, 10, 99},                   //18 toni interi
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 99} //19 cromatica
};

const char scaleNames[][12] PROGMEM = {
  "Maggiore",
  "Minore",
  "Dorico",
  "Frigio",
  "Lidio",
  "Misolidio",
  "Eolio",
  "Locrio",
  "Napoletana",
  "Nap minore",
  "Min melod",
  "Min armon",
  "Mag armon",
  "Orientale",
  "Ungherese",
  "Enigmatica",
  "Penta mag",
  "Diminuita",
  "Toni interi",
  "Cromatica"
};

const uint8_t NUM_SCALES = 20;

// Accordi di GeneraAccordi: coppie {grado di scala, alterazione}, 99 = fine.  Grado 0=tonica, 2=terza, 4=quinta, 6=settima, 8=nona, 10=undicesima, 12=tredicesima
// Alterazione: semitoni da sommare. Valori speciali: 9 = settima minore (abbassa solo se la scala ha la settima maggiore), 8 = settima maggiore (alza solo se la scala ha la settima minore)
PROGMEM const char accMod[13][13] = {
  {99},
  {0,0, 2,0, 4,0, 99},                        // 1 Maj/Min
  {0,0, 2,0, 4,0, 6,8, 99},                   // 2 7a Magg
  {0,0, 2,0, 4,0, 6,9, 99},                   // 3 Settima
  {0,0, 2,0, 4,0, 8,0, 99},                   // 4 9a Agg
  {0,0, 2,0, 4,0, 6,8, 8,0, 99},              // 5 Magg.9a
  {0,0, 2,0, 4,0, 6,9, 8,0, 99},              // 6 Nona
  {0,0, 2,0, 4,0, 6,9, 8,1, 99},              // 7 9a aum
  {0,0, 2,0, 4,0, 6,9, 8,-1, 99},             // 8 9a min
  {0,0, 2,0, 4,0, 6,9, 8,0, 10,0, 99},        // 9 11a
  {0,0, 2,0, 4,0, 6,9, 8,0, 10,1, 99},        // 10 11a aum
  {0,0, 2,0, 4,0, 6,9, 8,0, 12,0, 99},        // 11 13a
  {0,0, 2,0, 4,0, 5,0, 99}                    // 12 Sesta
};

#endif
