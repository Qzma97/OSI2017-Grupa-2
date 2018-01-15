typedef struct korisnik
{
	char PIN[5], korisnicko_ime[16];
	int tip;
	char ime[16], prezime[21];
	char email[100];
} KORISNIK;

typedef struct cvor { KORISNIK k; struct cvor *sljedeci; } CVOR;

void ispis_korisnika(CVOR *glava)
{
 int rb=0;
 printf("RB. KORISNICKI NALOG IME             PREZIME              TIP KORISNIKA EMAIL\n");
 while(glava)
{
	printf("%2d. %-16s %-15s %-20s ",rb++,glava->k.korisnicko_ime,glava->k.ime,glava->k.prezime);
	if((glava->k.tip)==0) printf("Analiticar   ");
	if ((glava->k.tip)==1) printf("Admin        ");
	printf(" %s\n",glava->k.email);
	glava=glava->sljedeci;
}
}