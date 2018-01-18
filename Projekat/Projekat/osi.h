#pragma once

typedef struct korisnik
{
	char PIN[5], korisnicko_ime[16];
	int tip;
	char ime[16], prezime[21];
	char email[100];
} KORISNIK;

//F-ja za prijavu korisnika. Argumenti: niz korisnickih naloga, index korisnickog naloga
int prijava(KORISNIK*, int);

//F-ja koja pretrazuje listu korisnika i uporedjuje korisnicka imena i PIN.
//Argumenti su: niz korisnickih naloga, velicinu niza, korisnika , username, PIN.
int search(KORISNIK*, int, KORISNIK*, char*, char*);

//F-ja za registraciju novih korisnika.
void registracija(KORISNIK*, int, FILE*);

//F-ja za pretrazivanje liste korisnika po imenu
int search_(KORISNIK*, int, char*);

//F-ja koja odredjuje kojeg je formata racun, vraca odgovarajuci broj formata
int checkFormat(FILE*);