#include "korisnici.h"

void promjenaTipa(int pozicija, int tip, CVOR** glava)
 {
	int i = 0;
	CVOR * temp = *glava;
	while (i != pozicija)
	{

		temp = temp->sljedeci;
		i++;
	}
	temp->korisnik.tip = tip;
}

CVOR* ucitajNalogeIzFajla()
{
    FILE* dat;
    KORISNIK k;
    CVOR* glava=0;
    int p;
    if((dat=fopen("korisnici.dat", "rb")) != NULL)
    {
        do
        {
           p=(fread(&k, sizeof(KORISNIK), 1, dat));
           if(p)
           {
               if(glava==0)
               {
                   CVOR* novi=(CVOR*)malloc(sizeof(CVOR));
                   novi->korisnik=k;
                   novi->sljedeci=0;
                   glava=novi;
               }
               else
                {
                    CVOR* privremeni;
                    CVOR* novi=(CVOR*)malloc(sizeof(CVOR));
                    for(privremeni=glava; privremeni->sljedeci != 0; privremeni=privremeni->sljedeci);
                    privremeni->sljedeci=novi;
                    novi->korisnik=k;
                    novi->sljedeci=0;
                }
           }
        }while(p);
        fclose(dat);
    }
     else
        printf("Greska prilikom otvaranja datoteke.\n");
    return glava;
}

void izbrisiCvor(CVOR**glava, int pozicija)
{
	
		if (*glava == NULL)
		 return;
	
		
		CVOR* privremeni = *glava;
	
		
		if (pozicija == 0)
		 {
		*glava = privremeni->sljedeci;
		free(privremeni);
		return;
		}
	
		
		for (int i = 0; privremeni != NULL && i < pozicija - 1; i++)
		 privremeni = privremeni->sljedeci;
		
		if (privremeni == NULL || privremeni->sljedeci == NULL)
		 return;
		CVOR *naredni = privremeni->sljedeci->sljedeci;
	
		free(privremeni->sljedeci);
	
		privremeni->sljedeci = naredni;
	}

int vratiVelicinuListe(CVOR *glava)
{
	int velicinaListe = 0;
	while (glava)
	{
		glava = glava->sljedeci;
		velicinaListe++;
	}
	return velicinaListe;
}

void ispisKorisnika(CVOR *glava)
{
	int rb = 1;
	printf("RB. KORISNICKI NALOG\tIME\t\tPREZIME\t\t\tTIP KORISNIKA\t\tEMAIL\n");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	while (glava)
	{
		printf("%d.  %-s\t\t%-s\t\t%-s\t\t", rb++, glava->korisnik.korisnicko_ime, glava->korisnik.ime, glava->korisnik.prezime);
		if ((glava->korisnik.tip) == 0) printf("Analiticar\t\t");
		if ((glava->korisnik.tip) == 1) printf("Admin     \t\t");
		printf("%s\n", glava->korisnik.email);
		glava = glava->sljedeci;
	}
}