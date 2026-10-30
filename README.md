# ScaleShow
Versione 2026-10-28. Commenti sulle funzioni inclusi.
ArduBoy. Scale, accordi e pentagramma in chiave di sol.

- Scale in notazione alfabetica (C, Db) e sillabica (Do, Reb)
- Scale in scaleNames (config.h): le 24 di prima piu' alterata, lidia dominante, bebop dominante, bebop maggiore, ungherese minore, persiana, hirajoshi, iwato, blues maggiore, diminuita semitono-tono, aumentata, prometheus
- Accordi della scala scelta (accMod)
- Pentagramma in chiave di sol
- Play della scala, dell'accordo o della nota singola

Il numero di scale e di accordi si calcola dalle righe degli array (NUM_SCALES, NUM_CHORDS).

ArduBoy<br>
https://arduboy.com/

Pentagramma (video)<br>
https://www.facebook.com/massimiliano.scordamaglia/videos/10154821437733406/

<hr>

# Schermate
A passa alla successiva. All'ultima si riparte da KEY.

0-KEY: scala alfabetica e le due successive, font normale<br>
1-ACC: accordi di quella scala. Su/giu cambiano l'accordo, non la scala<br>
2-ITA: scala in Do Re Mi, piu' le due scale successive<br>
3-MAN: scelta e play di una nota singola<br>
4-PEN: pentagramma, chiave di sol, tutta la scala<br>
5-INF: ScaleShow, Max Scordamaglia, 2026<br>

# Tasti
Destra / sinistra: tonica (C, Db, D...)<br>
Giu: scala successiva. In ACC: accordo successivo<br>
Su: scala precedente. In ACC: accordo precedente<br>
B: play scala (KEY, ITA, PEN), accordo (ACC) o nota (MAN)<br>
A: schermata successiva<br>
A tenuto 3 secondi: mute. In testata compare M<br>

# File
config.h: note, frequenze (A4 = 440 Hz), scaleMod, accMod, nomi<br>
ScaleShow.ino: setup, loop, variabili globali<br>
Funzioni.ino: tasti, lunghezza scala, nota di grado<br>
FunzScala.ino: schermate e play<br>
Grafica.ino: pentagramma<br>

Sopra ogni funzione c'e' il commento e, se ne ha, il significato dei parametri.
