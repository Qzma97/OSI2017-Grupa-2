#ifndef PRETRAGA_H
#define PRETRAGA_H
#include <stdio.h>
#include "Format4.h"

int trazi_po_artiklu(NODE*, char*);
void artikal(NODE*, int, char*);
void brisi_listu(NODE**);
int trazi_po_datumu(NODE*, char*);
int trazi_po_kupcu(NODE*head, char*kupac);

#endif // FORMAT1_H