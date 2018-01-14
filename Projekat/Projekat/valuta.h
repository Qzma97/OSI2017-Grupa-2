#ifndef VALUTA_H
#define VALUTA_H

typedef struct valuta
{
	char oznaka[4];
	double koeficijent;
}VALUTA;

VALUTA ucitajValutu();
void izborValute();

#endif //VALUTA_H
