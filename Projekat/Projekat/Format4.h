#ifndef FORMAT4_H
#define FORMAT4_H
#include <stdio.h>

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
 }RACUN;

typedef struct node
{
	RACUN racun;
	struct node* next;
}NODE;

void insert(NODE**, RACUN*);

RACUN format4(FILE*,char*);

int countf4(FILE*);
#endif // FORMAT4_H
