#ifndef PRETRAGA_H
#define PRETRAGA_H
#include <stdio.h>
#include "Formati.h"

//F-ja za ubacivanje racuna u jednostruko povezanu listu.
void insert(NODE**, RACUN*);

//F-ja za brisanje liste.
void brisi_listu(NODE**);

//F-ja koja pretrazuje listu racuna po nazivu artikla.
int trazi_po_artiklu(NODE*, char*);

//F-ja za pregled svih podataka za odredjeni proizvod.
void artikal(NODE*, int, char*);

//F-ja koja pretrazuje listu racuna po datumu.
int trazi_po_datumu(NODE*, char*);

//F-ja za pregled ukupne prodaje za odredjeni mjesec
void mjesec(NODE*, char*, int);

//F-ja koja pretrazuje listu racuna po nazivu kupca.
int trazi_po_kupcu(NODE*head, char*kupac);

//F-ja  za pregled svih podataka za odredjenog kupca.
void kupac(NODE*, char*, int);

#endif // PRETRAGA_H