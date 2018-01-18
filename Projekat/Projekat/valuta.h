#ifndef VALUTA_H
#define VALUTA_H

typedef struct valuta
{
	char oznaka[4];
	double koeficijent;
}VALUTA;

//F-ja koja ucitava defaultnu odabranu valutu.
VALUTA ucitajValutu();

//F-ja za izbor valute u kojoj ce se prikazivati racuni
void izborValute();

#endif //VALUTA_H