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
	ARTIKAL *nizArtikala;
	int brojArtikala;
	double ukupno, pdv, ukupnoZaPlatiti;
	VALUTA valuta;
 }RACUN;

typedef struct node
{
	RACUN racun;
	struct node* sljedeci;
}NODE;

//Funkcija za ucitavanje podataka sa racuna prvog formata.
RACUN ucitajPodatkeZaFormat1(FILE*, char*);

//Funkcija koja vraca broj artikala na racunu formata 1.
int prebrojArtikleFormata1(FILE*);

//Funkcija za ucitavanje podataka sa racuna drugog formata.
RACUN ucitajPodatkeZaFormat2(FILE*, char*);

//Funkcija koja vraca broj artikala na racunu formata 2.
int prebrojArtikleFormata2(FILE*);

//Funkcija za ucitavanje podataka sa racuna treceg formata.
RACUN ucitajPodatkeZaFormat3(FILE*, char*);

//Funkcija koja vraca broj artikala na racunu formata 3.
int prebrojArtikleFormata3(FILE*);

//Funkcija za ucitavanje podataka sa racuna cetvrtog formata.
RACUN ucitajPodatkeZaFormat4(FILE*,char*);

//Funkcija koja vraca broj artikala na racunu formata 4.
int prebrojArtikleFormata4(FILE*);

//Funkcija za ucitavanje podataka sa racuna petog formata.
RACUN ucitajPodatkeZaFormat5(FILE*, char*, char*);

//Funkcija koja vraca broj artikala na racunu formata 5.
int prebrojArtikleFormata5(FILE*);

//Funkcija koja provjerava da li je racun ispravan ili ne.
int verifikacija(RACUN *);

//F-ja za cuvanje ispravnih racuna u "memory" folder.
void cuvajUMemory(FILE*, char*,char*);

//F-ja za cuvanje neispravnih racuna u "error" folder.
void cuvajUError(FILE*f, char*, char*);

#endif // FORMATI_H
