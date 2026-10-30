# ScaleShow
Version 2026-10-31. Function comments are in the source.
Arduboy sketch: scales, chords and a treble-clef staff.

- Alphabetical note names (C, Db) and solfege (Do, Reb)
- Scale list is `scaleNames` in config.h. Major and minor come first, then alphabetical. Extra scales include altered, lydian dominant, bebop dominant, bebop major, Hungarian minor, Persian, Hirajoshi, Iwato, major blues, half-whole diminished, augmented and Prometheus
- Chords of the selected scale (`accMod`). Major/minor triad first, then by degree: 6th, 7th, 9th, 11th, 13th
- Treble clef staff
- Play the scale, the chord, or a single note

`NUM_SCALES` and `NUM_CHORDS` are the row counts of those arrays.

Arduboy<br>
https://arduboy.com/

Staff demo (video)<br>
https://www.facebook.com/massimiliano.scordamaglia/videos/10154821437733406/

<hr>

# Screens
A goes to the next screen. After the last one it returns to KEY.

0-KEY: alphabetical scale plus the next two, normal font. Secondary titles are inverted<br>
1-ACC: chords of the current scale. Up/Down change the chord, not the scale<br>
2-ITA: solfege (Do Re Mi) plus the next two scales<br>
3-MAN: pick and play a single note<br>
4-PEN: treble clef, the whole scale<br>
5-INF: ScaleShow, Max Scordamaglia, 2026<br>

# Buttons
Right / Left: root (C, Db, D...)<br>
Down: next scale. On ACC: next chord<br>
Up: previous scale. On ACC: previous chord<br>
B: play the scale (KEY, ITA, PEN), the chord (ACC) or the note (MAN)<br>
A: next screen<br>
Hold A for 3 seconds: mute. An M shows in the header<br>

# Files
config.h: note names, frequencies (A4 = 440 Hz), scaleMod, accMod, names<br>
ScaleShow.ino: setup, loop, globals<br>
Funzioni.ino: buttons, scale length, degree to pitch<br>
FunzScala.ino: screens and playback<br>
Grafica.ino: staff<br>

Each function has a comment above it. Parameters are described there.
