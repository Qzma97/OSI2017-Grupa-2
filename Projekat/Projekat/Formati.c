#include "Formati.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

RACUN ucitajPodatkeZaFormat1(FILE *fp, char *txt)
{
	int provjera = 0;
	RACUN racun;
	NODE* glava = 0;
	racun.brojArtikala = prebrojArtikleFormata1(fp);
	racun.nizArtikala = (ARTIKAL*)calloc(racun.brojArtikala, sizeof(ARTIKAL));
	fp = fopen(txt, "r");
	char pom[100], pom2[100];
	if (fp != NULL)
	{
		fseek(fp, 6, 1);
		fscanf(fp, " %s\n", racun.kupac);
		fseek(fp, 6, 1);
		fscanf(fp, " %s\n", racun.datum);
		for (int i = 0; i < 3; i++)
			fgets(pom, 100, fp);
		int i = 0;
		do {
			if (provjera)
				fseek(fp, -1L, SEEK_CUR);
			fscanf(fp, "%s %d", racun.nizArtikala[i].naziv, &racun.nizArtikala[i].sifra);
			while (fgetc(fp) == ' ' || fgetc(fp) == '-');
			fscanf(fp, "%lf", &racun.nizArtikala[i].kolicina);
			while (fgetc(fp) == ' ' || fgetc(fp) == '-');
			fscanf(fp, "%lf", &racun.nizArtikala[i].cijena);
			while (fgetc(fp) == ' ' || fgetc(fp) == '-');
			fscanf(fp, "%lf\n", &racun.nizArtikala[i].ukupno);
			i++;
			provjera = 1;
		} while (fgetc(fp) != '-');

		fgets(pom, 100, fp);
		fscanf(fp, "%s %lf\n", pom2, &racun.ukupno);
		fscanf(fp, "%s %lf\n", pom2, &racun.pdv);
		fscanf(fp, "%20c %lf\n", pom2, &racun.ukupnoZaPlatiti);
	}
	else printf("Greska pri otvaranju datoteke!");
	fclose(fp);
	return racun;
}

int prebrojArtikleFormata1(FILE *f)
{
	char junk[1024];
	int brojac = 0, n = 6, provjera = 1;
	while (n--)
		fgets(junk, sizeof(junk), f);
	while (provjera)
	{
		fgets(junk, sizeof(junk), f);
		if (strcmp(junk, "---------------------------------------\n") == 0)
			provjera = 0;
		if (provjera)
			brojac++;
	}
	fclose(f);
	return brojac;
}

RACUN ucitajPodatkeZaFormat2(FILE*fp, char*txt)
{
	int provjera = 0;
	RACUN racun;
	NODE* glava = 0;
	racun.brojArtikala = prebrojArtikleFormata2(fp);
	racun.nizArtikala = (ARTIKAL*)calloc(racun.brojArtikala, sizeof(ARTIKAL));
	fp = fopen(txt, "r");
	char pom[100], pom2[100];
	if (fp != NULL)
	{
		fgets(pom, 100, fp);
		fgets(pom, 100, fp);
		fgets(pom, 100, fp);
		fgets(pom, 100, fp);
		fgets(pom, 100, fp);
		fseek(fp, 6, 1);
		fscanf(fp, " %s\n", racun.kupac);
		for (int i = 0; i < 2; i++)
			fgets(pom, 100, fp);
		int i = 0;
		do {
			if (provjera)
				fseek(fp, -1L, SEEK_CUR);
			fscanf(fp, "%s %d", racun.nizArtikala[i].naziv, &racun.nizArtikala[i].sifra);
			while (fgetc(fp) == ' ' || fgetc(fp) == '-');
			fscanf(fp, "%lf", &racun.nizArtikala[i].kolicina);
			while (fgetc(fp) == ' ' || fgetc(fp) == '-');
			fscanf(fp, "%lf", &racun.nizArtikala[i].cijena);
			while (fgetc(fp) == ' ' || fgetc(fp) == '-');
			fscanf(fp, "%lf\n", &racun.nizArtikala[i].ukupno);
			provjera = 1;
			i++;
		} while (fgetc(fp) != '-');
		fgets(pom, 100, fp);
		fgets(pom, 100, fp);
		fscanf(fp, "%s %lf\n", pom2, &racun.ukupno);
		fscanf(fp, "%s %lf\n", pom2, &racun.pdv);
		fscanf(fp, "%20c %lf\n",pom2, &racun.ukupnoZaPlatiti);
		fscanf(fp, "%6c %s\n",pom2, racun.datum);
	}
	else printf("Greska pri otvaranju datoteke!");
	fclose(fp);
	return racun;
}

int prebrojArtikleFormata2(FILE *f)
{
	char junk[1024];
	int brojac = 0, n = 9, provjera = 1;
	while (n--)
		fgets(junk, sizeof(junk), f);
	while (provjera)
	{
		fgets(junk, sizeof(junk), f);
		if (strcmp(junk, "---------------------------------------\n") == 0)
			provjera = 0;
		if (provjera)
			brojac++;
	}
	fclose(f);
	return brojac;
}

RACUN ucitajPodatkeZaFormat3(FILE*fp, char*txt)
{
	int provjera = 0;
	RACUN racun;
	NODE* glava = 0;
	racun.brojArtikala = prebrojArtikleFormata3(fp);
	racun.nizArtikala = (ARTIKAL*)calloc(racun.brojArtikala, sizeof(ARTIKAL));
	fp = fopen(txt, "r");
	char pom[100], pom2[100];
	if (fp != NULL)
	{
		fgets(pom, 100, fp);
		fgets(pom, 100, fp);
		fseek(fp, 6, 1);
		fscanf(fp, " %s\n", racun.kupac);
		fseek(fp, 6, 1);
		fscanf(fp, " %s\n", racun.datum);
		for (int i = 0; i < 4; i++)
			fgets(pom, 100, fp);
		int i = 0;
		do {
			if (provjera)
				fseek(fp, -1L, SEEK_CUR);
			fscanf(fp, "%s %d", racun.nizArtikala[i].naziv, &racun.nizArtikala[i].sifra);
			fscanf(fp, "======%lf", &racun.nizArtikala[i].kolicina);
			fscanf(fp, "======%lf", &racun.nizArtikala[i].cijena);
			fscanf(fp, "======%lf\n", &racun.nizArtikala[i].ukupno);
			provjera = 1;
			i++;
		} while (fgetc(fp) != '-');
		fgets(pom, 100, fp);
		fscanf(fp, "%s %lf PDV: %lf\n", pom2, &racun.ukupno, &racun.pdv);
		fscanf(fp, "Ukupno za placanje: %lf", &racun.ukupnoZaPlatiti);
	}
	else printf("Greska pri otvaranju datoteke!");
	fclose(fp);
	return racun;
}

int prebrojArtikleFormata3(FILE *f)
{
	char junk[1024];
	int brojac = 0, n = 9, provjera = 1;
	while (n--)
		fgets(junk, sizeof(junk), f);
	while (provjera)
	{
		fgets(junk, sizeof(junk), f);
		if (strcmp(junk, "----------------------------------\n") == 0)
			provjera = 0;
		if (provjera)
			brojac++;
	}
	fclose(f);
	return brojac;
}

RACUN ucitajPodatkeZaFormat4(FILE* dat, char*txt)
{
	RACUN racun;
	char pom[50], pom2[50];
	int brRacuna;
	brRacuna = prebrojArtikleFormata4(dat);
	racun.brojArtikala = brRacuna;
	dat = fopen(txt, "r");
	if (dat != NULL)
	{

		racun.nizArtikala = (ARTIKAL*)calloc(brRacuna, sizeof(ARTIKAL));
		fseek(dat, 6, 1);
		fscanf(dat, "%s\n", racun.kupac);
		fseek(dat, 6, 1);
		fscanf(dat, "%s\n", racun.datum);
		for (int i = 0; i < 4; i++)
			fgets(pom, 50, dat);
		int check = 0, j = 0;
		do
		{
			if (check)
				fseek(dat, -1L, SEEK_CUR);
			fscanf(dat, "%s %d", racun.nizArtikala[j].naziv, &racun.nizArtikala[j].sifra);
			while (fgetc(dat) == ' ' || fgetc(dat) == '-');
			fscanf(dat, "%lf", &racun.nizArtikala[j].kolicina);
			while (fgetc(dat) == ' ' || fgetc(dat) == '-');
			fscanf(dat, "%lf", &racun.nizArtikala[j].cijena);
			while (fgetc(dat) == ' ' || fgetc(dat) == '-');
			fscanf(dat, "%lf\n", &racun.nizArtikala[j].ukupno);
			check = 1;
			j++;
		} while (fgetc(dat) != '-');
		fgets(pom, 50, dat);
		fscanf(dat, "%s %lf\n", pom2, &racun.ukupno);
		fscanf(dat, "%s %lf\n", pom2, &racun.pdv);
		fgets(pom, 50, dat);
		fgets(pom, 20, dat);
		fscanf(dat, "%lf\n", &racun.ukupnoZaPlatiti);
		return racun;
	}
	fclose(dat);
	return racun;
}

int prebrojArtikleFormata4(FILE *f)
{
	char junk[1024];
	int brojac = 0, n = 7, provjera=1;
	while (n--)
		fgets(junk, sizeof(junk), f);
	while (provjera)
	{
		fgets(junk, sizeof(junk), f);
		if (strcmp(junk, "---------------------------------------\n") == 0)
			provjera = 0;
		if(provjera)
			brojac++;
	}
	fclose(f);
	return brojac;
}

RACUN ucitajPodatkeZaFormat5(FILE *f, char *dir, char*nazivf)
{
	double ukupno = 0;
	RACUN racun;
	char pom[256], sifra[25] = { 0 };
	int i = 5, j = 0, brArtikala = 10;
	do {
		racun.kupac[j] = nazivf[i];
		j++;
		i++;
	} while (nazivf[i] != '#');
	racun.kupac[j] = 0;
	i++;
	j = 0;
	while (brArtikala--)
	{
		racun.datum[j] = nazivf[i];
		j++;
		i++;
	}
	racun.datum[2] = racun.datum[5] = '/';
	racun.datum[10] = 0;
	brArtikala = racun.brojArtikala = prebrojArtikleFormata5(f);
	fclose(f);
	racun.nizArtikala = (ARTIKAL*)calloc(brArtikala, sizeof(ARTIKAL));
	f = fopen(dir, "r");
	fgets(pom, sizeof(pom), f);
	i = 0;
	pom[1] = 0;
	while (brArtikala--)
	{
		j = 0;
		while (pom[0] = fgetc(f))
			if (pom[0] < 48 || pom[0]>57)
				j++;
			else
				break;
		fseek(f, -(j + 1), SEEK_CUR);
		int e = 0;
		while (j--)
		{
			racun.nizArtikala[i].naziv[e] = fgetc(f);
			e++;
		}
		fscanf(f, "%d,%lf,%lf,%lf\n", &racun.nizArtikala[i].sifra, &racun.nizArtikala[i].kolicina, &racun.nizArtikala[i].cijena, &racun.nizArtikala[i].ukupno);
		ukupno += racun.nizArtikala[i].ukupno;
		i++;
	}
	racun.pdv = ukupno * 0.17;
	racun.ukupno = ukupno;
	racun.ukupnoZaPlatiti = racun.pdv + racun.ukupno;
	fclose(f);
	return racun;
}

int prebrojArtikleFormata5(FILE *f)
{
	int brojac = 0;
	char pom[256];
	fgets(pom, sizeof(pom), f);
	while (fgets(pom, sizeof(pom), f))
		brojac++;
	return brojac;
}

int verifikacija(RACUN *r)
{
	int pom = 0;
	int n = r->brojArtikala;
	double ukupno = 0;
	for (int i = 0; i<n; i++)
	{
		ukupno += r->nizArtikala[i].ukupno;
		if ((r->nizArtikala[i].ukupno) == (r->nizArtikala[i].kolicina*r->nizArtikala[i].cijena)) pom++;
	}
	if ((ukupno == r->ukupno) && (pom == r->brojArtikala))
		return 1;
	else return 0;
}

void cuvajUMemory(FILE*f, char*naziv,char*fajl)
{
	char ch;
	fclose(f);
	char *pom=(char*)calloc(strlen(fajl)+20,sizeof(char));
	strcat(pom, "./memory/");
	strcat(pom, fajl);
	FILE* kopija = fopen(pom, "w");
	f = fopen(naziv, "r");
	while ((ch = fgetc(f)) != EOF)
		fputc(ch, kopija);
	fclose(kopija);
	fclose(f);
	remove(naziv);
	free(pom);
}

void cuvajUError(FILE*f, char*naziv, char*fajl)
{
	int i,j=4,k=0;
	char ch, extension[5] = { 0 };
	fclose(f);
	char *pom = calloc(strlen(naziv) + strlen("./error/") + 10, sizeof(char));
	strcat(pom, "./error/");
	strncat(pom, fajl, strlen(fajl)-4);
	strcat(pom, "_error");
	for (i = (strlen(fajl) - 4); j; i++, j--, k++)
		extension[k] = fajl[i];
	strcat(pom, extension);
	FILE*kopija = fopen(pom, "w");
	f = fopen(naziv, "r");
	while ((ch = fgetc(f)) != EOF)
		fputc(ch, kopija);
	fclose(kopija);
	fclose(f);
	remove(naziv);
}