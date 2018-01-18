#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "osi.h"

typedef struct cvor { KORISNIK k; struct cvor *sljedeci; } CVOR;

//F-ja koja vraca broj cvorova(velicinu) liste.
int listSize(CVOR*);

//F-ja koja formatirano ispisuje listu naloga.
void ispis_korisnika(CVOR *glava);

//F-ja za brisanje cvorova liste.
void deleteNode(CVOR **, int );

//F-ja za promjenu tipa korisnika.
void promjenaTipa(int, int, CVOR**);

//F-ja za ucitavanje naloga iz fajla i smjesta ih u listu. Vraca pokazivac na prvi cvor.
CVOR* ucitaj_naloge_iz_fajla();