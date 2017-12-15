#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "osi.h"


int prijava(KORISNIK* niz, int n)
{
	char ime[16], pin[5];
	printf("KORISNICKO IME:"); scanf("%s", ime);
	printf("PIN:"); scanf("%s", pin);
	KORISNIK k;
	int d;
	if ((search(niz, n, &k, ime, pin)) == 1)
	{
		printf("USPJESNA PRIJAVA!\n");
		printf("-------------------------------------------------------------------------------------------------\n");
		printf("IZABERITE OPCIJU:\n");
		if (k.tip == 0)
		{
			printf("\t1.Pregled svih podataka za odredjenog kupca\n");
			printf("\t2.Pregled svih podataka za odredjeni proizvod\n");
			printf("\t3.Pregled ukupne prodaje za odredjeni mjesec\n");
			scanf("%d", &d);
			printf("-------------------------------------------------------------------------------------------------\n");
			/*if (d == 1)
			pregled_kupca();
			else if (d == 2)
			pregled_proizvoda();
			else if (d == 3)
			ukupna_prodaja();
			else
			printf("Greska!");*/
		}
		else if (k.tip == 1)
		{
			printf("\t1.Podesavanje valute\n");
			printf("\t2.Upravljanje korisnickim nalozima\n");
			scanf("%d", &d);
			printf("-------------------------------------------------------------------------------------------------\n");
			/*if (d == 1)
			podesavanje_valute();
			else if (d == 2)
			upravljanje_nalozima();
			else
			printf("Greska!\n");*/
		}
		return 1;

	}
	else
	{
		printf("NEPOSTOJECI KORISNIK!\n");
		return 0;
	}

}

void registracija(KORISNIK* niz, int n, FILE *f)
{

	KORISNIK temp;
	char pom1[16], pom2[5];
	printf("UNESITE PODATKE:\n");
	int i = 1;
	do
	{
		printf("\tKorisnicko ime:");
		scanf("%s", pom1);
		i = search_(niz, n, pom1);
		if (i == 1)
			printf("Korisnik sa tim imenom vec postoji.\n");
	} while (i == 1);
	strcpy(temp.korisnicko_ime, pom1);
	do
	{
		printf("\tPIN:");
		scanf("%s", pom2);
		i = strlen(pom2);
		for (int i = 0; i < sizeof(pom2) - 1; i++)
			if (pom2[i] < 48 || pom2[i]>57)
				i = 5;
		if (i != 4)
			printf("PIN se mora sastojati od 4 broja!\n");
	} while (i != 4);
	strcpy(temp.PIN, pom2);
	printf("\tIme:"); scanf("%s", temp.ime);
	printf("\tPrezime:"); scanf("%s", temp.prezime);
	temp.tip = 0;
	niz = (KORISNIK *)realloc(niz, (++n) * sizeof(KORISNIK));
	niz[n - 1] = temp;
	f = fopen("korisnici.dat", "wb");
	fwrite(niz, sizeof(KORISNIK), n, f);
	fclose(f);
	printf("PRIJAVA:\n");
	prijava(niz, n);
}

int search(KORISNIK* niz, int n, KORISNIK *k, char *ime, char *pin)
{
	for (int i = 0; i < n; i++)
	{
		if ((strcmp(ime, niz[i].korisnicko_ime) == 0) && (strcmp(pin, niz[i].PIN) == 0))
		{
			*k = niz[i];
			return 1;
		}
	}
	return 0;

}

int search_(KORISNIK* niz, int n, char* ime)
{
	for (int i = 0; i < n; i++)
	{
		if ((strcmp(ime, niz[i].korisnicko_ime) == 0))
			return 1;
	}
	return 0;
}