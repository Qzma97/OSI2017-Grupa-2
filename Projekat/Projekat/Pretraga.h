#ifndef PRETRAGA_H
#define PRETRAGA_H
#include <stdio.h>
#include "Formati.h"

void insert(NODE**, RACUN*);
void brisi_listu(NODE**);
int trazi_po_artiklu(NODE*, char*);
void artikal(NODE*, int, char*);
int trazi_po_datumu(NODE*, char*);
void mjesec(NODE*, char*, int);
int trazi_po_kupcu(NODE*head, char*kupac);

#endif // FORMAT1_H