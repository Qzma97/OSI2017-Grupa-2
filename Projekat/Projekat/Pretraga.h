#ifndef PRETRAGA_H
#define PRETRAGA_H
#include <stdio.h>
#include "Formati.h"

//F-ja za ubacivanje racuna u jednostruko povezanu listu.
void dodajUListu(NODE**, RACUN*);

//F-ja za brisanje liste.
void brisiListu(NODE**);

//F-ja koja pretrazuje listu racuna po nazivu artikla.
int traziPoArtiklu(NODE*, char*);

//F-ja za pregled svih podataka za odredjeni proizvod.
void pregledArtikla(NODE*, int, char*);

//F-ja za izvoz pregleda svih podataka za odredjeni proizvod
void ispisZaArtikal(RACUN*, int, double, double,char*);

//F-ja koja pretrazuje listu racuna po datumu.
int traziPoDatumu(NODE*, char*);

//F-ja za pregled ukupne prodaje za odredjeni mjesec
void pregledMjeseca(NODE*, char*, int);

//F-ja za izvoz pregleda ukupne prodaje za odredjeni mjesec
void ispisZaMjesec(RACUN*, int, double, double);

//F-ja koja pretrazuje listu racuna po nazivu kupca.
int traziPoKupcu(NODE*, char*);

//F-ja  za pregled svih podataka za odredjenog kupca.
void pregledKupca(NODE*, char*, int);

//F-ja za izvoz pregleda podataka za odredjenog kupca
void ispisZaKupca(RACUN*, int);

#endif // PRETRAGA_H