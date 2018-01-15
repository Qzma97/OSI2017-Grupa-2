#include "korisnici.h"


void promjenaTipa(int pozicija, int tip, CVOR* glava)
{
	int i = 1;
	CVOR* temp = glava;
	while(temp && i < pozicija) {
		temp = temp->sljedeci;
		i++;
	}
	temp->k.tip = tip;
}