#ifndef FORMAT4_H
#define FORMAT4_H
typedef struct artikal
{
	char naziv[21];
	int sifra;
	double cijena, kolicina, ukupno;
}ARTIKAL;
typedef struct racun
{
	char kupac[21];
	char datum[21];
	ARTIKAL nizA[21];
	int brojArtikala;
	double ukupno, pdv, ukupnoPl;
 }RACUN;
typedef struct node
{
	RACUN racun;
	struct node* next;
}NODE;
void insert(NODE**, RACUN*);
void format4();
void print();
#endif // FORMAT4_H
