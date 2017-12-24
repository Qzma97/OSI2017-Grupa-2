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

RACUN format1(FILE*, char*);
int countf1(FILE*);

RACUN format2(FILE*, char*);
int countf2(FILE*);

RACUN format3(FILE*, char*);
int countf3(FILE*);

RACUN format4(FILE*,char*);
int countf4(FILE*);

RACUN format5(FILE*, char*, char*);
int countf5(FILE*);

int verifikacija(RACUN *);
void memory(FILE*, char*,char*);
void error(FILE*f, char*, char*);

void memory5(FILE*f, char*naziv, char*fajl);

#endif // FORMAT4_H
