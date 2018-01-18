#ifndef FORMATI_H
#define FORMATI_H
#include <stdio.h>
#include "valuta.h"

typedef struct artikal
{
	char naziv[21];
	int sifra;
	double cijena, kolicina, ukupno;
}ARTIKAL;

typedef struct racun
{
	char kupac[21];
	char datum[21];
	ARTIKAL *nizA;
	int brojArtikala;
	double ukupno, pdv, ukupnoPl;
	VALUTA valuta;
 }RACUN;

typedef struct node
{
	RACUN racun;
	struct node* next;
}NODE;

//Funkcija za ucitavanje podataka sa racuna prvog formata.
RACUN format1(FILE*, char*);

//Funkcija koja vraca broj artikala na racunu formata 1.
int countf1(FILE*);

//Funkcija za ucitavanje podataka sa racuna drugog formata.
RACUN format2(FILE*, char*);

//Funkcija koja vraca broj artikala na racunu formata 2.
int countf2(FILE*);

//Funkcija za ucitavanje podataka sa racuna treceg formata.
RACUN format3(FILE*, char*);

//Funkcija koja vraca broj artikala na racunu formata 3.
int countf3(FILE*);

//Funkcija za ucitavanje podataka sa racuna cetvrtog formata.
RACUN format4(FILE*,char*);

//Funkcija koja vraca broj artikala na racunu formata 4.
int countf4(FILE*);

//Funkcija za ucitavanje podataka sa racuna petog formata.
RACUN format5(FILE*, char*, char*);

//Funkcija koja vraca broj artikala na racunu formata 5.
int countf5(FILE*);

//Funkcija koja provjerava da li je racun ispravan ili ne.
int verifikacija(RACUN *);

//F-ja za cuvanje ispravnih racuna u "memory" folder.
void memory(FILE*, char*,char*);

//F-ja za cuvanje neispravnih racuna u "error" folder.
void error(FILE*f, char*, char*);

#endif // FORMATI_H
