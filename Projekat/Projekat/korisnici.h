#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "osi.h"

typedef struct cvor { KORISNIK korisnik; struct cvor *sljedeci; } CVOR;

//F-ja koja vraca broj cvorova(velicinu) liste.
int vratiVelicinuListe(CVOR*);

//F-ja koja formatirano ispisuje listu naloga.
void ispisKorisnika(CVOR *glava);

//F-ja za brisanje cvorova liste.
void izbrisiCvor(CVOR **, int );

//F-ja za promjenu tipa korisnika.
void promjenaTipa(int, int, CVOR**);

//F-ja za ucitavanje naloga iz fajla i smjesta ih u listu. Vraca pokazivac na prvi cvor.
CVOR* ucitajNalogeIzFajla();