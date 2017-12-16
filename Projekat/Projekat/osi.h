#pragma once

typedef struct korisnik
{
	char PIN[5], korisnicko_ime[16];
	int tip;
	char ime[16], prezime[21];
} KORISNIK;
typedef struct artikal
{
	char* naziv[16], sifra[16];
	double kolicina, cijena, ukupno;
}ARTIKAL;
typedef struct racun
{
	char nazivKupca[16],datum[11];
	ARTIKAL* nizA;
	struct racun* next;
}RACUN;
RACUN* glava;
int prijava(KORISNIK*, int);
int search(KORISNIK*, int, KORISNIK*, char*, char*);
void registracija(KORISNIK*, int, FILE*);
int search_(KORISNIK*, int, char*);
int chechkFormat(FILE*);