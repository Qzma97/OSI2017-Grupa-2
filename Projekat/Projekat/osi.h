#pragma once

typedef struct korisnik
{
	char PIN[5], korisnicko_ime[16];
	int tip;
	char ime[16], prezime[21];
	char email[100];
} KORISNIK;

int prijava(KORISNIK*, int);
int search(KORISNIK*, int, KORISNIK*, char*, char*);
void registracija(KORISNIK*, int, FILE*);
int search_(KORISNIK*, int, char*);
int chechkFormat(FILE*);