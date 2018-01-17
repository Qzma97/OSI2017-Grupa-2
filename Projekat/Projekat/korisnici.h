#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "osi.h"

typedef struct cvor { KORISNIK k; struct cvor *sljedeci; } CVOR;

int listSize(CVOR*);

void ispis_korisnika(CVOR *glava);

void deleteNode(CVOR **, int );

void promjenaTipa(int, int, CVOR**);

CVOR* ucitaj_naloge_iz_fajla();
